/*
 * DescompresorAritmeticoOrden0.h
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#ifndef DESCOMPRESORARITMETICOORDEN0_H_
#define DESCOMPRESORARITMETICOORDEN0_H_

#include "DescompresorAritmetico.h"
#include "TablaOrden0.h"
#include "CalculadorTabla.h"

class DescompresorAritmeticoOrden0: public DescompresorAritmetico {
private:
	TablaOrden0 table;
	CalculadorTabla calculador;
public:
	DescompresorAritmeticoOrden0(char * entrada);
	bool process (char a);
	virtual ~DescompresorAritmeticoOrden0();
};

#endif /* DESCOMPRESORARITMETICOORDEN0_H_ */
