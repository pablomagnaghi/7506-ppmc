/*
 * TablaOrden0.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "TablaOrden0.h"

TablaOrden0::TablaOrden0() {
	int i;
	for (i=0; i<NUMBER_OF_CHARACTERS; i++)
		this->frequences[i]=1;
	this->total_frequences = NUMBER_OF_CHARACTERS;
}

u_int32_t* TablaOrden0::get_table(){
	return this->frequences;
}

void TablaOrden0::refresh_table(u_int16_t a){
	this->total_frequences++;
	this->frequences[a]++;
}

TablaOrden0::~TablaOrden0() {

}
