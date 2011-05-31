#include "Compressor.h"
#include "FrequencyTable.h"
#include "M_1FrequencyTable.h"

using namespace std;

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
	Probability p;
	unsigned int startingOrder=0;  // sent to class and use it from compressEOF
	while (!reader->eof() && startingOrder < order) {
		c = reader->read();
		q.clear();
		cout << "LEO " << c << " CONTEXTO " << cs.get(startingOrder) << " EMITO: " << endl;
		for(int i=startingOrder; i>=0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			p = q.getProbability();
			cs.add(c);
			if ( q.isFound()) {
				calculate(p);
				setNewLimits();
				cout << c << " = " << p.width << "/" << p.total << " en modelo "<< i << endl;
				break;
			} else {
				cout << "ESC = " << p.width << "/" << p.total << " en modelo "<< i << endl;
			}
		}
		startingOrder++;
	}
	if (!q.isFound()) {
		compressWithM_1(cs, c);
	}
}

void Compressor::compressWithM_1(ContextSelector& cs, char c) {
	M_1FrequencyTable ft;
	q.setTerm(c);
	ft.compress(q);
	Probability p = q.getProbability();
	calculate(p);
	setNewLimits();
	cs.add(c); // useless, drop it
}

void Compressor::compressWithModels(ContextSelector& cs){
	Probability p;
	char c = reader->read();
	while (!reader->eof()) {
		q.clear();
		cout << "LEO " << c << " CONTEXTO " << cs.get(order) << " EMITO: " << endl;
		for(int i=order; i>=0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				setNewLimits();
				cs.add(c);
				cout << c << " = " << p.width << "/" << p.total << " en modelo "<< i << endl;
				break;
			} else {
				cout << "ESC = " << p.width << "/" << p.total << " en modelo "<< i << endl;
			}
		}
		if (!q.isFound()) {
			compressWithM_1(cs, c);
		}
		cs.add(c);
		c = reader->read();
	}

}

void Compressor::compressEof(ContextSelector& cs){
	cout << "LEO EOF CONTEXTO " << cs.get(order) << " EMITO: " << endl;
	for(int i=order; i>=0; i--) {
		FrequencyTable* ft = models[i]->find(cs.get(i));
		ft->compressEof(q);
		Probability p = q.getProbability();
		calculate(p);
		cout << "ESC = " << p.width << "/" << p.total << " en modelo "<< i << endl;
		setNewLimits();
	}

	M_1FrequencyTable ft;
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
