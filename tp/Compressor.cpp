#include "Compressor.h"
#include "FrequencyTable.h"
#include "M_1FrequencyTable.h"

using namespace std;

using namespace ppmc;
using namespace std;

size_t Compressor::increasingOrder = 0;

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
	q.setTerm(c);
	ft.compress(q);
	Probability p = q.getProbability();
	calculate(p);
	setNewLimits();
	cs.add(c); // useless, drop it
}

void Compressor::compressWithModels(ContextSelector& cs){
	Probability p;
	size_t increasingOrder=0;
	char c = reader->read();
	while (!reader->eof()) {
		q.clear();
		cout << "LEO " << c << " CONTEXTO " << cs.get(order) << " EMITO: " << endl;
		
		for(int i=increasingOrder; i>=0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				cs.add(c);
				setNewLimits();
				cout << c << " = " << p.width << "/" << p.total << endl;
				//cout << c << " = " << p.width << "/" << p.total << " en modelo "<< i << endl;
				break;
			} else {
				cout << "ESC = " << p.width << "/" << p.total  << endl;
				//cout << "ESC = " << p.width << "/" << p.total << " en modelo "<< i << endl;
			}
		}
		if (!q.isFound()) {
			compressWithM_1(cs, c);
		}
		c = reader->read();
		
		for (int i= increasingOrder; i>=0; --i) {
			cout << "Modelo " << i  << ":" << endl;
			cout << models[i]->show();
		}
		if (increasingOrder < order) {
			++increasingOrder;
		}
		
	}
}

void Compressor::compressEof(ContextSelector& cs){
	cout << "LEO EOF CONTEXTO " << cs.get(order) << " EMITO: " << endl;
	for(int i=order; i>=0; i--) {
		FrequencyTable* ft = models[i]->find(cs.get(i));
		ft->compressEof(q);
		Probability p = q.getProbability();
		calculate(p);
		//cout << "ESC = " << p.width << "/" << p.total << " en modelo "<< i << endl;
		cout << "ESC  = " << p.width << "/" << p.total << endl;
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
	//compressFirstChars(cs);
	compressWithModels(cs);
	compressEof(cs);
	clean_buffer();
}
