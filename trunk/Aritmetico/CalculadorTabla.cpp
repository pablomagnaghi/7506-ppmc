/*
 * CalculadorTabla.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "CalculadorTabla.h"
#include <math.h>

CalculadorTabla::CalculadorTabla() {

}


bool CalculadorTabla::get_ends(u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t *new_bottom, u_int64_t *new_top, u_int32_t table[NUMBER_OF_CHARACTERS], int total_frequences){
	bool result = false;
	u_int64_t range = top - bottom + 1;
	double character_top = 0;
	double temporal_top = 0;
	double pi = 0;
	double pb=0;
	*new_bottom = bottom;
	int i;
	for (i=0; i<=a; i++){
		character_top+= table[i];
		pi = character_top / total_frequences;
		*new_top = floor(bottom + range*pi - 1);
		if ((i-1)>=0){
			temporal_top = character_top - table[i];
			pb = temporal_top/total_frequences;
			*new_bottom = ceil(bottom + range*pb);
		}
	}
	if (i==NUMBER_OF_CHARACTERS)
		result = true;
	return result;
}

int CalculadorTabla::founded_char(u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporal_bottom, u_int64_t *temporal_top, u_int32_t table[NUMBER_OF_CHARACTERS], int total_frequences){
	int result = -1;
	int i = 0;
	u_int64_t partial_bottom = bottom;
	u_int64_t range = top - bottom + 1;
	double frequences = 0;
	u_int64_t partial_top;
	double pi;
	bool founded = false;
	if (size==32){
		while ((i<NUMBER_OF_CHARACTERS)&&(!founded)){
			frequences += table[i];
			pi = frequences/total_frequences;
			partial_top = floor(range*pi + bottom - 1);
			if ((partial_bottom<=number)&&(partial_top>=number)){
				result = i;
				founded = true;
			}
			*temporal_bottom = partial_bottom;
			*temporal_top = partial_top;
			partial_bottom = ceil (range*pi + bottom);
			i++;
		}
	}
	return result;
}

CalculadorTabla::~CalculadorTabla() {

}
