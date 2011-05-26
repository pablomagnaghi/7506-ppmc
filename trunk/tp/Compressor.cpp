#include "Compressor.h"
#include "FrequencyTable.h"
#include "M_1FrequencyTable.h"



using namespace ppmc;
using namespace std;

Compressor::Compressor(size_t o):Arithmetic(o){

}

Compressor::~Compressor(){


}

void Compressor::calculate(Probability& p){
	baseType delta        = ceiling - floor;
	baseType steps        = delta / p.total;
	baseType deltaCeiling = p.skip * steps;
	baseType deltaFloor   = p.total - p.skip - p.width;
	deltaFloor            = deltaFloor * steps;
	ceiling              -= deltaCeiling;
	floor                += deltaFloor;
}

void Compressor::compressWithM_1(ContextSelector& cs, char c) {
		M_1FrequencyTable ft;
		q.clear();
		q.setTerm(c);
		ft.compress(q);
		Probability p = q.getProbability();
		calculate(p);
		// emit something
		cs.add(c);
}

void Compressor::compressWithModels(ContextSelector& cs, char c){
		q.clear();
		for(int i=order; i>0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			Probability p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				// emit something
				cs.add(c);
				break;
			}
		}
}

void Compressor::compressEof(ContextSelector& cs){
	// not tested
	// deal with eof in models
	for(int i=order; i>0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.clear();
			ft->compressEof(q);
			Probability p = q.getProbability();
			calculate(p);
		// emit something
	}

	// deal with eof in model -1
	// not tested
	M_1FrequencyTable ft;
	q.clear();
	ft.compressEof(q);
	Probability p = q.getProbability();
	calculate(p);
	//emit something

}

/**
 * Los primeros "order" caracteres se comprimen
 * directamente en M-1 para facilitar la implementacion.
 */
void Compressor::compress(util::IFileReader* reader, util::IFileWriter* writer){
	char c;
	size_t i=0;
	ContextSelector cs(order);

	while (!reader->eof() && i < order) {
		c = reader->read();
		compressWithM_1(cs, c);
		i++;
	}
	
	while (!reader->eof()) {
		c = reader->read();
		compressWithModels(cs,c);
		cs.add(c);
	}
	
	compressEof(cs);
}
