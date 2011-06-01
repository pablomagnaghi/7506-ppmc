/*
 * Uncompressor.h
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#ifndef UNCOMPRESSOR_H_
#define UNCOMPRESSOR_H_

#include "FileReader.h"
#include "FileWriter.h"
#include "algorithm"
#include <queue>

using namespace util;

class Uncompressor {
private:
	FileReader inputfile;
	FileWriter outputFile;
	u_int32_t bottom;
	u_int32_t top;
	u_int32_t number;
	int bits_in_number;
	char buffer;
	int bits_in_buffer;
	std::queue<char> cola;
public:
	Uncompressor();
	Uncompressor(char * fileInput, char * fileOutput);
	void uncompress();
	void solve_overflow();
	void solve_underflow();
	virtual bool process (char a) = 0;

	char extract();

	void add_to_queue(char c){
		cola.push(c);
	}

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

	void set_buffer(char a){
		this->buffer = a;
		this->bits_in_buffer = 8;
	}

	u_int32_t get_number(){
		return this->number;
	}

	int get_bits_in_number(){
		return this->bits_in_number;
	}

	int get_bits_in_buffer(){
		return this->bits_in_buffer;
	}

	void drop_buffer_in_number();
	void remove_bits (int cant);
	virtual ~Uncompressor();
};

#endif /* UNCOMPRESSOR_H_ */
