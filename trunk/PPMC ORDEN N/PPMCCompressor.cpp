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
		process(c);
	}
}

void PPMCCompressor::show(){
	
	for (int i = ORDEN; i > -1; i--) {
		if (models[i]->getSize()) {
			cout << "Modelo " << i  << ": " << endl;
			cout << models[i]->show();
		}
	}
}

void PPMCCompressor::process(u_int8_t a){
	bool found = false;
	string context = contextSelector.getContext();
	size_t pos = context.size();
	string exclusionCharacters;
#ifdef VERBOSE_MODELS
	cout << "LEO " << (char)a << " CONTEXTO \"" << context << "\" EMITO:" << endl;
#endif
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
#ifdef VERBOSE_ARITHMETIC
		printf ("top antes de operar: %x\n", temporalTop);
		printf ("bottom antes de operar: %x\n", temporalBottom);
#endif
		setBottom(temporalBottom);
		setTop(temporalTop);
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
		if (frequencyTable.find(a)) {
			found = true;
#ifdef VERBOSE_MODELS
			cout << a << " = " << frequencyTable.getFrequencyChar() << "/";
			cout << frequencyTable.getTotal() << endl;
#endif
		} else {
#ifdef VERBOSE_MODELS
			cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			cout << frequencyTable.getTotal()<< endl;
#endif
		}

		models[pos]->update(context, a);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
#ifdef VERBOSE_MODELS
				cout << a <<" = 1/" << MAX - exclusionCharacters.size()<< endl;
#endif
				found = true;
				u_int64_t actualBottom = getBottom();
				u_int64_t actualTop = getTop();
				u_int64_t temporalLastBottom;
				u_int64_t temporalLastTop;

				// Esta funcion get_ends deberia ser la que puede devolver true si aparece el end of file

				table.getEndsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
				setBottom(temporalLastBottom);
				setTop(temporalLastTop);
#ifdef VERBOSE_ARITHMETIC
				printf ("top antes de operar: %x\n", temporalLastTop);
				printf ("bottom antes de operar: %x\n", temporalLastBottom);
#endif
				solveOverflow();
#ifdef VERBOSE_ARITHMETIC
				printf ("top dsp de over: %x\n", getTop());
				printf ("bottom dsp de over: %x\n", getBottom());
#endif
				// no es EOF
				solveUnderflow();
#ifdef VERBOSE_ARITHMETIC
				printf ("top dsp de under: %x\n", getTop());
				printf ("bottom dsp de under: %x\n", getBottom());
#endif
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
#ifdef VERBOSE_MODELS
	show();
#endif
	// actualizo el contexto
	contextSelector.add(a);
}

void PPMCCompressor::processEof(u_int16_t a){
	bool found = false;
	string context = contextSelector.getContext();
	size_t pos = context.size();
	string exclusionCharacters;

#ifdef VERBOSE_MODELS
	cout << "LEO " << (char)a << " CONTEXTO \"" << context << "\" EMITO:" << endl;
#endif
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
#ifdef VERBOSE_ARITHMETIC
		printf ("top antes de operar: %x\n", temporalTop);
		printf ("bottom antes de operar: %x\n", temporalBottom);
#endif
		setBottom(temporalBottom);
		setTop(temporalTop);
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
		if (frequencyTable.find(a)) {
			found = true;
#ifdef VERBOSE_MODELS
			cout << a << " = " << frequencyTable.getFrequencyChar() << "/";
			cout << frequencyTable.getTotal() << endl;
#endif
		} else {
#ifdef VERBOSE_MODELS
			cout << "ESC  = " << frequencyTable.getFrequencyEsc() << "/";
			cout << frequencyTable.getTotal()<< endl;
#endif
		}

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
#ifdef VERBOSE_MODELS
				cout << a <<" = 1/" << MAX - exclusionCharacters.size()<< endl;
#endif
				found = true;
				u_int64_t actualBottom = getBottom();
				u_int64_t actualTop = getTop();
				u_int64_t temporalLastBottom;
				u_int64_t temporalLastTop;

				// Esta funcion get_ends deberia ser la que puede devolver true si aparece el end of file

				table.getEndsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
				setBottom(temporalLastBottom);
				setTop(temporalLastTop);
#ifdef VERBOSE_ARITHMETIC
				printf ("top antes de operar: %x\n", temporalLastTop);
				printf ("bottom antes de operar: %x\n", temporalLastBottom);
#endif
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
