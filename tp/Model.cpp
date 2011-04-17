#include "Model.h"


using namespace ppmc;
using namespace std;

Model::Model(){

}

Model::~Model(){
	// ver si el destructor de std::map llama a los destructores de lo que tiene, 
	// si no hay que limpiar aca
}

ContextTable* Model::find(const std::string& contextName){
	std::map<std::string, ContextTable*>::iterator it;
	it = contextTables.find(contextName);
	if (it == contextTables.end()) {
		ContextTable* ct = new ContextTable();
		contextTables.insert(make_pair(contextName, ct));
		return ct;
		// dont forget to delete this somewhere
	}
	return it->second;
}
