#include "PPMCCompressor.h"

using namespace ppmc;

PPMCCompressor::PPMCCompressor(FileReader* r, FileWriter* w, size_t o):ArithmeticCompressor(r,w),order(o) {
	contextSelector.setOrder(order);
	for (size_t i=0; i<(order + 1);i++) {
		Model * model = new Model();
		if (!model) {
			throw bad_alloc();
		}
		models.push_back(model);
	}
}

void PPMCCompressor::compress() {
	static int i = 0;
	writer->writeSizeInHeader(order,reader->getSize());
	while (!reader->eof() ) {
		i++;
		char c = reader->read();
		process(c);
	}
	process(END_OF_FILE);
}

void PPMCCompressor::show(){
	for (int i = order; i > -1; i--) {
		if (models[i]->getSize()) {
			cout << "Modelo " << i << ": " << endl;
			cout << models[i]->show() << endl;
		}
	}
}

void PPMCCompressor::process(u_int16_t a){
	bool found = false;
	string context = contextSelector.getContext();
	size_t pos = context.size();
	string exclusionCharacters;

	if (a!=END_OF_FILE)
			a &= 0x00FF;

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

		if (frequencyTable.find(a)) {
			found = true;
		} else {
		}
		setBottom(temporalBottom);
		setTop(temporalTop);
		solveOverflow();
		solveUnderflow();

		models[pos]->update(context, a);

		if (pos == 0) {
			if (!found) {
				// Esta en el Modelo -1 porque no se encontro en el Modelo 0
				// Obtengo los caracteres a excluir del modelo 0
				frequencyTable.getStringExc(exclusionCharacters);
				// Aplico mecanismo de exclusion restando a MAX el size del string de
				// exclusion
				found = true;
				u_int64_t actualBottom = getBottom();
				u_int64_t actualTop = getTop();
				u_int64_t temporalLastBottom;
				u_int64_t temporalLastTop;

				// Esta funcion get_ends deberia ser la que puede devolver true si aparece el end of file

				bool isEof = table.getEndsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
				setBottom(temporalLastBottom);
				setTop(temporalLastTop);
				solveOverflow();

				if (!isEof) {
					solveUnderflow();
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

	if (a==END_OF_FILE){
		cleanBuffer();
	}

	//show();
	// actualizo el contexto
	contextSelector.add(a);
}

PPMCCompressor::~PPMCCompressor() {
	for (size_t i=0; i<(order + 1);i++) {
		delete models[i];
	}
}
