#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "Decompressor.h"
#include "FileReader.h"
#include "FileWriter.h"

#include <stdexcept>
#include <iostream>
#include <string>

using namespace ppmc;
using namespace std;
using namespace util;
class bad_arguments:public exception {};
	
/**
 * @todo mejorar tipo y manejo de excepciones
 *
 */ 
int main(int argc, char* argv[]) {
	FileReader* in = 0;
	FileWriter* out = 0;
	size_t order = 2;
	try {
		if (argc!=4) {
			throw bad_arguments();
		}
		
		std::string mode(argv[1]);
		in = new FileReader(argv[2]);
		out = new FileWriter(argv[3]);
		
		if (mode=="c") {
			Compressor c(order);
			cerr << "Inicio compresión..." << endl;
			c.compress(in,out);
			cerr << "...fin compresión!" << endl;
		} else if(mode=="d") {
			Decompressor d(order);
			cerr << "Inicio descompresión..." << endl;
			d.decompress(in,out);
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
		cout << "checkpoint 5.1" << endl;
		cerr << "Error interno: " << e.what() << endl;
	}
	if (in) delete in;
	if (out) delete out;

}
