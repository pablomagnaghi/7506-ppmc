#include "Model.h"


using namespace ppmc;
using namespace std;

Model::Model(){
	size = 0;
}

Model::~Model(){
	std::map<std::string, FrequencyTable*>::iterator it = model.begin();
	while (it != model.end() ) {
		delete it->second;
		it++;
	}
}

FrequencyTable* Model::find(const std::string& context){
	std::map<std::string, FrequencyTable*>::iterator it;
	// Busco el contexto en el modelo
	it = model.find(context);

	// Si esta devuelvo la tabla de frecuencias
	if (it != model.end()) {
		return it->second;
	}

	//std::cout << "creando tabla para contexto " << context << std::endl;
	size++;
	FrequencyTable* ct = new FrequencyTable();
	model.insert(make_pair(context, ct));
	return ct;
}

void Model::show(){
	std::map<std::string, FrequencyTable*>::iterator it = model.begin();

	while (it != model.end() ) {
		std::cout << "contexto " << it->first << std::endl;
		it->second->show();
		it++;
	}
}

// El contexto se creo en el metodo find(), ahora hay que
// actualizar su tabla de frecuencias
void Model::update(const std::string& context, char c) {
	std::map<std::string, FrequencyTable*>::iterator it;

	// Busco el contexto en el modelo
	it = model.find(context);

	//codigo insertado de prueba
	if (it == model.end()){
		size++;
		FrequencyTable* ct = new FrequencyTable();
		model.insert(make_pair(context, ct));
	}
	it = model.find(context);


	// Es seguro que existe porque sino se encontro
	// en el find(), se creo la tabla para ese contexto
	it->second->addCharacter(c);
}

std::size_t Model::getSize() {
	return size;
}


