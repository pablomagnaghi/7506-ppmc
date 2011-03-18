/*
 * DescompresorAritmeticoOrden1.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef DESCOMPRESORARITMETICOORDEN1_H_
#define DESCOMPRESORARITMETICOORDEN1_H_

#include "DescompresorAritmetico.h"
#include "TablaOrden1.h"
#include "CalculadorTabla.h"

class DescompresorAritmeticoOrden1: public DescompresorAritmetico {
private:
	TablaOrden1 table;
	CalculadorTabla calculador;
	bool first_character;
public:
	DescompresorAritmeticoOrden1(char * entrada);
	bool process (char a);
	virtual ~DescompresorAritmeticoOrden1();
};

#endif /* DESCOMPRESORARITMETICOORDEN1_H_ */
