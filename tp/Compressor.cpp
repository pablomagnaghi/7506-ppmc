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

void Compressor::compressWithM_1(ContextSelector& cs, char c) {
	M_1FrequencyTable ft;
	q.setTerm(c);
	ft.compress(q);
	Probability p = q.getProbability();
	calculate(p);
	//setNewLimits();
	cs.add(c);
}

void Compressor::compressWithModels(ContextSelector& cs){
	Probability p;
	size_t increasingOrder=0;
	
	while (!reader->eof()) {
		char c = reader->read();
		q.clear();
#ifdef EXTRAVERBOSE
		cerr << "LEO " << c << " CONTEXTO \"" << cs.get(order) << "\" EMITO:" << endl;
#endif
		for(int i=increasingOrder; i>=0; i--) {
			FrequencyTable* ft = models[i]->find(cs.get(i));
			q.setTerm(c);
			ft->compress(q);
			p = q.getProbability();
			if ( q.isFound()) {
				calculate(p);
				cs.add(c);
				//setNewLimits();
#ifdef VERBOSE
				cerr << c << " = " << p.width << "/" << p.total << endl;
#endif
				break;
			} else {
#ifdef VERBOSE
				cerr << "ESC  = " << p.width << "/" << p.total  << endl;
#endif
			}
		}
		if (!q.isFound()) {
			compressWithM_1(cs, c);
		}
		
#ifdef EXTRAVERBOSE
		cerr << show(increasingOrder);
#endif
		if (increasingOrder < order) {
			++increasingOrder;
		}
		
	}
}

void Compressor::compressEof(ContextSelector& cs){
#ifdef EXTRAVERBOSE
	cerr << "LEO   CONTEXTO \"" << cs.get(order) << "\" EMITO:" << endl;
#endif
	q.clear();
	for(int i=order; i>=0; i--) {
		FrequencyTable* ft = models[i]->find(cs.get(i));
		ft->compressEof(q);
		Probability p = q.getProbability();
		calculate(p);
#ifdef VERBOSE
		cerr << "ESC  = " << p.width << "/" << p.total << endl;
#endif
		//setNewLimits();
	}
	M_1FrequencyTable ft;
	ft.compressEof(q);
	Probability p = q.getProbability();
	calculate(p);
	//setNewLimits();

}

void Compressor::compress(util::IFileReader* r, util::IFileWriter* w){
	reader = r;
	writer = w;
	ContextSelector cs(order);
	compressWithModels(cs);
	compressEof(cs);
	clean_buffer();
}

std::string Compressor::show(size_t increasingOrder) {
	stringstream result;
	for (int i= increasingOrder; i>=0; --i) {
		result << "Modelo " << i  << ": " << endl;
		result << models[i]->show();
	}
	return result.str();
}