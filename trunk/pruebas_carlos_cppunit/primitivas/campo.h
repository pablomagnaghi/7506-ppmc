#ifndef _campo_h_
#define _campo_h_

#include "constantes.h"

typedef struct {
	const char* nombre;
	int tipo;
	int longitud;
} campo;

#define CHAR       1
#define INT        2
#define LONG       3
#define FLOAT      4
#define DOUBLE     5
#define UNSIGNED 0X80

int REG_SIZEOF(const campo* esquema);
int REG_SET(void* buffer, const campo* esquema, const char* desc, ...);
int REG_GET(const void* buffer, const campo* esquema, const char* desc, ...);

#endif // _campo_h_