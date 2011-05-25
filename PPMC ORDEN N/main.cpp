#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
using namespace ppmc;

int main(int argc, char* argv[]) {

	//ruta donde se guarda el archivo comprimido
	Compressor compresor;

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
