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
	int state;
	std::string currentContext;
	std::string exclusionChars;
	std::string firstContext;
public:
	Uncompressor();
	Uncompressor(util::FileReader* r, util::FileWriter* w);
	void uncompress();
	void uncompressorSolveOverflow();
	void uncompressorSolveUnderflow();
	void uncompressorSetUpLimits(u_int32_t, u_int32_t);
	bool solveNonLastModel(std::string, std::string, std::string);
	bool solveLastModel(std::string, std::string);
	int extract();

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

	/*
	 * Devuelve True, si es el end of file
	 */
	bool process (u_int8_t a);
	int getChar(std::string);
	int getCharInLastModel(std::string);
	void drop_buffer_in_number();
	void remove_bits (int cant);
	virtual ~Uncompressor();
};

#endif /* UNCOMPRESSOR_H_ */
