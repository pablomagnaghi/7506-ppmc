#ifndef _secuencial_h_
#define _secuencial_h_

#include "constantes.h"
#include "campo.h"

int S_CREATE(const char*, nombre_fisico);
int S_OPEN(const char* nombre_fisico, int modo);
int S_CLOSE(int handler);
int S_READ(int handler, void* reg);
int S_WRITE(int handler, cont void* reg, unsigned long cantidad);

#endif // _secuencial_h_