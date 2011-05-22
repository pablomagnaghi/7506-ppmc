#include "Compressor.h"
#include "ContextSelector.h"
#include "ContextTable.h"
#include "Query.h"
#include "Probability.h"

using namespace ppmc;
using namespace std;

Compressor::Compressor():Arithmetic(){

}

Compressor::~Compressor(){


}

/**
 * Hemos decidido que los primeros "order" caracteres se comprimen
 * directamente en M-1 para facilitar la implementacion.
 */
void Compressor::compress(util::IFileReader* reader, util::IFileWriter* writer){
	char c;
	size_t i=0;
	while (!reader->eof() && i < order) {
		c = reader->read();
		ContextTable* ct = new ContextTable(); //quizas requiera subclase para M-1
		Query q;
		q.setTerm(c);
		ct->compress(q);
		Probability p = q.getProbability();
		// calculate new floor and ceiling
		// emit something
		// ask model -1 for c
		delete(ct);
		i++;
	}

	ContextSelector cs(1);
	cs.add(c);
 	while (!reader->eof()) {
		c = reader->read();
		writer->write(c);
		for(int i=order; i>0; i--) {
			ContextTable* ct = models[i]->find(cs.get(i));
			Query q;
			q.setTerm(c);
			ct->compress(q);
			Probability p = q.getProbability();
			// calculate new floor and ceiling
			// emit something
		}
		cs.add(c);
	}
}