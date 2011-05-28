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

void Compressor::compressFirstChars(ContextSelector& cs) {
	char c;
	unsigned int j=0;
	while (!reader->eof() && j < order) {
		c = reader->read();
		q.clear();
		for(int i=j; i>0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			Probability p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				setNewLimits();
				cs.add(c);
				break;
			}
		}
		j++;
	}
	
}

void Compressor::compressWithM_1(ContextSelector& cs, char c) {
	M_1FrequencyTable ft;
	q.clear();
	q.setTerm(c);
	ft.compress(q);
	Probability p = q.getProbability();
	calculate(p);
	setNewLimits();
	cs.add(c);
}

void Compressor::compressWithModels(ContextSelector& cs){
	char c;
	while (!reader->eof()) {
		c = reader->read();
		q.clear();
		for(int i=order; i>0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			Probability p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				setNewLimits();
				cs.add(c);
				break;
			}
		}
		cs.add(c);
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
		setNewLimits();
	}

	// deal with eof in model -1
	// not tested
	M_1FrequencyTable ft;
	q.clear();
	ft.compressEof(q);
	Probability p = q.getProbability();
	calculate(p);
	setNewLimits();

}

void Compressor::compress(util::IFileReader* r, util::IFileWriter* w){
	reader = r;
	writer = w;
	ContextSelector cs(order);
	compressFirstChars(cs);
	compressWithModels(cs);
	compressEof(cs);
	clean_buffer();
}
