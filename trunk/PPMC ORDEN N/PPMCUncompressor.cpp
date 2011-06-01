/*
 * PPMCUncompressor.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#include "PPMCUncompressor.h"
#include "Constants.h"

PPMCUncompressor::PPMCUncompressor(char * fileInput, char * fileOutput):Uncompressor(fileInput, fileOutput) {

}

bool PPMCUncompressor::process(char a){
	if (this->first_character){
		//this->table.set_context(a);
		add_to_queue(a);
		this->first_character = false;
	}
	else {
		set_buffer(a);
		bool end = false;
		int result = 0;
		while (!end){
			u_int64_t temporal_bottom;
			u_int64_t temporal_top;
			//result = this->calculador.founded_char(get_number(), get_bits_in_number(), get_bottom(), get_top(), &temporal_bottom, &temporal_top, this->table.get_table(), this->table.get_frequences());
			if (result >= 0){
				if (result < END_OF_FILE){
					set_bottom(temporal_bottom);
					set_top(temporal_top);
					u_int8_t character_table = result;
					add_to_queue(character_table);
					solve_overflow();
					solve_underflow();
					//this->table.refresh_table(character_table);
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
	}
	return false;
}

PPMCUncompressor::~PPMCUncompressor() {

}