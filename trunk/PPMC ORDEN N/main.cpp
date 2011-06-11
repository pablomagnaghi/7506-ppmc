#include <iostream>
#include <stdexcept>
#include "PPMC.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "PPMCCompressor.h"
#include "PPMCUncompressor.h"

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
		FileReader in(argv[2]);
		FileWriter out(argv[3]);
		
		if (mode=="c") {
			PPMCCompressor c(&in,&out);
			cerr << "Inicio compresión..." << endl;
			c.compress();
			cerr << "...fin compresión!" << endl;
		} else if(mode=="x") {
			PPMCUncompressor d(&in,&out);
			cerr << "Inicio descompresión..." << endl;
			d.uncompress();
			cerr << "...fin descompresión!" << endl;
		} else {
			throw invalid_argument(mode);
		}
	} catch (invalid_argument& e) {
		cerr << "Modo " << e.what() << " no reconocido" << endl;
		cerr << "Debe elegir \"c\" para comprimir o \"x\" para descomprimir" << endl;
		return 1;
	} catch (bad_arguments& e) {
		cerr << "Cantidad de argumentos incorrecta" << endl;
		cerr << "Modo de uso: " << argv[0] << "  [c|x] entrada salida" << endl;
		return 2;
	} catch (exception& e) {
		cerr << "Error interno: " << e.what() << endl;
		return 3;
	}

	return 0;
}
