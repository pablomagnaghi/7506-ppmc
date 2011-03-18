/*
 * CompresorAritmetico.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef COMPRESORARITMETICO_H_
#define COMPRESORARITMETICO_H_

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include "Constants.h"
#include <algorithm>

class CompresorAritmetico {
private:
	u_int64_t bottom;
	u_int64_t top;
	char underflow_counter;
	char buffer;
	char bits_in_buffer;
	FILE * salida;
public:
	CompresorAritmetico(char *output_name);
	void solve_overflow();
	void solve_underflow();
	virtual void process(u_int16_t a)=0;
	u_int64_t get_bottom(){
		return this->bottom;
	}

	u_int64_t get_top(){
		return this->top;
	}

	void set_bottom(u_int64_t bottom){
		this->bottom = bottom;
	}

	void set_top(u_int64_t top){
		this->top = top;
	}

	void put_bit_in_buffer(char bit);
	void put_buffer_in_output();
	void put_byte_in_buffer(char byte);
	void clean_buffer();
	virtual ~CompresorAritmetico();
};

#endif /* COMPRESORARITMETICO_H_ */
