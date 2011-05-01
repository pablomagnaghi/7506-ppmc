#include <string>
#include "Compressor.hpp"
#include <cmath>

#include <iostream>

using namespace lz78;
using namespace std;

Compressor::Compressor(size_t mb):bits(9){
	if (mb < 9) {
		throw 1;
	}
	max_bits=mb;
	code_table = new vector<string>(pow(2,max_bits));
	string c; 
	for (unsigned char pos = 0; pos < 255; pos ++) {
		c=pos;
		add(c); 
	}
}

void Compressor::compress(util::IFileReader* reader, util::IFileWriter* writer){
	char c = reader->read();
	string context;
	context = c;
	while (!reader->eof()) {
		c = reader->read();
		
		if ( find (context + c)) {
			context += c;
		} else {
			writer->write(encode(context));
			if (true) {
				add (context + c );
				context=c;
			}
		}
	}
	
	writer->write(encode(context));
	writer->write("'256");
}

bool Compressor::find(std::string match) {
	cout << "find" << endl;
	vector<string>::iterator it = code_table->begin();
	size_t pos = 0;
	for ( ; it != code_table->end(); it++) {
		if (match == *it) {
			cache = pos;
			return true;
		}
		pos++;
	}
	return false;
}

void Compressor::add(std::string match) {
	cout << "add" << endl;
	code_table->push_back(match);
}

std::string Compressor::encode(std::string match) {
	cout << "encode: " << match << endl;
	if (!find(match)) throw 1;
	cout << "encode: " << match << endl;
	string r;
	r = cache;
	return r;
	return code_table->at(cache);
}