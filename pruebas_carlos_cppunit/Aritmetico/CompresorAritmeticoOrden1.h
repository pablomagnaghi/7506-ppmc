/*
 * CompresorAritmeticoOrden1.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef COMPRESORARITMETICOORDEN1_H_
#define COMPRESORARITMETICOORDEN1_H_

#include "TablaOrden1.h"
#include "CalculadorTabla.h"
#include "CompresorAritmetico.h"

class CompresorAritmeticoOrden1: public CompresorAritmetico {
private:
	TablaOrden1 table;
	CalculadorTabla calculador;
	bool first_character;
public:
	CompresorAritmeticoOrden1(char * nombre);
	void process(u_int16_t a);
	virtual ~CompresorAritmeticoOrden1();
};

#endif /* COMPRESORARITMETICOORDEN1_H_ */
