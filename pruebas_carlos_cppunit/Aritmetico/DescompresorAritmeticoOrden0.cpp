/*
 * DescompresorAritmeticoOrden0.cpp
 *
 *  Created on: 23/05/2010
 *      Author: luis
 */

#include "DescompresorAritmeticoOrden0.h"

DescompresorAritmeticoOrden0::DescompresorAritmeticoOrden0(char * entrada):DescompresorAritmetico(entrada) {

}

bool DescompresorAritmeticoOrden0::process(char a){
	set_buffer(a);
	bool end = false;
	int result;
	while (!end){
		u_int64_t actual_bottom = get_bottom();
		u_int64_t actual_top = get_top();
		u_int64_t temporal_bottom;
		u_int64_t temporal_top;
		result = this->calculador.founded_char(get_number(), get_bits_in_number(), actual_bottom, actual_top, &temporal_bottom, &temporal_top, this->table.get_table(), this->table.get_frequences());
		if (result >= 0){
			if (result < END_OF_FILE){
				set_bottom(temporal_bottom);
				set_top(temporal_top);
				u_int8_t character_table = result;
				add_to_queue(character_table);
				solve_overflow();
				solve_underflow();
				this->table.refresh_table(character_table);
			}
			else{
				return true;
			}
		}
		else{
			if (get_bits_in_buffer() >0){
				drop_buffer_in_number();
			}
			else{
				end = true;
			}
		}
	}
	return false;
}

DescompresorAritmeticoOrden0::~DescompresorAritmeticoOrden0() {

}
