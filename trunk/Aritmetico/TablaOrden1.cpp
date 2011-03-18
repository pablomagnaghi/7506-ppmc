/*
 * TablaOrden1.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "TablaOrden1.h"
#include "Constants.h"

TablaOrden1::TablaOrden1() {
	int i;
	int j;
	for (i=0; i<NUMBER_OF_CHARACTERS; i++){
		for (j=0; j<NUMBER_OF_CHARACTERS; j++){
			this->frequences[i][j]=1;
		}
		this->total_frequences[i] = NUMBER_OF_CHARACTERS;
	}
}

void TablaOrden1::refresh_table(u_int16_t a){


		a&= 0x00FF;


	this->frequences[ctx][a]++;
	this->total_frequences[ctx]++;
	this->ctx = a;
}

void TablaOrden1::set_context(u_int16_t a){
	(a)&= 0x00FF;
	this->ctx = a;
}

u_int32_t* TablaOrden1::get_table(){
	return this->frequences[ctx];
}

TablaOrden1::~TablaOrden1() {
}
