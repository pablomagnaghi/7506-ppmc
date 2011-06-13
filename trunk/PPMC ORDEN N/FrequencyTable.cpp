#include "FrequencyTable.h"

using namespace ppmc;

FrequencyTable::FrequencyTable() {
	esc = 1;
	firstPass = true;
	frequency = 1;
	this->total = 1;
	this->top = 0;
	this->bottom = 0;
}

FrequencyTable::~FrequencyTable() {}

map<u_int16_t, size_t> FrequencyTable::getTable(){
	return table;
}

map<u_int16_t, size_t>::iterator FrequencyTable::tableBegin() {
  return table.begin();
}

map<u_int16_t, size_t>::iterator FrequencyTable::tableEnd() {
  return table.end();
}

size_t FrequencyTable::getFrequencyChar() {
	return frequency;
}

size_t FrequencyTable::getFrequencyEsc() {
	return esc;
}

u_int32_t FrequencyTable::getTotal() {
	return total;
}

bool isInString(u_int8_t c, std::string exclusionString){
	std::size_t j;
	bool isInString = false;
	for (j=0; j<exclusionString.size() && !isInString; j++){
		if (exclusionString[j]==c){
			isInString = true;
		}
	}
	return isInString;
}

bool FrequencyTable::find(u_int8_t c) {
	map<u_int16_t, size_t>::iterator it;

	// Busco el caracter en la tabla
	it = table.find(c);

	// No se encontro el caracter
	if (it == table.end()) {
		return false;
	}
	frequency = it->second;
	return true;
}

// Incrementa la frecuencia del caracter o del ESC
// y actualiza el total.
void FrequencyTable::addCharacter(u_int8_t c) {
	map<u_int16_t, size_t>::iterator it;
	// Busco el caracter en la tabla
	it = table.find(c);

	if (it != table.end()) {
		it->second++;
	} else {
		u_int16_t data = c;
		data &= 0x00FF;
		table.insert(make_pair(data, 1));
		if (firstPass)
			firstPass = false;
		else {
			esc++;
			total++;
		}
	}

	// Se agrego una frecuencia al caracter o
	// se le asigno frecuencia 1 si no existia
	total++;
}

// Agrega a la cadena los caracteres de la tabla que no
// estaban en el string
void FrequencyTable::getStringExc(string& characters) {

	map<u_int16_t, size_t>::iterator it = table.begin();

	while (it != table.end()) {
		if (characters.find(it->first) == string::npos) {
			characters += it->first;
		}
		it++;
	}
}

// Aplico el mecanismo de exclusión a la tabla
void FrequencyTable::exc(const std::string& characters) {

	map<u_int16_t, size_t>::iterator it;

	for (std::size_t i = 0; i < characters.size(); i++) {
		it = table.find(characters[i]);

		// Si el caracter se encuentra en la tabla lo borro
		if (it != table.end()) {
			total -= it->second;
			table.erase(it);
		}
	}
}

// Devuelvo la cantidad de caracteres que hay en el mapa
size_t FrequencyTable::getNumberOfChars() {
	return table.size();
}

string FrequencyTable::show() {
	stringstream result;
	map<u_int16_t, size_t>::iterator it = table.begin();

	result << "TABLA: " << this->total << endl;

	while (it != table.end()) {
		result << "caracter "<< (int)it->first << " |  frecuencia " << it->second;
		result << endl;
		it++;
	}

	result << "caracter esc " << " |  frecuencia " << esc << endl;
	return result.str();
}

// Crea una tabla de frecuencias a partir de otra
void FrequencyTable::update(FrequencyTable *tableAux) {
	map<u_int16_t, size_t>::iterator it = tableAux->tableBegin();
	esc = tableAux->getFrequencyEsc();
	total = tableAux->getTotal();
	while (it != tableAux->tableEnd()) {
		table.insert(make_pair(it->first, it->second));
		it++;
	}
}

u_int32_t FrequencyTable::getNewBottom(){
	return this->bottom;
}

u_int32_t FrequencyTable::getNewTop(){
	return this->top;
}

void FrequencyTable::clear() {
	table.clear();
}
