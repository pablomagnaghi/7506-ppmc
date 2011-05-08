// Archivo indexado clientes: codigo cliente, nombres, apellido, domicilio,
// codigo postal, activo
// donde activo es S o N
// Clave primaria: codigo cliente

// Archivo indexado sucursales: codigo sucursal, domicilio, codigo postal
// Clave primaria: codigo sucursal

// Generar listado que indique para cada cliente activo cual es la o las sucursales
// que le corresponden de acuerdo a su codigo postal

// AYUDA: es necesario crear un indice secundario por activo para evitar recorrer
// registros de clientes inactivos.
// Un cliente no tener ninguna sucursal asignada, una o varias.

#include <stdio.h>
#include <stdlib.h>

void listarClientesSucursal();

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

void listarClientesSucursal(){
	int fdClientes;
	int fdSucursales;

	fdClientes = I_OPEN("Clientes", READ);

	if (fdClientes == RES_NULL)
		return 1;

	fdSucursales = I_OPEN("Sucursales", READ);

	if (fdSucursales == RES_NULL)
		return 1;

	campo esqClientes[] = { {"codCliente", INT, 1}, {"nombres", CHAR, 20}, {"apellido", CHAR, 20}, {"domicilio", CHAR, 50},
	{"codPostal", INT, 1}, {"activo", CHAR, 1}, {0,0,0}};

	campo esqSucursales[] = { {"codSucursal", INT, 1}, {"domicilio", CHAR, 50}, {"codPostal", INT, 1}, {0,0,0}};

	void *regCliente;
	void *regSucursal;

	int tamanioReg;

	tamanioReg = REG_SIZEOF(esqClientes);
	regCliente = malloc(tamanioReg);

	tamanioReg = REG_SIZEOF(esqSucursales);
	regSucursales = malloc(tamanioReg);

	int result;

	campo esqClaveSecundariaSuc[] = {{"codPostal", INT, 1}, {0,0,0}};

	campo esqClaveSecundariaClientes[] = {{"activo", CHAR, 1}, {0,0,0}};

	int indexIdClientes, indexIdSuc, error = 0;

	indexIdClientes = I_IS_INDEX(fdClientes, esqClaveSecuendariaCliente);

	// indice secundario para clientes
	if (indexIdCliente == RES_NO_EXISTE_INDICE) {
		result = I_ADD_INDEX(fdClientes, esqClaveSecundariaClientes);
		if (result == RES_ERROR)
			error = 1;
	}

	indexIdSuc = I_IS_INDEX(fdSucursales, esqClaveSecundariaSuc);

	// indice secundario para sucursales
	if (indexIdSuc == RES_NO_EXISTE_INDICE) {
		result = I_ADD_INDEX(fdSucursales, esqClaveSecundariaSuc);
		if (result == RES_ERROR)
			error = 1;
	}

	if (!error) {
		REG_SET(regCliente, esqClientes, "activo", 'S');
		result = I_START(fdClientes, indexIdCliente, "=", regCliente);

		if (result == RES_ERROR)
			error = 1;

		if (result == RES_NO_EXISTE)
			error = 2; // no hay registro que cumpla la condicion deseada

		result = I_READ_NEXT(fdClientes, indexIdCliente, regCliente);

		while ((result != RES_EOF) && (result != RES_ERROR) && (!error)) {
			int codCliente;
			result = REG_GET(regCliente, esqClientes, "codCliente", &codCliente);
			if (result != RES_OK)
				return 1;

			result = I_START(fdSucursales, indexIdSuc, "=", regCliente);

			if (result == RES_NO_EXISTE)
				printf("%d no cuenta con sucursal asignada", codCliente);
			else
			{
				result = I_READ_NEXT(fdSucursales, indexIdSuc, regSucursal);
				while ((result != RES_EOF) && (result != RES_ERROR)) {
					int codSucursal;
					result = REG_GET(regSucursal, esqSucursales, "codSucursal", &codSucursal);
					if (result != RES_OK)
						error = 1;
					printf("%d %d \n", codCliente, codSucursal);
					result = I_READ_NEXT(fdSucursales, indexIdSuc, regSucursal);
				}
				if (result == RES_ERROR)
					error = 1;
			}

			result = I_READ_NEXT(fdClientes, indexIdCliente, regCliente);
		}
	}

	if (result == RES_ERROR)
		error = 1;

	free (regCliente);
	free (regSucursal);

	result = I_CLOSE(fdClientes);

	if (result != RES_OK)
		error = 1;

	result = I_CLOSE(fdSucursales);

	if (result != RES_OK)
		error = 1;

	return error;
}
