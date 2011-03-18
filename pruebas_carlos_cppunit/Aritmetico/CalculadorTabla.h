/*
 * CalculadorTabla.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef CALCULADORTABLA_H_
#define CALCULADORTABLA_H_

#include <algorithm>
#include "Constants.h"

class CalculadorTabla {
public:
	CalculadorTabla();
	bool get_ends (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* new_top, u_int32_t table[NUMBER_OF_CHARACTERS], int total_frequences);
	int founded_char (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporal_bottom, u_int64_t * temporal_top, u_int32_t table[NUMBER_OF_CHARACTERS], int total_frequences);
	virtual ~CalculadorTabla();
};

#endif /* CALCULADORTABLA_H_ */
