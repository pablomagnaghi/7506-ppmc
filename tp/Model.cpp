#include "Model.h"


using namespace ppmc;
using namespace std;

Model::Model(){

}

Model::~Model(){
	// ver si el destructor de std::map llama a los destructores de lo que tiene, 
	// si no hay que limpiar aca
}

FrequencyTable* Model::find(const std::string& contextName){
	std::map<std::string, FrequencyTable*>::iterator it;
	it = frequencyTables.find(contextName);
	if (it == frequencyTables.end()) {
		FrequencyTable* ft = new FrequencyTable();
		frequencyTables.insert(make_pair(contextName, ft));
		return ft;
		// dont forget to delete this somewhere
	}
	return it->second;
}
