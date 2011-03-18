/*
 * Principal.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include <iostream>
#include "CompresorAritmeticoOrden0.h"
#include "CompresorAritmeticoOrden1.h"
#include "DescompresorAritmeticoOrden0.h"
#include "DescompresorAritmeticoOrden1.h"
#include <iomanip>
#include <string>
#include <string.h>

void pasar_a_binario(char nro){
	int i;
	for (i=7; i>=0; i--){
		if (((nro>>i) & 1)==1)
			std::cout<<"1";
		else std::cout<<"0";
	}
	std::cout<<std::endl;
}

int main(int argc, char **argv) {

	if (argc == 3){
		if (strcmp(argv[1], "-c") == 0){

			//ruta donde se guarda el archivo comprimido
			CompresorAritmeticoOrden1 * compresor = new CompresorAritmeticoOrden1("/home/luis/Escritorio/comprimido.xx");

			//archivo a comprimir
			FILE * entrada = fopen(argv[2], "r");
			char c ;
			std::cout<<"Comprimiendo..."<<std::endl;
			while ( !feof(entrada)){
				c = fgetc(entrada);
				compresor->process(c);
			}
			fclose (entrada);
			delete compresor;
		}
		if (strcmp(argv[1], "-x") == 0){
			DescompresorAritmeticoOrden1 * descompresor = new DescompresorAritmeticoOrden1("/home/luis/Escritorio/comprimido.xx");
			FILE * salida = fopen("/home/luis/Escritorio/archivoDescomprimido.html", "w");
			bool end = false;
			std::cout<<"Descomprimiendo..."<<std::endl;
			while ( !end){
				char value = descompresor->extract();
				if (value == EOF){
					end = true;
				}
				else {
					fputc(value, salida);
				}
			}
			fclose(salida);
			delete descompresor;
		}
	}

}

