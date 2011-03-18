/*
 * CompresorAritmeticoOrden1.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "CompresorAritmeticoOrden1.h"

CompresorAritmeticoOrden1::CompresorAritmeticoOrden1(char *nombre): CompresorAritmetico(nombre) {
	this->first_character = true;
}

void CompresorAritmeticoOrden1::process(u_int16_t a){
	if (a!=END_OF_FILE)
		a &= 0x00FF;
	if (first_character){
		this->table.set_context(a);
		this->first_character = false;
		put_byte_in_buffer(a);
	}
	else {
		u_int64_t actual_bottom = get_bottom();
		u_int64_t actual_top = get_top();
		u_int64_t temporal_bottom;
		u_int64_t temporal_top;
		bool eofile;
		eofile = this->calculador.get_ends(a, actual_bottom, actual_top, &temporal_bottom, &temporal_top, this->table.get_table(), this->table.get_frequences());
		set_bottom(temporal_bottom);
		set_top(temporal_top);
		solve_overflow();
		if (!eofile){
			solve_underflow();
		}
		table.refresh_table(a);
	}
	if (a==END_OF_FILE)
		clean_buffer();
}

CompresorAritmeticoOrden1::~CompresorAritmeticoOrden1() {
	process(END_OF_FILE);
}
