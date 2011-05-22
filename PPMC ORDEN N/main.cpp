#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
using namespace ppmc;

int main(int argc, char* argv[]) {

	//ruta donde se guarda el archivo comprimido
	Compressor compresor;

	FrequencyTable table;

	//cadena a comprimir
	std::string cadena = "abracadabra";

	std::cout<<"Comprimiendo..."<<std::endl;

	for (std::size_t i = 0; i < cadena.size(); i++) {
		compresor.compress(cadena[i]);
	}



	return 0;

}
