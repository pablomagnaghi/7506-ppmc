#include "PPMCUncompressor.h"
#include "PPMCCompressor.h"
#include "Constants.h"
#include "TableCalculator.h"

using namespace ppmc;
using namespace std;

PPMCUncompressor::PPMCUncompressor(FileReader* r, FileWriter* w):ArithmeticDescompressor(r,w) {
	for (size_t i=0; i<(ORDEN + 1);i++) {
		models.push_back(new Model());
	}
	this->state = STATE_OK;
}

void PPMCUncompressor::show(){
	for (int i = ORDEN; i > -1; i--) {
		if (models[i]->getSize()) {
			cout << "Modelo " << i << ": " << endl;
			cout << models[i]->show();
		}
	}
}

// Este solve last model es el que puede devolver true ya que va a definir si el caracter es el EOF o no

bool PPMCUncompressor::solveLastModel(string ex, string firstCtx, int * moreIterations){
	bool end = false;
	int result;

	u_int64_t temporalBottom;
	u_int64_t temporalTop;
	TableCalculator calculator;

	while (!end){
		//busco el char con el numero actual y los techos y pisos
		//esta funcion si es >= a 0 tiene un resultado valudo, sino tiene que mandar mas biuts
		result = calculator.foundedCharLastModel(getNumber(), getBitsInNumber(), getBottom(), getTop(), &temporalBottom, &temporalTop, ex);
		//int result = this->getCharInLastModel(exclusionChars);
		if (result < 0){
			//Si entra aqui es po que no llego a definir con los bits que estan y tiene q seguir metiendo bits

			if (getBitsInBuffer() >0){
				dropBufferInNumber();
			}
			else{
				this->state = STATE_LAST_MODEL;
				this->firstContext = firstCtx;
				this->exclusionChars = ex;
				*moreIterations = 0;
				end = true;
			}
		}
		else {
			this->state = STATE_OK;
			setBottom(temporalBottom);
			setTop(temporalTop);
			u_int16_t characterTable = result;
			addToQueue(characterTable);
#ifdef VERBOSE_ARITHMETIC
			printf ("top antes de operar: %x\n", temporalTop);
			printf ("bottom antes de operar: %x\n", temporalBottom);
#endif
			solveOverflow();
#ifdef VERBOSE_ARITHMETIC
			printf ("top dsp de over: %x\n", getTop());
			printf ("bottom dsp de over: %x\n", getBottom());
#endif
			solveUnderflow();
#ifdef VERBOSE_ARITHMETIC
			printf ("top dsp de under: %x\n", getTop());
			printf ("bottom dsp de under: %x\n", getBottom());
#endif
			if (result == END_OF_FILE){
				return true;
			}
			int i;
			//updateo todos los contextos que haya pasado
			for (i=firstCtx.size(); i>=0; i--){
				if (i<0){
					break;
				}
				models[i]->update(firstCtx, characterTable);
				if (firstCtx.size()>0){
					firstCtx = firstCtx.substr(1);
				}
			}
			frequencyTable.getStringExc(exclusionChars);
			frequencyTable.clear();
#ifdef VERBOSE_MODELS
			show();
#endif
			contextSelector.add(characterTable);
			*moreIterations = 1;
			end = true;
		}
	}
	return false;
}

// Devuelve siempre false, excepto si descomprime el EOF

bool PPMCUncompressor::process(char a){
	setBuffer(a);
	int hasMoreIterations = 1;
	size_t size = reader->getSizeFromHeader();
	while (hasMoreIterations){
		if (this->state == STATE_LAST_MODEL){
			// Retorna true si es el end of file, si no consiguio deducir el caracter, hasMoreIt se pone en 1

			bool value = solveLastModel(this->exclusionChars, this->firstContext, &hasMoreIterations);
			if (value){
				return true;
			}
			if (!hasMoreIterations){
				return false;
			}
		}
		bool found = false;
		string context = contextSelector.getContext();

		string firstContext = context;
		string exclusionCharacters;

		if (state == STATE_NON_LAST_MODEL){
			context = this->currentContext;
			firstContext = this->firstContext;
			exclusionCharacters = this->exclusionChars;
		}
		size_t pos = context.size();
		size_t firstPos = firstContext.size();

		TableCalculator calculator;
		u_int64_t temporalBottom;
		u_int64_t temporalTop;
		while (!found) {
			// cargo la tabla con el modelo actual
			frequencyTable.update (models[pos]->find(context));
			// Aplico mecanismo de exclusion
			frequencyTable.exc(exclusionCharacters);
			int result = -1;
			bool end = false;
			//Mientras no pueda resolver la consulta, pide numeros
			while (!end){
				result = calculator.foundedCharModel(getNumber(), getBitsInNumber(), getBottom(), getTop(), &temporalBottom, &temporalTop, frequencyTable);
				if (result < 0){
					//Si entra aqui es po que no llego a definir con los bits que estan y tiene q seguir metiendo bits

					if (getBitsInBuffer() >0){
						dropBufferInNumber();
					}
					else{
						this->state = STATE_NON_LAST_MODEL;
						this->currentContext = context;
						this->exclusionChars = exclusionCharacters;
						this->firstContext = firstContext;
						return false;
					}
				}
				else {
					end = true;
				}
			}
			setBottom(temporalBottom);
			setTop(temporalTop);
#ifdef VERBOSE_ARITHMETIC
			printf ("number antes de operar: %x\n", getNumber());
			printf ("top antes de operar: %x\n", temporalTop);
			printf ("bottom antes de operar: %x\n", temporalBottom);
#endif
			solveOverflow();
#ifdef VERBOSE_ARITHMETIC
			printf ("number dsp de over: %x\n", getNumber());
			printf ("top dsp de over: %x\n", getTop());
			printf ("bottom dsp de over: %x\n", getBottom());
#endif
			solveUnderflow();
#ifdef VERBOSE_ARITHMETIC
			printf ("number dsp de under: %x\n", getNumber());
			printf ("top dsp de under: %x\n", getTop());
			printf ("bottom dsp de under: %x\n", getBottom());
#endif

			if (result != ESC){
				found = true;
				frequencyTable.find(result);
				u_int16_t characterTable = result;
				addToQueue(characterTable);
				this->state = STATE_OK;
				int i;
				for (i=(int)firstPos; i>=(int)pos; i--){
					if (i<0){
						break;
					}
					models[i]->update(firstContext, characterTable);
					if (firstContext.size()>0){
						firstContext = firstContext.substr(1);
					}
				}

				contextSelector.add(characterTable);
				hasMoreIterations = 1;
				end = true;
			}
			else {
				this->state = STATE_OK;
				if (pos == 0) {
					if (!found) {
						// Esta en el Modelo -1 porque no se encontro en el Modelo 0
						// Obtengo los caracteres a excluir del modelo 0
						frequencyTable.getStringExc(exclusionCharacters);
						// Aplico mecanismo de exclusion restando a MAX el size del string de
						// exclusion
						found = true;

						bool value = solveLastModel(exclusionCharacters, firstContext, &hasMoreIterations);
						if (value){
							return true;
						}
						if (!hasMoreIterations){
							return false;
						}
					}
				} else {
					pos--;
					context = context.substr(1);
				}

			}
			// Agrego los posibles caracteres a excluir a la cadena de
			// caracteres de exclusion
			frequencyTable.getStringExc(exclusionCharacters);
			frequencyTable.clear();
		}
#ifdef VERBOSE_MODELS
		show();
#endif
	}
	return false;
}

PPMCUncompressor::~PPMCUncompressor() {
	for (size_t i=0; i<(ORDEN + 1);i++) {
		delete models[i];
	}
}
