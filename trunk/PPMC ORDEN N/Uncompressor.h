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
public:
	Uncompressor();
	Uncompressor(util::FileReader* r, util::FileWriter* w);
	void uncompress();
	void solve_overflow();
	void solve_underflow();

	char extract();

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
	bool process (u_int8_t a);
	bool calculateChar(int *,std::string);
	bool calculateCharInLastModel(int *, std::string);
	void drop_buffer_in_number();
	void remove_bits (int cant);
	virtual ~Uncompressor();
};

#endif /* UNCOMPRESSOR_H_ */
