#include "FrequencyTable.h"
#include "Constants.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable() {
	esc = 1;
	firstPass = true;
	frequency = 1;
	this->total = 1;
	this->top = 0;
	this->bottom = 0;
}

FrequencyTable::~FrequencyTable() {}

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

int FrequencyTable::findChar(u_int32_t number, u_int8_t size, u_int32_t bottom, u_int32_t top, const std::string& exclusionString){
	int result = -1;
	u_int8_t i = 0;
	u_int32_t localBottom = bottom;
	u_int32_t localTop = bottom;
	u_int32_t delta   = top - bottom;
	u_int32_t temporal_bottom_freq = 0;
	u_int32_t frequence = 0;
	u_int32_t total_char = this->total-esc;
	std::map<char, std::size_t>::iterator it = table.begin();
	bool founded = false;
	if (size==32){
		if (total_char==0){
			return ESC;
		}
		while ((i<total_char)&&(!founded)){
			if (isInString(it->first, exclusionString)){
				continue;
			}
			frequence += it->second;
			double pBottom = (double)temporal_bottom_freq / (double)total;
			double pTop = (double)frequence / (double)total;
			localBottom = delta * pBottom;
			localBottom += bottom;

			localTop = delta*pTop;
			localTop += bottom-1;
			if ((localBottom<=number)&&(localTop>=number)){
				result = it->first;
				founded = true;
			}
			temporal_bottom_freq = frequence;
			i++;
			it++;
		}
		if (!founded){
			return ESC;
		}
	}
	return result;
}

int FrequencyTable::findCharInLastModel(u_int32_t number, u_int8_t size, u_int32_t bottom, u_int32_t top, const std::string& exclusionString){

	int result = -1;
	int i = 0;
	u_int32_t total = 257 - exclusionString.size();
	u_int32_t localBottom = bottom;
	u_int32_t localTop = 0;
	u_int32_t temporal_bottom_freq = 0;
	u_int32_t delta   = top - bottom;
	u_int32_t frequence = 0;

	bool founded = false;
	if (size==32){
		while ((i<=NUMBER_OF_CHARACTERS)&&(!founded)){
			if (isInString(i, exclusionString)){
				i++;
				continue;
			}
			frequence += 1;
			double pBottom = (double)temporal_bottom_freq/ (double)total;
			double pTop = (double)frequence / (double)total;
			localBottom = delta * pBottom;
			localBottom += bottom;

			localTop = delta*pTop;
			localTop += bottom-1;
			if ((localBottom<=number)&&(localTop>=number)){
				result = i;
				founded = true;
			}
			temporal_bottom_freq = frequence;
			i++;
		}
	}
	return result;
}

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
		std::cout << "caracter "<< it->first << " |  frecuencia " << it->second;
		std::cout << std::endl;
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

void FrequencyTable::setUpLimitsOnLastModel(u_int32_t bottom, u_int32_t top, u_int8_t c, const std::string& exclusionString){
	u_int32_t value = 0;
	std::cout << "char: " << (int)c << std::endl;
	for (std::size_t i = 0; i <exclusionString.size(); i++) {
		if (exclusionString[i] < c){
			value++;
		}
	}
	u_int32_t total = 257 - exclusionString.size();
	u_int32_t localBottom = c - value;
	u_int32_t localTop = localBottom + 1;
	u_int32_t delta   = top - bottom;

	double pBottom = (double)localBottom / (double)total;
	double pTop = (double)localTop / (double)total;
	this->bottom = delta * pBottom;
	this->bottom += bottom;
	this->top = delta * pTop;
	this->top += bottom-1;
}

void FrequencyTable::setUpLimitsWithEOF(u_int32_t bottom, u_int32_t top, const std::string& exclusionString){
	u_int32_t total = 257 - exclusionString.size();
	u_int32_t localTop = total;
	u_int32_t localBottom = total - 1;
	u_int32_t delta   = top - bottom;

	double pBottom = (double)localBottom / (double)total;
	double pTop = (double)localTop / (double)total;
	this->bottom = delta * pBottom;
	this->bottom += bottom;
	this->top = delta * pTop;
	this->top += bottom;
}


void FrequencyTable::setUpLimitsWithCharacter(u_int32_t bottom, u_int32_t top
		, u_int8_t character){
	u_int32_t value = this->getPreviousFrequences(character);
	std::cout << "char: " << (int)character << std::endl;
	calculateValues(bottom, top, value);
}

void FrequencyTable::setUpLimitsWithEscape(u_int32_t bottom, u_int32_t top){
	u_int32_t value = this->getPreviousFrequencesForEscape();
	calculateValues(bottom, top, value);
}

void FrequencyTable::calculateValues(u_int32_t bottom, u_int32_t top, u_int32_t lowerFrequency){
	u_int32_t delta   = top - bottom;

	double pBottom = (double)lowerFrequency / (double)this->total;
	double pTop = (double)(lowerFrequency + frequency) / (double)this->total;
	this->bottom = delta * pBottom;
	this->bottom += bottom;
	this->top = delta * pTop;
	this->top += bottom;
}

u_int32_t FrequencyTable::getPreviousFrequences(u_int8_t c){
	std::map<char, std::size_t>::iterator it = table.begin();
	u_int32_t value = 0;
	bool found = false;
	while (it != table.end() && !found) {
		if (it->first!=c){
			value+= it->second;
			it++;
		} else {
			found = true;
		}
	}
	return value;
}

u_int32_t FrequencyTable::getPreviousFrequencesForEscape(){
	return this->total-this->esc;
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
