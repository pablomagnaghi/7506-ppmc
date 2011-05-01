#include <string>
#include "Compressor.hpp"
#include <cmath>

#include <sstream>

using namespace lz78;
using namespace std;

Compressor::Compressor(size_t mb):bits(9){
	if (mb < 9) {
		throw 1;
	}
	max_bits=mb;
	//pow(2,max_bits)
	code_table = new vector<string>();
	add("eof");
	cache = 0;
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
			if (true) { // it checks that code_table not full, use exception instead
				add (context + c );
				context=c;
			}
		}
	}
	
	writer->write(encode(context));
	writer->write("'256");
}

bool Compressor::find(std::string match) {
	if (match.size() == 1) {
		return true;
	}
	
	//if (code_table->at(cache) == match) return true;
	
	cache = 256;
	vector<string>::iterator it = code_table->begin();
	for ( ; it != code_table->end(); it++) {
		if (match == *it) {
			return true;
		}
		cache++;
	}
	return false;
}

void Compressor::add(std::string match) {
	code_table->push_back(match);
}

std::string Compressor::encode(std::string match) {
	if (!find(match)) throw 1;
	if (match.size() == 1) {
		return match;
	}
	stringstream ss;
	ss << "'" << cache ;
	return ss.str();
}