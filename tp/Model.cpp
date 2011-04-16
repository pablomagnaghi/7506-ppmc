#include "Model.h"


using namespace ppmc;
using namespace std;

Model::Model(){

}

Model::~Model(){
	// ver si el destructor de std::map llama a los destructores de lo que tiene, 
	// si no hay que limpiar aca
}

ContextTable* Model::find(ContextSelector& cs, size_t depth){
	std::map<std::string, ContextTable*>::iterator it;
	it = contextTables.find(cs.get(depth));
	if (it == contextTables.end()) {
		return new ContextTable();
		// dont forget to delete this somewhere
	}
	return it->second;
}
