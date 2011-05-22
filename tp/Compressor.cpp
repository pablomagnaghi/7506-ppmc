#include "Compressor.h"
#include "ContextSelector.h"
#include "FrequencyTable.h"
#include "Query.h"
#include "Probability.h"

using namespace ppmc;
using namespace std;

Compressor::Compressor(size_t o):Arithmetic(o){

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
	ContextSelector cs(1);
	while (!reader->eof() && i < order) {
		c = reader->read();
		FrequencyTable* ft = new FrequencyTable(); //quizas requiera subclase para M-1
		Query q;
		q.setTerm(c);
		ft->compress(q);
		Probability p = q.getProbability();
		// calculate new floor and ceiling
		// emit something
		delete(ft);
		cs.add(c);
		i++;
	}
	
	while (!reader->eof()) {
		c = reader->read();
		writer->write(c);
		for(int i=order; i>0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			Query q;
			q.setTerm(c);
			ft->compress(q);
			Probability p = q.getProbability();
			if ( q.isFound()) {
				// calculate new floor and ceiling
				// emit something
				cs.add(c);
				break;
			}
		}
		cs.add(c);
	}
	if (order > 0) {
	// ask model -1 for eof
	// calculate new floor and ceiling
	// emit something
	}
	
}
