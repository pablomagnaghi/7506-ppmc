#include "Model.h"


using namespace ppmc;
using namespace std;

Model::Model(){

}

Model::~Model(){
	std::map<std::string, FrequencyTable*>::iterator iter;
	for( iter = frequencyTables.begin(); iter != frequencyTables.end(); ++iter ) {
		delete iter->second;
	}
}
std::string Model::show() {
	stringstream result;
	std::map<std::string, FrequencyTable*>::iterator it;
	for (it=frequencyTables.begin(); it != frequencyTables.end(); ++it) {
		result << "contexto " << it->first << endl << "TABLA: " << frequencyTables.size() << endl;
		result << it->second->show();
	}
	return result.str();
}

FrequencyTable* Model::find(const std::string& contextName){
	std::map<std::string, FrequencyTable*>::iterator it;
	it = frequencyTables.find(contextName);
	if (it == frequencyTables.end()) {
		FrequencyTable* ft = new FrequencyTable();
		frequencyTables.insert(make_pair(contextName, ft));
		return ft;
	}
	return it->second;
}
