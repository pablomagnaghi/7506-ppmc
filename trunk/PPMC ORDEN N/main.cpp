#include <iostream>
#include <stdexcept>
#include "PPMC.h"
#include "Compressor.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Uncompressor.h"

using namespace ppmc;
using namespace util;
using namespace std;

class bad_arguments:public exception {};

int main(int argc, char* argv[]) {
	try {
		if (argc!=4) {
			throw bad_arguments();
		}
		
		std::string mode(argv[1]);
		//size_t order = atoi(argv[2]);
		FileReader in(argv[2]);
		FileWriter out(argv[3]);
		
		if (mode=="c") {
			Compressor compresor(&in,&out);
			cerr << "Inicio compresión..." << endl;
			
			// mover este loop a compress o quitar el reader del constructor
			char c = in.read();
			while (!in.eof() ) {
				compresor.compress(c);
				c = in.read();
			}
			compresor.compressEof();
			compresor.clean_buffer();
			cerr << "...fin compresión!" << endl;
		} else if(mode=="d") {
			Uncompressor uncompressor(&in, &out);
			cerr << "Inicio descompresión..." << endl;
			uncompressor.uncompress();
			cerr << "...fin descompresión!" << endl;
		} else {
			throw invalid_argument(mode);
		}
	} catch (invalid_argument& e) {
		cerr << "Modo " << e.what() << " no reconocido" << endl;
		cerr << "Debe elegir (c)omprimir o (d)escomprimir" << endl;
	} catch (bad_arguments& e) {
		cerr << "Cantidad de argumentos incorrecta" << endl;
		cerr << "Modo de uso: " << argv[0] << "  [c|d] entrada salida" << endl;
	} catch (exception& e) {
		cerr << "Error interno: " << e.what() << endl;
	}
}
