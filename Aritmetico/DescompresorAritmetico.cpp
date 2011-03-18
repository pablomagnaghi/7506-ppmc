/*
 * DescompresorAritmetico.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "DescompresorAritmetico.h"
#include <math.h>

DescompresorAritmetico::DescompresorAritmetico(char * entrada):cola(){
	this->inputfile = fopen (entrada, "r");
	this->bottom = BYTE_BOTTOM;
	this->top = BYTE_TOP;
	this->number = 0;
	this->bits_in_number = 0;
	this->bits_in_buffer = 0;
}

void DescompresorAritmetico::solve_overflow(){
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
		remove_bits(bitsOfOverflow);
	}
}

void DescompresorAritmetico::solve_underflow(){
	int i = 29;
	int local_counter = 0;
	int first_bit_top = (top>>31) & 1;
	int first_bit_bottom = (bottom>>31) & 1;
	int bit_bottom = (bottom>>30) & 1;
	int bit_top = (top>>30) & 1;
	if (first_bit_bottom != first_bit_top){
		while ((first_bit_bottom != bit_bottom)&&(first_bit_top != bit_top)&&(bit_bottom != bit_top)){
			local_counter++;
			bit_bottom = (bottom>>i) & 1;
			bit_top = (top>>i) & 1;
			i--;
		}
	}
	if (local_counter>0){
		u_int64_t new_bottom = ((BYTE_128 & bottom)|((bottom<<local_counter) & BYTE_127));
		bottom = new_bottom;
		u_int64_t new_techo = ((BYTE_128 & top)|((top<<local_counter) & BYTE_127));
		top = new_techo;
		u_int64_t shift = pow (2,local_counter)-1;
		top = (top | shift);
		top = (top & AUX_BYTE);
		bottom = (bottom & AUX_BYTE);
		this->number = ((BYTE_128 & number)|((number<<local_counter) & BYTE_127));
		this->bits_in_number -= local_counter;
	}
}

char DescompresorAritmetico::extract(){
	char c;
	bool end = false;
	while (cola.empty() && !end){
		c = fgetc(inputfile);
		end = this->process(c);
	}

	char result = cola.front();
	cola.pop();
	return result;
}

void DescompresorAritmetico::drop_buffer_in_number(){
	u_int32_t aux = 0x00000000;
	char bit;
	int i = 7;
	int caracteres = this->bits_in_buffer;
	if (caracteres + this->bits_in_number >32){
		caracteres = 32-this->bits_in_number;
	}
	int k = 0;
	int l = this->bits_in_buffer;
	while ((k<caracteres) && (this->bits_in_buffer>0)){
		bit = (buffer>>i)&1;
		bit &= 0x01;
		aux<<=1;
		aux |= bit;
		this->bits_in_buffer--;
		buffer<<=1;
		k++;
	}
	int shift = 24 - this->bits_in_number + (8-l);
	if (shift>0)
		aux <<= shift;
	number |= aux;
	this->bits_in_number += caracteres;
}

void DescompresorAritmetico::remove_bits(int cant){
	this->number<<=cant;
	this->bits_in_number -= cant;
}


DescompresorAritmetico::~DescompresorAritmetico() {
}