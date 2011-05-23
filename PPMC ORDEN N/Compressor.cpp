#include "Compressor.h"


using namespace ppmc;
using namespace std;

Compressor::Compressor():Arithmetic(){

}

Compressor::~Compressor(){


}

void Compressor::compress(char c){
	bool encontrado = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;
	// necesito mapa de probabilidades, <frecuencia, total>

	std::cout << "-----CARACTER " << c << " CONTEXTO " << context << std::endl;

	while (!encontrado) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));
		// todo falta agregar mecanismo de exclusion
		if (frequencyTable.find(c)) {
			encontrado = true;
		}
		frequencyTable.setUpLimits(this->getBottom(), this->getTop(), c);
		u_int64_t bottom = frequencyTable.getNewBottom();
		u_int64_t top = frequencyTable.getNewTop();
		this->setNewLimits(bottom, top);
		models[pos]->update(context, c);

		if (pos == 0) {
			// Esta en el Modelo -1 porque no se encontro
			// en el Modelo 0
			encontrado = true;
			// obtener probabilidad
			// no actualiza modelo -1 porque es fijo
		} else {
			pos--;
			context = context.substr(1);
		}

		// todo aca hay que tomar la tabla de frecuencias para actualizar
		// piso y techo

		frequencyTable.clear();
	}

	for (int i = ORDEN; i > -1; i--) {
		if (models[i]->getSize()) {
			std::cout << "Modelo " << i << ": " << std::endl;
			models[i]->show();
		}
	}

	// actualizo el contexto
	contextSelector.add(c);
}
