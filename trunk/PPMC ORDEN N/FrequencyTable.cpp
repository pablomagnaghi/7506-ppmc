#include "FrequencyTable.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable() {
	esc = 1;
	primerPasada = true;
	this->total = 1;
	this->top = 0;
	this->bottom = 0;
}

FrequencyTable::~FrequencyTable() {

}

std::map<char, std::size_t>::iterator FrequencyTable::tableBegin() {
  return table.begin();
}

std::map<char, std::size_t>::iterator FrequencyTable::tableEnd() {
  return table.end();
}

std::size_t FrequencyTable::getFrecuenciaChar() {
	return frecuencia;
}

std::size_t FrequencyTable::getFrecuenciaEsc() {
	return esc;
}

// Si encuentra la frecuencia la guarda y devuelve true
// en caso contrario devuelve true
bool FrequencyTable::find(char c) {
	std::map<char, std::size_t>::iterator it;

	// Busco el caracter en la tabla
	it = table.find(c);

	// No se encontro el caracter
	if (it == table.end()) {
		return false;
	}

	frecuencia = it->second;

	return true;
}

// Incrementa la frecuencia del caracter
void FrequencyTable::addCharacter(char c) {
	std::map<char, std::size_t>::iterator it;
	// Busco el caracter en la tabla
	it = table.find(c);

	// Si encontro el caracter
	if (it != table.end()) {
		it->second++;
		total++;
	} else {
		table.insert(make_pair(c, 1));
		if (primerPasada)
			primerPasada = false;
		else
			esc++;
		total++;
	}
}

// Agrega a la cadena los caracteres de la tabla que no
// estaban en el string
void FrequencyTable::getStringExc(std::string& characters) {

	std::map<char, std::size_t>::iterator it = table.begin();

	while (it != table.end()) {
		if (characters.find(it->first) == std::string::npos) {
			characters += it->first;
		}
		it++;
	}
}

void FrequencyTable::show() {
	std::map<char, std::size_t>::iterator it = table.begin();

	std::cout << "TABLA" << std::endl;

	while (it != table.end()) {
		std::cout << "caracter "<< it->first << " |  frecuencia " << it->second << std::endl;
		it++;
	}

	std::cout << "caracter esc " << " |  frecuencia " << esc << std::endl;
}

// Cre una tabla de frecuencias a partir de otra
void FrequencyTable::update(FrequencyTable *tableAux) {
	std::map<char, std::size_t>::iterator it = tableAux->tableBegin();

	while (it != tableAux->tableEnd()) {
		table.insert(make_pair(it->first, it->second));
		it++;
	}
}

void FrequencyTable::setUpLimits(u_int64_t bottom, u_int64_t top, char character){
	std::map<char, std::size_t>::iterator it = table.begin();
	int localBottom = 0;
	int localTop = 0;
	bool found = false;
	while (it != table.end()) {
		if (it->first!=character){
			localBottom+= it->second;
			it++;
		}
		else {
			found = true;
		}
	}
	if (found){
		localTop = localBottom + it->second;
	}
	else {
		localTop = localBottom + this->esc;
	}
	double pBottom = localBottom/this->total;
	double pTop = localTop/this->total;
	this->bottom = (top-bottom)*pBottom + bottom;
	this->top = (top-bottom)*pTop + bottom-1;
}


u_int64_t FrequencyTable::getNewBottom(){
	return this->bottom;
}

u_int64_t FrequencyTable::getNewTop(){
	return this->top;
}

void FrequencyTable::clear() {
	table.clear();
}
