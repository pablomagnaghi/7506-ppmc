#include <iostream>
#include "PPMC.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "PPMCCompressor.h"
#include "PPMCUncompressor.h"

using namespace ppmc;
using namespace util;

// TPGrupoXX -c pepe.txt
// Comprime el achivo pepe.txt generando el archivo pepe.txt.XX
// TPGrupoXX -x pepe.txt.XX
// Descomprime el archivo pepe.XX re-creando el archivo original (pepe.txt)

void help() {
	std::cerr << "Modo de uso: " << std::endl;
	std::cerr << "Para comprimir: -c archivo" << std::endl;
	std::cerr << "Para descomprimir: -x archivo" << std::endl;
}

int main(int argc, char* argv[]) {

	if (argc==3) {
		std::string mode(argv[1]);
		std::string name(argv[2]);
		if (mode == "-c") {
			FileReader in(name.c_str());
			std::cerr << "ARCHIVO A LEER: " << name << std::endl;
			name += ".XX";
			FileWriter out(name.c_str());
			std::cerr << "ARCHIVO COMPRIMIDO: " << name << std::endl;
			PPMCCompressor compresor(&in,&out);
			std::cerr << "Inicio compresión..." << std::endl;
			compresor.compress();
			std::cerr << "...fin compresión!" << std::endl;
		} else if(mode == "-x") {
			FileReader in(name.c_str());
			std::cerr << "ARCHIVO A LEER: " << name << std::endl;
			name = name.substr(0, name.size() - 3);
			FileWriter out(name.c_str());
			std::cerr << "ARCHIVO DESCOMPRIMIDO: " << name << std::endl;
			PPMCUncompressor uncompressor(&in, &out);
			std::cerr << "Inicio descompresión..." << std::endl;
			uncompressor.uncompress();
			std::cerr << "...fin descompresión!" << std::endl;
			} else {
				help();
			}
	} else {
		help();
	}

	return 0;
}
