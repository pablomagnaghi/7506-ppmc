#include "TableCalculator.h"

using namespace ppmc;
using namespace std;

TableCalculator::TableCalculator() {
	// TODO Auto-generated constructor stub

}

bool TableCalculator::isInString(u_int8_t c, string exclusionString){
	size_t j;
	bool isInString = false;
	for (j=0; j<exclusionString.size() && !isInString; j++){
		u_int8_t character = exclusionString[j];
		if (character==c){
			isInString = true;
		}
	}
	return isInString;
}

void TableCalculator::getEnds(u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t *newBottom, u_int64_t *newTop, FrequencyTable table){
	u_int64_t range = top - bottom + 1;
	double characterTop = 0;
	double temporalTop = 0;
	double pi = 0;
	double pb=0;
	*newBottom = bottom;
	int i = 0;
	//total va a ser el total de las frecuancias menos el tamanio del string
	int totalFrequences = table.getTotal();
	bool found = false;
	map<u_int16_t, size_t>::iterator it = table.tableBegin();
	while (it != table.tableEnd() && !found) {
		characterTop += it->second;
		pi = characterTop / totalFrequences;
		*newTop = floor(bottom + range*pi - 1);
		if ((i-1)>=0){
			temporalTop = characterTop - it->second;
			pb = temporalTop/totalFrequences;
			*newBottom = ceil(bottom + range*pb);
		}
		if (it->first == a){
			found = true;
		}
		i++;
		it++;
	}
	if (!found){
		//hay un escape
		pb = characterTop/totalFrequences;
		*newTop = floor(bottom + range*1 - 1);
		*newBottom = ceil(bottom + range*pb);
	}
}

bool TableCalculator::getEndsLastModel (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * newBottom, u_int64_t* newTop, string ex){
	bool result = false;
	u_int64_t range = top - bottom + 1;
	double characterTop = 0;
	double temporalTop = 0;
	double pi = 0;
	double pb=0;
	*newBottom = bottom;
	int i;
	int totalFrequences = 257 - ex.size();
	for (i=0; i<=a; i++){
		if (isInString(i, ex)){
			continue;
		}
		characterTop+= 1;
		pi = characterTop / totalFrequences;
		*newTop = floor(bottom + range*pi - 1);
		if ((i-1)>=0){
			temporalTop = characterTop - 1;
			pb = temporalTop/totalFrequences;
			*newBottom = ceil(bottom + range*pb);
		}
	}

	if (i==NUMBER_OF_CHARACTERS)
		result = true;
	return result;
}

int TableCalculator::foundedCharLastModel(u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t *temporalTop, string ex){
	int result = -1;
	int i = 0;
	u_int64_t partialBottom = bottom;
	u_int64_t range = top - bottom + 1;
	double frequences = 0;
	u_int64_t partialTop;
	double pi;
	bool founded = false;
	int totalFrequences = 257 - ex.size();
	if (size==32){
		// todo verrr
		while ((i<NUMBER_OF_CHARACTERS)&&(!founded)){
			if (isInString(i, ex)){
				i++;
				continue;
			}
			frequences += 1;
			pi = frequences/totalFrequences;
			partialTop = floor(range*pi + bottom - 1);
			if ((partialBottom<=number)&&(partialTop>=number)){
				result = i;
				founded = true;
			}
			*temporalBottom = partialBottom;
			*temporalTop = partialTop;
			partialBottom = ceil (range*pi + bottom);
			i++;
		}

		// todo Esto esta agregado solo para probar

		if (!founded){
			result = END_OF_FILE;
		}
	}
	return result;
}

int TableCalculator::foundedCharModel(u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t *temporalTop, FrequencyTable table){
	int result = -1;
	int i = 0;
	u_int64_t partialBottom = bottom;
	u_int64_t range = top - bottom + 1;
	double frequences = 0;
	u_int64_t partialTop;
	double pi;
	bool founded = false;
	int totalFrequences = table.getTotal();
	map<u_int16_t, size_t>::iterator it = table.tableBegin();

	if (size==32){
		while (it != table.tableEnd() && !founded){
			frequences += it->second;
			pi = frequences/totalFrequences;
			partialTop = floor(range*pi + bottom - 1);
			if ((partialBottom<=number)&&(partialTop>=number)){
				result = it->first;
				result &= 0x00FF;
				founded = true;
			}
			*temporalBottom = partialBottom;
			*temporalTop = partialTop;
			partialBottom = ceil (range*pi + bottom);
			i++;
			it++;
		}
//		if (i == (total_frequences-table.getFrequencyEsc()) || total_frequences == table.getFrequencyEsc()){
//			result = ESC;
//			double pb = frequences/total_frequences;
//			*temporal_top = floor(bottom + range*1 - 1);
//			*temporal_bottom = ceil(bottom + range*pb);
//		}
		if (!founded){
			result = ESC;
			double pb = frequences/totalFrequences;
			*temporalTop = floor(bottom + range*1 - 1);
			*temporalBottom = ceil(bottom + range*pb);
		}
	}
	return result;
}

TableCalculator::~TableCalculator() {

}
