#include "Arithmetic.h"
#include "Constants.h"
#include <math.h>

using namespace ppmc;
using namespace std;

Arithmetic::Arithmetic(){
	for (size_t i=0; i<(ORDEN + 1);i++) {
		models.push_back(new Model());
	}
	this->bottom = BOTTOM;
	this->top = TOP;
	this->buffer = EMPTY_BUFFER;
	this->bits_in_buffer = 0;
	this->underflow_counter = 0;
}


void print_in_bin(u_int32_t x){
	int i;
	for (i=MAX_BIT; i>=0; i--){
		if (((x>>i) & 1)==1)
			std::cout<<"1";
		else std::cout<<"0";
	}
	std::cout<<std::endl;
}

u_int32_t Arithmetic::getBottom(){
	return this->bottom;
}


u_int32_t Arithmetic::getTop(){
	return this->top;
}

void Arithmetic::setNewLimits(u_int32_t bottom, u_int32_t top){

	this->bottom = bottom;
	this->top = top;
	this->solve_overflow();
	this->solve_underflow();
}

void Arithmetic::addBitToBuffer(u_int8_t bit){
	bit &= 0x01;
	this->buffer <<= 1;
	this->buffer |= bit;
	this->bits_in_buffer++;
	if (this->bits_in_buffer==MAX_BIT + 1){
		putBufferInFileWriter();
	}
}

void Arithmetic::putBufferInFileWriter(){
	print_in_bin(this->buffer);

	this->bits_in_buffer = 0;
}

void Arithmetic::solve_underflow(){
	int i = MAX_BIT - 2;
	int local_counter = 0;
	int first_bit_top = (this->top>>MAX_BIT) & 1;
	int first_bit_bottom = (this->bottom>>MAX_BIT) & 1;
	int bit_bottom = (this->bottom>>MAX_BIT-1) & 1;
	int bit_top = (this->top>>MAX_BIT-1) & 1;
	if (first_bit_bottom != first_bit_top){
		while ((first_bit_bottom != bit_bottom)&&(first_bit_top != bit_top)&&(bit_bottom != bit_top)){
			local_counter++;
			bit_bottom = (this->bottom>>i) & 1;
			bit_top = (this->top>>i) & 1;
			i--;
		}
	}
	if (local_counter>0){
		u_int32_t new_bottom = ((BYTE_128 & this->bottom)|((this->bottom<<local_counter) & BYTE_127));
		this->bottom = new_bottom;
		u_int32_t new_techo = ((BYTE_128 & this->top)|((this->top<<local_counter) & BYTE_127));
		this->top = new_techo;
		u_int32_t shift = pow (2,local_counter)-1;
		this->top = (this->top | shift);
		this->top = (this->top & TOP);
		this->bottom = (this->bottom & TOP);
		this->underflow_counter += local_counter;
	}
}

void Arithmetic::solve_overflow(){
	int i=MAX_BIT;
	int bitsOfOverflow=0;
	while (((this->bottom>>i) & 1)==((this->top>>i) & 1)){
		addBitToBuffer((this->top>>i)&1);
		int k;
		if (this->underflow_counter>0){
			for (k=0; k<this->underflow_counter; k++){
				addBitToBuffer(~(this->top>>i) & 1);
			}
			this->underflow_counter = 0;
		}
		i--;
		bitsOfOverflow++;
	}
	if (bitsOfOverflow>0){
		this->bottom<<=bitsOfOverflow;
		u_int32_t shift = pow (2,bitsOfOverflow)-1;
		this->top<<=bitsOfOverflow;
		this->top = (this->top | shift);
		this->top = (this->top & TOP);
		this->bottom = (this->bottom & TOP);
	}
}

void Arithmetic::clean_buffer(){
	int i;
	for (i=MAX_BIT; i>=0; i--){
		addBitToBuffer((this->bottom>>i) & 1);
	}
	if (this->bits_in_buffer != 0){
		int k;
		int bit_to_put = (~(this->buffer>>(this->bits_in_buffer-1))&1);
		for (k = 63; this->bits_in_buffer!=0; k--)
			addBitToBuffer(bit_to_put);
	}
	//todo cerrar el fileWriter
}


Arithmetic::~Arithmetic(){
	for (size_t i=0; i<(ORDEN + 1);i++) {
		delete models[i];
	}
}
