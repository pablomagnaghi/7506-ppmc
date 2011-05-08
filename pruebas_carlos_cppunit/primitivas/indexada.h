#ifndef _indexada_h_
#define _indexada_h_

#include "constantes.h"
#include "campo.h"

int I_CREATE(const char* nombre_fisico, const campo* registro, const campo* clave_primaria);
int I_OPEN(const char* nombre_fisico, int modo);
int I_CLOSE(int handler);
int I_ADD_INDEX(int handler, const campo* clave);
int I_DROP_INDEX(int handler, int index_id);
int I_IS_INDEX(int handler, const campo* clave);
int I_START(int handler, int index_id, char* operador, const void* valor_referencia);
int I_READ(int handler, void* registro);
int I_READNEXT(int handler, int index_id, void* registro);


#endif // _indexada_h_