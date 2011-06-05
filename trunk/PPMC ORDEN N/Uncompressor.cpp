/*
 * Uncompressor.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: luispaniagua
 */

#include "Uncompressor.h"


Uncompressor::Uncompressor(util::FileReader* r, util::FileWriter* w):Arithmetic(r, w),cola(){
	this->number = 0;
	this->bits_in_number = 0;
	this->state = STATE_OK;
}

void Uncompressor::uncompress(){
	bool end = false;
	while ( !end){
		int value = this->getNextChar();
		if (value == EOF){
			end = true;
		}
		else {
			this->writer->write((char)value);
		}
	}
}

int Uncompressor::getNextChar(){
	char c;
	bool end = false;
	//Cola vacia indica que no pudo resolver un character para los bits del numero dado, necesita mas
	while (cola.empty() && !end){
		c = this->reader->read();
		//end sera true, si el process da EOF
		end = this->solveNumber(c);
	}
	//si la cola no esta vacia, devuelve el caracter
	char result = cola.front();
	cola.pop();
	return result;
}

int Uncompressor::getCharFromModel(std::string exclusion){
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
		add_to_queue(result);
		return result;
	}
	else{
		while (get_bits_in_buffer() >0 && result < 0){
			drop_buffer_in_number();
			result = this->frequencyTable.findCharInLastModel(number, this->get_bits_in_number(), this->getBottom(), this->getTop(), exclusion);
			if (result == END_OF_FILE - 1){
				add_to_queue(EOF);
			}
			else if (result >= 0){
				add_to_queue(result);
			}
		}
		return result;
	}
}

void Uncompressor::uncompressorSetUpLimits(u_int32_t bottom, u_int32_t top){
	this->bottom = bottom;
	this->top = top;

	std::cout <<"antes de operar"<<std::endl;
	printf("hexa top: %x\n", this->top);
	printf("hexa bottom: %x\n", this->bottom);

	this->uncompressorSolveOverflow();

	this->uncompressorSolveUnderflow();

	std::cout <<"despues de operar"<<std::endl;
	printf("hexa top: %x\n", this->top);
	printf("hexa bottom: %x\n", this->bottom);

}

bool Uncompressor::solveLastModel(std::string exclusionChars, std::string firstContext){
	u_int32_t lastModelBottom = this->getBottom();
	u_int32_t lastModelTop = this->getTop();
	int result = this->getCharInLastModel(exclusionChars);
	if (result < 0){
		//Si entra aqui es po que no llego a definir con los bits que estan y tiene q seguir metiendo bits
		this->state = STATE_LAST_MODEL;
		this->firstContext = firstContext;
		this->exclusionChars = exclusionChars;
		return false;
	}
	this->state = STATE_OK;
	if (result == END_OF_FILE-exclusionChars.size()){

		//ALGO DEBE PASAR


		return true;
	}
	else {
		std::cout << (char)result <<" = 1/" << MAX - exclusionChars.size()<< std::endl;
		frequencyTable.setUpLimitsOnLastModel(lastModelBottom, lastModelTop, result, exclusionChars);
		contextSelector.add(result);
	}
	this->uncompressorSetUpLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());
	int i;
	//updateo todos los contextos que haya pasado
	for (i=firstContext.size(); i>=0; i--){
		if (i<0){
			break;
		}
		std::cout << "context " << firstContext << std::endl;
		models[i]->update(firstContext, result);
		if (firstContext.size()>0){
			firstContext.erase(firstContext.size()-1, 1);
		}
	}
	frequencyTable.getStringExc(exclusionChars);
	frequencyTable.clear();
	show();
	return true;
}

bool Uncompressor::solveNumber(u_int8_t a){
	this->buffer = a;
	this->bits_in_buffer = 8;
	bool hasMoreIterations = true;
	while (hasMoreIterations){
		if (this->state == STATE_LAST_MODEL){
			hasMoreIterations = solveLastModel(this->exclusionChars, this->firstContext);
			if (!hasMoreIterations){
				return false;
			}
		}
		bool found = false;
		std::string context = contextSelector.getContext();
		std::string firstContext = context;
		std::cout << "context \"" << context << "\""<<std::endl;
		std::size_t pos = context.size();
		std::size_t firstPos = pos;
		std::string exclusionCharacters;
		while (!found) {
			// cargo la tabla con el modelo actual
			frequencyTable.update (models[pos]->find(context));

			// Aplico mecanismo de exclusion
			frequencyTable.exc(exclusionCharacters);

			int result;
			result = this->getCharFromModel(exclusionCharacters);
			if (result < 0){
				//Si entra aqui es po que no llego a definir con los bits que estan y tiene q seguir metiendo bits
				this->state = STATE_NON_LAST_MODEL;
				this->currentContext = context;
				this->exclusionChars = exclusionCharacters;
				this->firstContext = firstContext;
				return false;
			}
			if (result != ESC){
				found = true;
				frequencyTable.find(result);
				std::cout << (char)result << " = " << frequencyTable.getFrequencyChar() << "/";
				std::cout << frequencyTable.getTotal() << std::endl;
				frequencyTable.setUpLimitsWithCharacter(this->getBottom(), this->getTop(), result);
				int i;
				for (i=firstPos; i>=pos; i--){
					if (i<0){
						break;
					}
					std::cout << "context " << firstContext << std::endl;
					models[i]->update(firstContext, result);
					if (firstContext.size()>0){
						firstContext.erase(firstContext.size()-1, 1);
					}
				}
				contextSelector.add(result);
			}
			else {
				std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
				std::cout << frequencyTable.getTotal()<< std::endl;
				frequencyTable.setUpLimitsWithEscape(this->getBottom(), this->getTop());
			}
			this->uncompressorSetUpLimits(frequencyTable.getNewBottom(), frequencyTable.getNewTop());

			//		models[pos]->update(context, c);

			if (pos == 0) {
				if (!found) {
					// Esta en el Modelo -1 porque no se encontro en el Modelo 0
					// Obtengo los caracteres a excluir del modelo 0
					frequencyTable.getStringExc(exclusionCharacters);
					// Aplico mecanismo de exclusion restando a MAX el size del string de
					// exclusion
					found = true;

					hasMoreIterations = solveLastModel(exclusionCharacters, firstContext);
					if (!hasMoreIterations){
						return false;
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
		show();

		// actualizo el contexto
	}
	return true;
}




Uncompressor::~Uncompressor() {

}
