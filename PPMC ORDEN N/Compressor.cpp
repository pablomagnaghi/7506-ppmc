#include "Compressor.h"


using namespace ppmc;
using namespace std;

Compressor::Compressor(util::FileReader* r, util::FileWriter* w)
	:Arithmetic(r,w){}

Compressor::~Compressor(){ }

void Compressor::compress(char c){
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;

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
		} else {
			std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			std::cout << frequencyTable.getTotal()<< std::endl;
		}

		// todo ver si hay que cambiar algo en este metodo, ya tenes los
		// datos total, y la frecuencia del esc o del char
		frequencyTable.setUpLimits(this->getBottom(), this->getTop(), c);

		u_int32_t bottom = frequencyTable.getNewBottom();
		u_int32_t top = frequencyTable.getNewTop();

		this->setNewLimits(bottom, top);
		models[pos]->update(context, c);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de 
				// exclusion
				std::cout << c <<" = 1/" << MAX -exclusionCharacters.size()<< std::endl;
				found = true;
				// todo ACA TENES QUE ACTULIZAR PISO Y TECHO
				// todo UTILIZA EL STRING DE EXCLUSION
				// todo tenes el caracter, los caracteres a quitar y con esos datos el 
				// todo total
				// todo y la frecuencia que en ese modelo es siempre 1
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

		// todo ver si hay que cambiar este metodo, ya tenes los
		// datos total, y la frecuencia ES del esc
		// HACER METODO NUEVO QUE YA SABE QUE RECIBE EOF
		// frequencyTable.setUpLimits(this->getBottom(), this->getTop(), c);

		// todo u_int32_t bottom = frequencyTable.getNewBottom();
		// todo u_int32_t top = frequencyTable.getNewTop();

		// todo this->setNewLimits(bottom, top);

		if (pos == 0) {
			// Esta en el Modelo -1 porque no se encontro en el Modelo 0
			// Obtengo los caracteres a excluir del modelo 0
			frequencyTable.getStringExc(exclusionCharacters);
			// Aplico mecanismo de exclusion restando a MAX el size del string de
			// exclusion
			std::cout << "EOF" << " = 1/" << MAX - exclusionCharacters.size() ;
			std::cout << std::endl;
			found = true;
			// todo ACA TENES QUE ACTULIZAR PISO Y TECHO
			// todo UTILIZA EL STRING DE EXCLUSION
			// todo tenes el EOF, los caracteres a quitar y con esos datos el total
			// todo y la frecuencia que en ese modelo es siempre 1
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