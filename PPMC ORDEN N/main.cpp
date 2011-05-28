#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "../tp/FileWriter.h"
#include "../tp/FileReader.h"

using namespace ppmc;
using namespace util;

int main(int argc, char* argv[]) {
	FileReader r("in.txt");
	FileWriter w("out.z");
	//ruta donde se guarda el archivo comprimido
	Compressor compresor(&r,&w);

	//cadena a comprimir
	std::string cadena = "ABDABABABD";

	std::cout<<"Comprimiendo..."<<std::endl;

	for (std::size_t i = 0; i < cadena.size(); i++) {
		compresor.compress(cadena[i]);
	}

	compresor.compressEof();

	compresor.clean_buffer();

	return 0;

}
