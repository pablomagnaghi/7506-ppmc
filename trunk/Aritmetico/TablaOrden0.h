/*
 * TablaOrden0.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef TABLAORDEN0_H_
#define TABLAORDEN0_H_

#include <algorithm>
#include "Constants.h"

class TablaOrden0 {
private:
	u_int32_t frequences[NUMBER_OF_CHARACTERS];
	int total_frequences;
public:
	TablaOrden0();
	u_int32_t* get_table();

	int get_frequences(){
		return total_frequences;
	}

	void refresh_table(u_int16_t a);
	virtual ~TablaOrden0();
};

#endif /* TABLAORDEN0_H_ */
