/*
 * CompresorAritmeticoOrden0.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef COMPRESORARITMETICOORDEN0_H_
#define COMPRESORARITMETICOORDEN0_H_

#include "TablaOrden0.h"
#include "CalculadorTabla.h"
#include "CompresorAritmetico.h"

class CompresorAritmeticoOrden0 : public CompresorAritmetico{
private:
	TablaOrden0 table;
	CalculadorTabla calculador;
public:
	CompresorAritmeticoOrden0(char * nombre);
	void process(u_int16_t a);
	virtual ~CompresorAritmeticoOrden0();
};

#endif /* COMPRESORARITMETICOORDEN0_H_ */
