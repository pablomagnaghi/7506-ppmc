#include "Model.h"

using namespace ppmc;

Model::Model(){
	size = 0;
}

Model::~Model(){
	map<string, FrequencyTable*>::iterator it = model.begin();
	while (it != model.end() ) {
		delete it->second;
		it++;
	}
}

FrequencyTable* Model::find(const string& context){
	map<string, FrequencyTable*>::iterator it;
	// Busco el contexto en el modelo
	it = model.find(context);

	// Si esta devuelvo la tabla de frecuencias
	if (it != model.end()) {
		return it->second;
	}

	size++;
	FrequencyTable* ct = new FrequencyTable();
	model.insert(make_pair(context, ct));
	return ct;
}

string Model::show(){
	stringstream result;
	map<string, FrequencyTable*>::iterator it = model.begin();

	while (it != model.end() ) {
		result << "contexto " << it->first << endl;
		result << it->second->show();
		it++;
	}
	return result.str();
}

// El contexto se creo en el metodo find(), ahora hay que
// actualizar su tabla de frecuencias
void Model::update(const string& context, u_int8_t c) {
	map<string, FrequencyTable*>::iterator it;

	// Busco el contexto en el modelo
	it = model.find(context);

	// Es seguro que existe porque sino se encontro
	// en el find(), se creo la tabla para ese contexto
	it->second->addCharacter(c);
}

size_t Model::getSize() {
	return size;
}
