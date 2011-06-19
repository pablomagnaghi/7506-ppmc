#include <iostream>
#include <cmath>

#include "Arithmetic.h"

#include <climits>

using namespace ppmc;
using namespace std;

Arithmetic::Arithmetic(size_t o):order(o){
	for (size_t i=0; i<=order;i++) {
		models.push_back(new Model);
	}
	floor = 0;
	ceiling = floor -1;
}

Arithmetic::~Arithmetic(){
	for (size_t i=0; i<=order;i++) {
		delete models[i];
	}
}

void Arithmetic::setNewLimits(){
	solve_overflow();
	solve_underflow();
}

void Arithmetic::print_in_bin(baseType x){
	int i;
	for (i=MAX_BIT; i>=0; i--){
		if (((x>>i) & 1)==1)
			std::cerr<<"1";
		else std::cerr<<"0";
	}
	std::cerr<<std::endl;
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
#ifdef VERBOSE
	print_in_bin(this->buffer);
#endif
	writer->write(this->buffer);
	this->bits_in_buffer = 0;
}

void Arithmetic::solve_underflow(){
	int i = MAX_BIT - 2;
	int local_counter = 0;
	int first_bit_ceiling = (this->ceiling>>MAX_BIT) & 1;
	int first_bit_floor = (this->floor>>MAX_BIT) & 1;
	int bit_floor = (this->floor>>(MAX_BIT-1)) & 1;
	int bit_ceiling = (this->ceiling>>(MAX_BIT-1)) & 1;
	if (first_bit_floor != first_bit_ceiling){
		while ((first_bit_floor != bit_floor)&&(first_bit_ceiling != bit_ceiling)&&(bit_floor != bit_ceiling)){
			local_counter++;
			bit_floor = (this->floor>>i) & 1;
			bit_ceiling = (this->ceiling>>i) & 1;
			i--;
		}
	}
	// get rid of new_floor and new_techo
	if (local_counter>0){
		baseType new_floor = ((BYTE_128 & this->floor)|((this->floor<<local_counter) & BYTE_127));
		this->floor = new_floor;
		baseType new_techo = ((BYTE_128 & this->ceiling)|((this->ceiling<<local_counter) & BYTE_127));
		this->ceiling = new_techo;
		baseType shift = pow (2,local_counter)-1;
		this->ceiling = (this->ceiling | shift);
		this->underflow_counter += local_counter;
	}
}

void Arithmetic::solve_overflow(){
	int i=MAX_BIT;
	int bitsOfOverflow=0;
	while (((this->floor>>i) & 1)==((this->ceiling>>i) & 1)){
		addBitToBuffer((this->ceiling>>i)&1);
		int k;
		if (this->underflow_counter>0){
			for (k=0; k<this->underflow_counter; k++){
				addBitToBuffer(~(this->ceiling>>i) & 1);
			}
			this->underflow_counter = 0;
		}
		i--;
		bitsOfOverflow++;
	}
	if (bitsOfOverflow>0){
		this->floor<<=bitsOfOverflow;
		baseType shift = pow (2,bitsOfOverflow)-1;
		this->ceiling<<=bitsOfOverflow;
		this->ceiling = (this->ceiling | shift);
	}
}

void Arithmetic::clean_buffer(){
	int i;
	for (i=MAX_BIT; i>=0; i--){
		addBitToBuffer((this->floor>>i) & 1);
	}
	if (this->bits_in_buffer != 0){
		int k;
		int bit_to_put = (~(this->buffer>>(this->bits_in_buffer-1))&1);
		for (k = 63; this->bits_in_buffer!=0; k--)
			addBitToBuffer(bit_to_put);
	}
	//todo cerrar el fileWriter
}