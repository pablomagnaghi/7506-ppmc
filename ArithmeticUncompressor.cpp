#include <cmath>

#include "ArithmeticUncompressor.h"

using namespace ppmc;
using namespace util;
using namespace std;

ArithmeticUncompressor::ArithmeticUncompressor(FileReader* r, FileWriter* w):charQueue() {
	this->reader = r;
	this->writer = w;
	this->bottom = BYTE_BOTTOM;
	this->top = BYTE_TOP;
	this->number = 0;
	this->bitsInNumber = 0;
	this->bitsInBuffer = 0;
	this->buffer = 0x00;
}

void printInBin(u_int32_t x){
	int i;
	for (i=31; i>=0; i--){
		if (((x>>i) & 1)==1)
			cout<<"1";
		else cout<<"0";
	}
	cout<<endl;
}

void ArithmeticUncompressor::solveOverflow(){
	int i=31;
	int bitsOfOverflow=0;
	while (((bottom>>i) & 1)==((top>>i) & 1)){
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
		removeBits(bitsOfOverflow);
	}
}

void ArithmeticUncompressor::solveUnderflow(){
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
		this->number = ((BYTE_128 & number)|((number<<localCounter) & BYTE_127));
		this->bitsInNumber -= localCounter;
	}
}

void ArithmeticUncompressor::uncompress(){
	if (order == (size_t) -1) {
		reader->copy(writer);
	} else {
		size_t currentPos = 0;
		while (currentPos < size){
			u_int16_t value = this->extract();
			++currentPos;
			if (value != END_OF_FILE){
				this->writer->write(value);
			}
		}
	}
}

u_int16_t ArithmeticUncompressor::extract(){
	char c;
	bool end = false;
	while (charQueue.empty() && !end && !reader->eof()){
		c = this->reader->read();
		end = this->process(c);
	}

	u_int16_t result = charQueue.front();
	charQueue.pop();
	return result;
}

void ArithmeticUncompressor::addToQueue(u_int16_t c){
	charQueue.push(c);
}

u_int64_t ArithmeticUncompressor::getBottom(){
	return this->bottom;
}

u_int64_t ArithmeticUncompressor::getTop(){
	return this->top;
}

void ArithmeticUncompressor::setBottom(u_int64_t bottom){
	this->bottom = bottom;
}

void ArithmeticUncompressor::setTop(u_int64_t top){
	this->top = top;
}

void ArithmeticUncompressor::setBuffer(char a){
	this->buffer = a;
	this->bitsInBuffer = 8;
}

u_int32_t ArithmeticUncompressor::getNumber(){
	return this->number;
}

int ArithmeticUncompressor::getBitsInNumber(){
	return this->bitsInNumber;
}

int ArithmeticUncompressor::getBitsInBuffer(){
	return this->bitsInBuffer;
}

void ArithmeticUncompressor::dropBufferInNumber(){
	u_int32_t aux = 0x00000000;
	char bit;
	int i = 7;
	int caracteres = this->bitsInBuffer;
	if (caracteres + this->bitsInNumber >32){
		caracteres = 32-this->bitsInNumber;
	}
	int k = 0;
	int l = this->bitsInBuffer;
	while ((k<caracteres) && (this->bitsInBuffer>0)){
		bit = (buffer>>i)&1;
		bit &= 0x01;
		aux<<=1;
		aux |= bit;
		this->bitsInBuffer--;
		buffer<<=1;
		k++;
	}
	int shift = 24 - this->bitsInNumber + (8-l);
	if (shift>0)
		aux <<= shift;
	number |= aux;
	this->bitsInNumber += caracteres;
}

void ArithmeticUncompressor::removeBits(int cant){
	this->number<<=cant;
	this->bitsInNumber -= cant;
}

ArithmeticUncompressor::~ArithmeticUncompressor() {
}
