// gcc -std=c99 1_2010_1P_carlos.c -c -Wall -pedantic -pedantic-errors


#include "indexada.h"
#include <malloc.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd_cliente = I_OPEN("clientes", READ);
	int fd_sucursal = I_OPEN("sucursales", READ);

	campo esquema_cliente[] = {
		{"cod_postal",UNSIGNED|INT,1},
		{"activo",CHAR,1},
		// otros campos...
		{0,0,0}
	};
	campo esquema_sucursal[]= {
		{"cod_postal",UNSIGNED|INT,1},
		// otros campos...
		{0,0,0}
	};
	campo esquema_clave[]= {
		{"cod_postal",UNSIGNED|INT,1},
		{0,0,0}
	};

	int size_cliente        = REG_SIZEOF(esquema_cliente);
	int size_sucursal       = REG_SIZEOF(esquema_sucursal);
	int size_clave          = REG_SIZEOF(esquema_clave);
	
	int drop_idx_cliente = 0;
	int drop_idx_sucursal = 0;
	
	void* reg_cliente  = malloc(size_cliente);
	void* reg_sucursal = malloc(size_sucursal);
	void* reg_clave    = malloc(size_clave);
	
	memset(reg_cliente,0,size_cliente);
	memset(reg_sucursal,0,size_sucursal);
	memset(reg_clave,0,size_clave);
	
	int idx_cliente = I_IS_INDEX(fd_cliente, esquema_clave);
	if ( RES_NO_EXISTE_INDICE == idx_cliente) {
		idx_cliente = I_ADD_INDEX(fd_cliente, esquema_clave);
		drop_idx_cliente = 1;
	}
	
	int idx_sucursal = I_IS_INDEX(fd_sucursal, esquema_clave);
	if ( RES_NO_EXISTE_INDICE == idx_sucursal) {
		idx_sucursal = I_ADD_INDEX(fd_sucursal, esquema_clave);
		drop_idx_sucursal = 1;
	}
	
	REG_SET(reg_clave, esquema_clave, "cod_postal", 0);
	int status_cliente = I_START(fd_cliente, idx_cliente, ">", &reg_clave);
	int status_sucursal = I_START(fd_sucursal, idx_sucursal, ">", &reg_clave);
	
	if (status_cliente == RES_OK && status_sucursal == RES_OK) {
		int cod_postal_cliente;
		int cod_postal_sucursal;
		char activo; 
		// otros campos;
		
		status_cliente  = I_READNEXT(fd_cliente, idx_cliente, reg_cliente);
		status_sucursal = I_READNEXT(fd_sucursal, idx_sucursal, reg_sucursal);

		while (status_cliente == RES_OK && status_sucursal == RES_OK) {

			REG_GET(reg_cliente, esquema_cliente, "activo", &activo);
			REG_GET(reg_cliente, esquema_cliente, "cod_postal", &cod_postal_cliente);
			REG_GET(reg_sucursal, esquema_sucursal, "cod_postal", &cod_postal_sucursal);
			if (activo == 'N') {
				status_cliente = I_READNEXT(fd_cliente, idx_cliente, reg_cliente);
			} else if (cod_postal_cliente > cod_postal_sucursal) {
				REG_GET(reg_sucursal, esquema_sucursal, "cod_postal", &cod_postal_sucursal);
			} else if (cod_postal_cliente < cod_postal_sucursal) {
				// imprimir cliente aclarando que no tiene sucursal
				status_cliente = I_READNEXT(fd_cliente, idx_cliente, reg_cliente);
			} else {
				// imprimir cliente con sucursal
			}
		}
		while (status_cliente == RES_OK ) {
			char activo; 
			REG_GET(reg_cliente, esquema_cliente, "activo", &activo);
			if (activo == 'S') {
				// imprimir cliente aclarando que no tiene sucursal
			}
			REG_GET(reg_cliente, esquema_cliente, "cod_postal", &cod_postal_cliente);

			status_cliente = I_READNEXT(fd_cliente, idx_cliente, reg_cliente);
		}
	}
	
	if (drop_idx_cliente) {
		I_DROP_INDEX(fd_cliente, idx_cliente);
	}
	
	if (drop_idx_sucursal) {
		I_DROP_INDEX(fd_sucursal, idx_sucursal);
	}
	
	I_CLOSE(fd_cliente);
	I_CLOSE(fd_sucursal);
	
	free(reg_cliente);
	free(reg_sucursal);
	
}