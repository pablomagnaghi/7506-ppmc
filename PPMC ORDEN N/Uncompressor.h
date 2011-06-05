/*
 * Uncompressor.h
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#ifndef UNCOMPRESSOR_H_
#define UNCOMPRESSOR_H_

#include "Constants.h"
#include <math.h>
#include "FileReader.h"
#include "FileWriter.h"
#include "algorithm"
#include "Arithmetic.h"
#include <queue>

using namespace util;
using namespace ppmc;

class Uncompressor: public Arithmetic {
private:
	u_int32_t number;
	int bits_in_number;
	char buffer;
	int bits_in_buffer;
	std::queue<char> cola;
	int state;
	std::string currentContext;
	std::string exclusionChars;
	std::string firstContext;
	bool solveLastModel(std::string, std::string);
	int getCharFromModel(std::string);
	int getCharInLastModel(std::string);
	int getNextChar();
	/*
	 * Devuelve True si pudo resolver, false si no alcanzaron los bits
	 */
	bool solveNumber (u_int8_t a);

	void add_to_queue(char c){
		cola.push(c);
	}
	u_int32_t get_number(){
		return this->number;
	}
	int get_bits_in_buffer(){
		return this->bits_in_buffer;
	}
	int get_bits_in_number(){
		return this->bits_in_number;
	}
	void drop_buffer_in_number(){
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
	void remove_bits (int cant){
		this->number<<=cant;
		this->bits_in_number -= cant;
	}

	void uncompressorSolveOverflow(){
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
			top = (top & TOP);
			bottom = (bottom & TOP);
			remove_bits(bitsOfOverflow);
		}
	}

	void uncompressorSolveUnderflow(){
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
			top = (top & TOP);
			bottom = (bottom & TOP);
			this->number = ((BYTE_128 & number)|((number<<local_counter) & BYTE_127));
			this->bits_in_number -= local_counter;
		}

	}

	void uncompressorSetUpLimits(u_int32_t, u_int32_t);

public:
	Uncompressor();
	Uncompressor(util::FileReader* r, util::FileWriter* w);
	void uncompress();
	virtual ~Uncompressor();
};

#endif /* UNCOMPRESSOR_H_ */
