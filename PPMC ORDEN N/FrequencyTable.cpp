#include "FrequencyTable.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable() {
	esc = 1;
	firstPass = true;
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

std::size_t FrequencyTable::getFrequencyChar() {
	return frequency;
}

std::size_t FrequencyTable::getFrequencyEsc() {
	return esc;
}

u_int32_t FrequencyTable::getTotal() {
	return total;
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

	frequency = it->second;

	return true;
}

// Incrementa la frecuencia del caracter o del ESC
// y actualiza el total.
void FrequencyTable::addCharacter(char c) {
	std::map<char, std::size_t>::iterator it;
	// Busco el caracter en la tabla
	it = table.find(c);


	if (it != table.end()) {
		it->second++;
	} else {
		table.insert(make_pair(c, 1));
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
void FrequencyTable::getStringExc(std::string& characters) {

	std::map<char, std::size_t>::iterator it = table.begin();

	while (it != table.end()) {
		if (characters.find(it->first) == std::string::npos) {
			characters += it->first;
		}
		it++;
	}
}

// Aplico el mecanismo de exclusión a la tabla
void FrequencyTable::exc(const std::string& characters) {

	std::map<char, std::size_t>::iterator it;

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
std::size_t FrequencyTable::getNumberOfChars() {
	return table.size();
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

// Crea una tabla de frecuencias a partir de otra
void FrequencyTable::update(FrequencyTable *tableAux) {
	std::map<char, std::size_t>::iterator it = tableAux->tableBegin();
	esc = tableAux->getFrequencyEsc();
	total = tableAux->getTotal();
	while (it != tableAux->tableEnd()) {
		table.insert(make_pair(it->first, it->second));
		it++;
	}
}

void FrequencyTable::setUpLimits(u_int32_t bottom, u_int32_t top, char character){
	std::map<char, std::size_t>::iterator it = table.begin();
	int localBottom = 0;
	int localTop = 0;
	bool found = false;
	while (it != table.end() && !found) {
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
	double pBottom = (double)localBottom/(double)this->total;
	double pTop = (double)localTop/(double)this->total;
	this->bottom = (top-bottom)*pBottom + bottom;
	this->top = (top-bottom)*pTop + bottom-1;
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
