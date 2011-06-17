#include "PPMCCompressor.h"

#include <sys/time.h>
#include <sys/resource.h>
/*
    struct timeval ru_utime; // user time used 
    struct timeval ru_stime; // system time used 
    long   ru_maxrss;        // maximum resident set size 
    long   ru_ixrss;         // integral shared memory size 
    long   ru_idrss;         // integral unshared data size 
    long   ru_isrss;         // integral unshared stack size
    long   ru_minflt;        // page reclaims
    long   ru_majflt;        // page faults
    long   ru_nswap;         // swaps
    long   ru_inblock;       // block input operations
    long   ru_oublock;       // block output operations
    long   ru_msgsnd;        // messages sent
    long   ru_msgrcv;        // messages received
    long   ru_nsignals;      // signals received 
    long   ru_nvcsw;         // voluntary context switches 
    long   ru_nivcsw;        // involuntary context switches 
 */
int measure() {
	int who = RUSAGE_SELF; 
	struct rusage usage; 
	int ret; 
	ret=getrusage(who,&usage);
	return usage.ru_maxrss;
}

using namespace ppmc;

PPMCCompressor::PPMCCompressor(FileReader* r, FileWriter* w):ArithmeticCompressor(r,w) {
	for (size_t i=0; i<(ORDEN + 1);i++) {
		Model * model = new Model();
		if (!model) {
			throw bad_alloc();
		}
		models.push_back(model);
	}
}

void PPMCCompressor::compress() {
	static int i = 0;
	writer->writeSizeInHeader(reader->getSize());
	while (!reader->eof() ) {
		i++;
		char c = reader->read();
		process(c);
		if (i % 100000 == 0) {
			cout << i << endl;
		}
	}
	cleanBuffer();
}

void PPMCCompressor::show(){
	for (int i = ORDEN; i > -1; i--) {
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

	a &= 0x00FF;

#ifdef VERBOSE_MODELS
	cout << "LEO " << a << " CONTEXTO \"" << context << "\" EMITO:" << endl;
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

				table.getLimitsLastModel(a, actualBottom, actualTop, &temporalLastBottom, &temporalLastTop, exclusionCharacters);
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

PPMCCompressor::~PPMCCompressor() {
	for (size_t i=0; i<(ORDEN + 1);i++) {
		delete models[i];
	}
}
