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
		
		string mode(argv[1]);
		FileReader in(argv[2], 2048);
		FileWriter out(argv[3], 2048);
		
		if (mode=="c") {
			PPMCCompressor c(&in,&out);
			c.compress();
		} else if(mode=="x") {
			PPMCUncompressor d(&in,&out);
			d.uncompress();
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
	} catch (bad_alloc& e) {
		cerr << "Nos hemos quedado sin memoria, pruebe con un orden menor" << endl;
		return 3;
	} catch (ios_base::failure& e) {
		cerr << "Error de archivos: " << e.what() << endl;
		return 4;
	} catch (exception& e) {
		cerr << "Error interno: " << e.what() << endl;
		return 5;
	}

	return 0;
}
