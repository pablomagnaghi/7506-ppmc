/*
 * CompresorAritmetico.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "CompresorAritmetico.h"
#include "math.h"

CompresorAritmetico::CompresorAritmetico(char *output_name) {
	salida = fopen(output_name, "w");
	this->top = BYTE_TOP;
	this->bottom = BYTE_BOTTOM;
	this->bits_in_buffer = 0;
	this->underflow_counter = 0;
}

void CompresorAritmetico::solve_overflow(){
	int i=31;
	int bitsOfOverflow=0;
	while (((bottom>>i) & 1)==((top>>i) & 1)){
		put_bit_in_buffer((top>>i)&1);
		int k;
		if (underflow_counter>0){
			for (k=0; k<underflow_counter; k++){
				put_bit_in_buffer(~(top>>i) & 1);
			}
			this->underflow_counter = 0;
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

void CompresorAritmetico::solve_underflow(){
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
		this->underflow_counter += local_counter;
	}
}



void CompresorAritmetico::put_bit_in_buffer(char bit){
	bit &= 0x01;
	this->buffer <<= 1;
	this->buffer |= bit;
	this->bits_in_buffer++;
	if (bits_in_buffer==8){
		put_buffer_in_output();
	}
}


void CompresorAritmetico::put_buffer_in_output(){
	int x = (int) buffer;
	fputc(x, salida);
	this->bits_in_buffer=0;
}

void CompresorAritmetico::put_byte_in_buffer(char byte){
	int x = (int) byte;
	fputc(x, salida);
}

void CompresorAritmetico::clean_buffer(){

	int i;
	for (i=31; i>=0; i--){
		put_bit_in_buffer((bottom>>i) & 1);
	}
	if (this->bits_in_buffer != 0){
		int k;
		int bit_to_put = (~(buffer>>(bits_in_buffer-1))&1);
		for (k = 7; bits_in_buffer!=0; k--)
			put_bit_in_buffer(bit_to_put);
	}
	fclose(salida);
}



CompresorAritmetico::~CompresorAritmetico() {

}
