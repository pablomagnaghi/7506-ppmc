#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "Decompressor.h"
#include "FileReader.h"
#include "FileWriter.h"

#include <exception>

#include <iostream>
#include <string>

using namespace ppmc;
using namespace util;

/**
 * @todo mejor tipo y manejo de excepciones
 *
 */ 
int main(int argc, char* argv[]) {
	FileReader* in = 0;
	FileWriter* out = 0;
	size_t order = 2;
	try {
		if (argc!=4) {
			throw new std::exception();
		}
		
		std::string mode(argv[1]);
		in = new FileReader(argv[2]);
		out = new FileWriter(argv[3]);
		if (mode=="c") {
			Compressor c(order);
			c.compress(in,out);
		} else if(mode=="d") {
			Decompressor d(order);
			d.decompress(in,out);
		} else {
			throw new std::exception();
		}
	} catch ( std::exception* e) {
		std::cerr << "Modo de uso: " << argv[0] << "  [c|d] entrada salida" << std::endl;
	}
	if (in) delete in;
	if (out) delete out;

}
