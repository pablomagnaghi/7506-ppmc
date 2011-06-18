#include "ArithmeticCompressor.h"

using namespace ppmc;

ArithmeticCompressor::ArithmeticCompressor(FileReader* r, FileWriter* w) {
	this->reader = r;
	this->writer = w;
	this->top = BYTE_TOP;
	this->bottom = BYTE_BOTTOM;
	this->bitsInBuffer = 0;
	this->underflowCounter = 0;
	this->buffer = 0x00;
}

u_int64_t ArithmeticCompressor::getBottom(){
	return this->bottom;
}

u_int64_t ArithmeticCompressor::getTop(){
	return this->top;
}

void ArithmeticCompressor::setBottom(u_int64_t bottom){
	this->bottom = bottom;
}

void ArithmeticCompressor::setTop(u_int64_t top){
	this->top = top;
}

void ArithmeticCompressor::solveOverflow(){
	int i=31;
	int bitsOfOverflow=0;
	while (((bottom>>i) & 1)==((top>>i) & 1)){
		putBitInBuffer((top>>i)&1);
		int k;
		if (underflowCounter>0){
			for (k=0; k<underflowCounter; k++){
				putBitInBuffer(~(top>>i) & 1);
			}
			this->underflowCounter = 0;
		}
		i--;
		bitsOfOverflow++;
	}
	if (bitsOfOverflow>0){
		bottom<<=bitsOfOverflow;
		unsigned long shift = pow (2,bitsOfOverflow)-1;
		top<<=bitsOfOverflow;
		top = (top | shift);
		top = (top & AUX_BYTE);
		bottom = (bottom & AUX_BYTE);
	}
}

void ArithmeticCompressor::solveUnderflow(){
	int i = 29;
	int localCounter = 0;
	int firstBitTop = (top>>31) & 1;
	int firstBitBottom = (bottom>>31) & 1;
	int bitBottom = (bottom>>30) & 1;
	int bitTop = (top>>30) & 1;
	if (firstBitBottom != firstBitTop){
		while ((firstBitBottom != bitBottom)&&(firstBitTop != bitTop)&&(bitBottom != bitTop)){
			localCounter++;
			bitBottom = (bottom>>i) & 1;
			bitTop = (top>>i) & 1;
			i--;
		}
	}
	if (localCounter>0){
		u_int64_t newBottom = ((BYTE_128 & bottom)|((bottom<<localCounter) & BYTE_127));
		bottom = newBottom;
		u_int64_t newTecho = ((BYTE_128 & top)|((top<<localCounter) & BYTE_127));
		top = newTecho;
		u_int64_t shift = pow (2,localCounter)-1;
		top = (top | shift);
		top = (top & AUX_BYTE);
		bottom = (bottom & AUX_BYTE);
		this->underflowCounter += localCounter;
	}
}

void ArithmeticCompressor::putBitInBuffer(char bit){
	bit &= 0x01;
	this->buffer <<= 1;
	this->buffer |= bit;
	this->bitsInBuffer++;
	if (bitsInBuffer==8){
		putBufferInOutput();
	}
}

void ArithmeticCompressor::putBufferInOutput(){
	this->writer->write(buffer);
	this->bitsInBuffer=0;
}

void ArithmeticCompressor::cleanBuffer(){

	int i;
	for (i=31; i>=0; i--){
		putBitInBuffer((bottom>>i) & 1);
	}
	if (this->bitsInBuffer != 0){
		int k;
		int bitToPut = (~(buffer>>(bitsInBuffer-1))&1);
		for (k = 7; bitsInBuffer!=0; k--)
			putBitInBuffer(bitToPut);
	}
}

ArithmeticCompressor::~ArithmeticCompressor() {
}
