#include "Compressor.h"

#include "Constants.h"
#include <stdio.h>
using namespace ppmc;
using namespace std;

Compressor::Compressor(util::FileReader* r, util::FileWriter* w)
:Arithmetic(r,w){}

Compressor::~Compressor(){ }

void Compressor::compress(u_int8_t c){
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;

	std::cout << "top " << this->getTop() << std::endl;
	printf("hexa: %x\n", this->getTop());
	std::cout << "Bin: ";
	print_in_bin(this->getTop());
	std::cout << "bottom " << this->getBottom() << std::endl;
	printf("hexa: %x\n", this->getBottom());
	std::cout << "Bin: ";
	print_in_bin(this->getBottom());

	std::cout << "LEO " << c << " CONTEXTO " << context << " EMITO:" << std::endl;

	while (!found) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));

		// Aplico mecanismo de exclusion
		frequencyTable.exc(exclusionCharacters);

		if (frequencyTable.find(c)) {
			found = true;
			std::cout << c << " = " << frequencyTable.getFrequencyChar() << "/";
			std::cout << frequencyTable.getTotal() << std::endl;
			frequencyTable.setUpLimitsWithCharacter(this->getBottom(), this->getTop(), c);
		} else {
			std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			std::cout << frequencyTable.getTotal()<< std::endl;
			frequencyTable.setUpLimitsWithEscape(this->getBottom(), this->getTop());
		}
		this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

		std::cout << "top " << this->getTop() << std::endl;
		printf("hexa: %x\n", this->getTop());
		std::cout << "Bin: ";
		print_in_bin(this->getTop());
		std::cout << "bottom " << this->getBottom() << std::endl;
		printf("hexa: %x\n", this->getBottom());
		std::cout << "Bin: ";
		print_in_bin(this->getBottom());
		models[pos]->update(context, c);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de 
				// exclusion
				std::cout << c <<" = 1/" << MAX - exclusionCharacters.size()<< std::endl;
				found = true;
				u_int32_t lastModelBottom = this->getBottom();
				u_int32_t lastModelTop = this->getTop();
				frequencyTable.setUpLimitsOnLastModel(lastModelBottom, lastModelTop, c, exclusionCharacters);

				this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

				std::cout << "top " << this->getTop() << std::endl;
				printf("hexa: %x\n", this->getTop());
				std::cout << "Bin: ";
				print_in_bin(this->getTop());
				std::cout << "bottom " << this->getBottom() << std::endl;
				printf("hexa: %x\n", this->getBottom());
				std::cout << "Bin: ";
				print_in_bin(this->getBottom());
				// no actualiza modelo -1 porque es fijo
			}
		} else {
			pos--;
			context = context.substr(1);
		}

		// Agrego los posibles caracteres a excluir a la cadena de
		// caracteres de exclusion
		frequencyTable.getStringExc(exclusionCharacters);
		frequencyTable.clear();
	}

	show();

	// actualizo el contexto
	contextSelector.add(c);
}

void Compressor::compressEof(){
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;

	std::cout << "LEO EOF CONTEXTO " << context << " EMITO:" << std::endl;

	while (!found) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));

		// Aplico mecanismo de exclusion
		frequencyTable.exc(exclusionCharacters);

		std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/" ;
		std::cout << frequencyTable.getTotal()<< std::endl;
		frequencyTable.setUpLimitsWithEscape(this->getBottom(), this->getTop());
		this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

		std::cout << "top " << this->getTop() << std::endl;
		printf("hexa: %x\n", this->getTop());
		std::cout << "Bin: ";
		print_in_bin(this->getTop());
		std::cout << "bottom " << this->getBottom() << std::endl;
		printf("hexa: %x\n", this->getBottom());
		std::cout << "Bin: ";
		print_in_bin(this->getBottom());
		if (pos == 0) {
			// Esta en el Modelo -1 porque no se encontro en el Modelo 0
			// Obtengo los caracteres a excluir del modelo 0
			frequencyTable.getStringExc(exclusionCharacters);
			// Aplico mecanismo de exclusion restando a MAX el size del string de
			// exclusion
			std::cout << "EOF" << " = 1/" << MAX - exclusionCharacters.size() ;
			std::cout << std::endl;
			found = true;
			u_int32_t lastModelBottom = this->getBottom();
			u_int32_t lastModelTop = this->getTop();
			frequencyTable.setUpLimitsWithEOF(lastModelBottom, lastModelTop, exclusionCharacters);
			this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

			std::cout << "top " << this->getTop() << std::endl;
			printf("hexa: %x\n", this->getTop());
			std::cout << "Bin: ";
			print_in_bin(this->getTop());
			std::cout << "bottom " << this->getBottom() << std::endl;
			printf("hexa: %x\n", this->getBottom());
			std::cout << "Bin: ";
			print_in_bin(this->getBottom());
		} else {
			pos--;
			context = context.substr(1);
		}

		// Agrego los posibles caracteres a excluir a la cadena de
		// caracteres de exclusion
		frequencyTable.getStringExc(exclusionCharacters);
		frequencyTable.clear();
	}
}
