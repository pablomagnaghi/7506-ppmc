/*
 * TablaOrden1.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef TABLAORDEN1_H_
#define TABLAORDEN1_H_

#include <algorithm>
#include "Constants.h"

class TablaOrden1 {
private:
	u_int32_t frequences[NUMBER_OF_CHARACTERS][NUMBER_OF_CHARACTERS];
	int total_frequences[NUMBER_OF_CHARACTERS];
	u_int16_t ctx;
public:
	TablaOrden1();
	void set_context(u_int16_t a);
	void refresh_table(u_int16_t a);
	u_int32_t* get_table();
	int get_frequences(){
		return total_frequences[ctx];
	}

	virtual ~TablaOrden1();
};

#endif /* TABLAORDEN1_H_ */
