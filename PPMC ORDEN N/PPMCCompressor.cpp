#include "PPMCCompressor.h"
#include "Constants.h"
#include "TableCalculator.h"
using namespace ppmc;
using namespace std;


PPMCCompressor::PPMCCompressor(util::FileReader *r, util::FileWriter *w):ArithmeticCompressor(r,w) {
	for (size_t i=0; i<(ORDEN + 1);i++) {
		models.push_back(new Model());
	}
}

void PPMCCompressor::compress() {
	
	while (!reader->eof() ) {
		char c = reader->read();
		cout << "c" << endl;
		process(c);
	}
}

void PPMCCompressor::show(){
	for (int i = ORDEN; i > -1; i--) {
		if (models[i]->getSize()) {
			std::cout << "Modelo " << i << ": " << std::endl;
			models[i]->show();
		}
	}
}

void PPMCCompressor::process(u_int8_t a){
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;

	std::cout << "LEO " << (char)a << " CONTEXTO \"" << context << "\" EMITO:" << std::endl;

	TableCalculator table;
	while (!found) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));

		// Aplico mecanismo de exclusion
		frequencyTable.exc(exclusionCharacters);
		u_int64_t actualBottom = getBottom();
		u_int64_t actualTop = getTop();
		u_int64_t temporalBottom;
		u_int64_t temporalTop;

		// table no deberia devolver true nunca, no importa eso por que es modelo != del -1 donde
		// puede haber un eof

		table.getEnds(a, actualBottom, actualTop, &temporalBottom, &temporalTop, this->frequencyTable);
		printf ("top antes de operar: %x\n", temporalTop);
		printf ("bottom antes de operar: %x\n", temporalBottom);
		setBottom(temporalBottom);
		setTop(temporalTop);
		solveOverflow();
		printf ("top dsp de over: %x\n", getTop());
		printf ("bottom dsp de over: %x\n", getBottom());
		solveUnderflow();
		printf ("top dsp de under: %x\n", getTop());
		printf ("bottom dsp de under: %x\n", getBottom());
		if (frequencyTable.find(a)) {
			found = true;
			std::cout << a << " = " << frequencyTable.getFrequencyChar() << "/";
			std::cout << frequencyTable.getTotal() << std::endl;
		} else {
			std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			std::cout << frequencyTable.getTotal()<< std::endl;
		}

		models[pos]->update(context, a);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
				std::cout << a <<" = 1/" << MAX - exclusionCharacters.size()<< std::endl;
				found = true;
				u_int64_t actualBottom = getBottom();
				u_int64_t actualTop = getTop();
				u_int64_t temporalLastBottom;
				u_int64_t temporalLastTop;

				// Esta funcion get_ends deberia ser la que puede devolver true si aparece el end of file

				table.getEndsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
				setBottom(temporalLastBottom);
				setTop(temporalLastTop);
				printf ("top antes de operar: %x\n", temporalLastTop);
				printf ("bottom antes de operar: %x\n", temporalLastBottom);

				solveOverflow();
				printf ("top dsp de over: %x\n", getTop());
				printf ("bottom dsp de over: %x\n", getBottom());

				// no es EOF
				solveUnderflow();
				printf ("top dsp de under: %x\n", getTop());
				printf ("bottom dsp de under: %x\n", getBottom());

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
	contextSelector.add(a);
}

void PPMCCompressor::processEof(u_int16_t a){
	bool found = false;
	std::string context = contextSelector.getContext();
	std::size_t pos = context.size();
	std::string exclusionCharacters;

	std::cout << "LEO " << (char)a << " CONTEXTO \"" << context << "\" EMITO:" << std::endl;

	TableCalculator table;
	while (!found) {
		// cargo la tabla con el modelo actual
		frequencyTable.update (models[pos]->find(context));

		// Aplico mecanismo de exclusion
		frequencyTable.exc(exclusionCharacters);
		u_int64_t actualBottom = getBottom();
		u_int64_t actualTop = getTop();
		u_int64_t temporalBottom;
		u_int64_t temporalTop;

		// table no deberia devolver true nunca, no importa eso por que es modelo != del -1 donde
		// puede haber un eof

		table.getEnds(a, actualBottom, actualTop, &temporalBottom, &temporalTop, this->frequencyTable);
		printf ("top antes de operar: %x\n", temporalTop);
		printf ("bottom antes de operar: %x\n", temporalBottom);
		setBottom(temporalBottom);
		setTop(temporalTop);
		solveOverflow();
		printf ("top dsp de over: %x\n", getTop());
		printf ("bottom dsp de over: %x\n", getBottom());
		solveUnderflow();
		printf ("top dsp de under: %x\n", getTop());
		printf ("bottom dsp de under: %x\n", getBottom());
		if (frequencyTable.find(a)) {
			found = true;
			std::cout << a << " = " << frequencyTable.getFrequencyChar() << "/";
			std::cout << frequencyTable.getTotal() << std::endl;
		} else {
			std::cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			std::cout << frequencyTable.getTotal()<< std::endl;
		}

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
				std::cout << a <<" = 1/" << MAX - exclusionCharacters.size()<< std::endl;
				found = true;
				u_int64_t actualBottom = getBottom();
				u_int64_t actualTop = getTop();
				u_int64_t temporalLastBottom;
				u_int64_t temporalLastTop;

				// Esta funcion get_ends deberia ser la que puede devolver true si aparece el end of file

				table.getEndsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
				setBottom(temporalLastBottom);
				setTop(temporalLastTop);
				printf ("top antes de operar: %x\n", temporalLastTop);
				printf ("bottom antes de operar: %x\n", temporalLastBottom);

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

	cleanBuffer();
}

PPMCCompressor::~PPMCCompressor() {
	processEof(END_OF_FILE);
	for (size_t i=0; i<(ORDEN + 1);i++) {
		delete models[i];
	}
}
