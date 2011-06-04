/*
 * Uncompressor.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#include "Uncompressor.h"
#include "Constants.h"
#include <math.h>

Uncompressor::Uncompressor(util::FileReader* r, util::FileWriter* w):Arithmetic(r, w),cola(){
	this->number = 0;
	this->bits_in_number = 0;
}

void Uncompressor::uncompress(){
	bool end = false;
	while ( !end){
		int value = this->extract();
		if (value == EOF){
			end = true;
		}
		else {
			this->writer->write((char)value);
		}
	}
}

void Uncompressor::solve_overflow(){
	int i=31;
	int bitsOfOverflow=0;
	while (((bottom>>i) & 1)==((top>>i) & 1)){
		i--;
		bitsOfOverflow++;
	}
	if (bitsOfOverflow>0){
		bottom<<=bitsOfOverflow;
		unsigned long shift = pow (2,bitsOfOverflow)-1;
		top<<=bitsOfOverflow;
		top = (top | shift);
		top = (top & TOP);
		bottom = (bottom & TOP);
		remove_bits(bitsOfOverflow);
	}
}

void Uncompressor::solve_underflow(){
	int i = 29;
	int local_counter = 0;
	int first_bit_top = (top>>31) & 1;
	int first_bit_bottom = (bottom>>31) & 1;
	int bit_bottom = (bottom>>30) & 1;
	int bit_top = (top>>30) & 1;
	if (first_bit_bottom != first_bit_top){
		while ((first_bit_bottom != bit_bottom)&&(first_bit_top != bit_top)&&(bit_bottom != bit_top)){
			local_counter++;
			bit_bottom = (bottom>>i) & 1;
			bit_top = (top>>i) & 1;
			i--;
		}
	}
	if (local_counter>0){
		u_int64_t new_bottom = ((BYTE_128 & bottom)|((bottom<<local_counter) & BYTE_127));
		bottom = new_bottom;
		u_int64_t new_techo = ((BYTE_128 & top)|((top<<local_counter) & BYTE_127));
		top = new_techo;
		u_int64_t shift = pow (2,local_counter)-1;
		top = (top | shift);
		top = (top & TOP);
		bottom = (bottom & TOP);
		this->number = ((BYTE_128 & number)|((number<<local_counter) & BYTE_127));
		this->bits_in_number -= local_counter;
	}
}

int Uncompressor::extract(){
	char c;
	bool end = false;
	//Cola vacia indica que no pudo resolver un character para los bits del numero dado, necesita mas
	while (cola.empty() && !end){
		c = this->reader->read();
		//end sera true, si el process da EOF
		end = this->process(c);
	}
	//si la cola no esta vacia, devuelve el caracter
	char result = cola.front();
	cola.pop();
	return result;
}

void Uncompressor::drop_buffer_in_number(){
	u_int32_t aux = 0x00000000;
	char bit;
	int i = 7;
	int caracteres = this->bits_in_buffer;
	if (caracteres + this->bits_in_number >32){
		caracteres = 32-this->bits_in_number;
	}
	int k = 0;
	int l = this->bits_in_buffer;
	while ((k<caracteres) && (this->bits_in_buffer>0)){
		bit = (buffer>>i)&1;
		bit &= 0x01;
		aux<<=1;
		aux |= bit;
		this->bits_in_buffer--;
		buffer<<=1;
		k++;
	}
	int shift = 24 - this->bits_in_number + (8-l);
	if (shift>0)
		aux <<= shift;
	number |= aux;
	this->bits_in_number += caracteres;
}

void Uncompressor::remove_bits(int cant){
	this->number<<=cant;
	this->bits_in_number -= cant;
}


int Uncompressor::getChar(std::string exclusion){
	int result = this->frequencyTable.findChar(number, this->get_bits_in_number(), this->getBottom(), this->getTop(), exclusion);
	// si el resultado es >= 0 pudo resolver la consulta, sino probar si hay mas bits en el buffer
	if (result >= 0){
		if (result != ESC){
			add_to_queue(result);
		}
		return result;
	}
	else{
		while (get_bits_in_buffer() >0 && result < 0){
			drop_buffer_in_number();
			result = this->frequencyTable.findChar(number, this->get_bits_in_number(), this->getBottom(), this->getTop(), exclusion);
			if (result >= 0){
				if (result != ESC){
					add_to_queue(result);
				}
			}
		}
		return result;
	}
}

int Uncompressor::getCharInLastModel(std::string exclusion){

	int result = this->frequencyTable.findCharInLastModel(number, this->get_bits_in_number(), this->getBottom(), this->getTop(), exclusion);
	// si el resultado es >= 0 pudo resolver la consulta, sino probar si hay mas bits en el buffer
	if (result >= 0){
		if (result != ESC){
			add_to_queue(result);
		}
		return result;
	}
	else{
		while (get_bits_in_buffer() >0 && result < 0){
			drop_buffer_in_number();
			result = this->frequencyTable.findCharInLastModel(number, this->get_bits_in_number(), this->getBottom(), this->getTop(), exclusion);
			if (result >= 0){
				if (result != ESC){
					add_to_queue(result);
				}
			}
		}
		return result;
	}
}

bool Uncompressor::process(u_int8_t a){
	this->buffer = a;
	this->bits_in_buffer = 8;
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::size_t firstPos = pos;
	std::string exclusionCharacters;

	while (!found) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));

		// Aplico mecanismo de exclusion
		frequencyTable.exc(exclusionCharacters);

		int result;
		result = this->getChar(exclusionCharacters);
		if (result < 0){
			return false;
		}
		if (result != ESC){
			found = true;
			frequencyTable.setUpLimitsWithCharacter(this->getBottom(), this->getTop(), result);
			models[pos]->update(context, result);
		}
		else {
			std::cout << frequencyTable.getTotal()<< std::endl;
			frequencyTable.setUpLimitsWithEscape(this->getBottom(), this->getTop());
		}
		this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

		//		models[pos]->update(context, c);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
				found = true;
				u_int32_t lastModelBottom = this->getBottom();
				u_int32_t lastModelTop = this->getTop();
				result = this->getCharInLastModel(exclusionCharacters);
				if (result < 0){
					return false;
				}
				if (result == END_OF_FILE){
					return true;
				}
				else {
					frequencyTable.setUpLimitsOnLastModel(lastModelBottom, lastModelTop, result, exclusionCharacters);
				}
				this->setNewLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());
				std::size_t i;
				//updateo todos los contextos que haya pasado
				for (i=1; i<=firstPos; i++){
					models[i]->update(context, result);
				}
			}
		} else {
			pos--;
			context = context.substr(1);
		}

		// Agrego los posibles caracteres a excluir a la cadena de
		// caracteres de exclusion
		frequencyTable.getStringExc(exclusionCharacters);
		frequencyTable.clear();
	}
	return true;
}



Uncompressor::~Uncompressor() {

}
