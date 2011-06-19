#include "M_1FrequencyTable.h"

using namespace ppmc;
using namespace std;

M_1FrequencyTable::M_1FrequencyTable():FrequencyTable(){

}

void M_1FrequencyTable::compressEof(Query &q){
	Probability p;
	p.total = 256 - q.getExclusionSize();
	p.skip = p.total -1;
	p.width = 1;
	q.setFound(true);
	q.setProbability(p);
#ifdef VERBOSE
	cerr << "256 = " << p.width << "/" << p.total << endl;
	//cerr << "EOF = " << p.width << "/" << p.total << " en modelo -1" << endl;
#endif
}

void M_1FrequencyTable::compress(Query & q){
	Probability p;
	int total = 257;
	int skip  =   0;
	bool skipping = true;
	for(int i=0; i<256; ++i) {
		if (q.isExcluded((char)i) ) {
			total--;
			if ((char)i == q.getTerm()) {
				skipping = false;
			}
			if (skipping) {
				++skip;
			}
		}
	}
	p.total = total;
	p.skip  = q.getTerm() - skip;
	p.width = 1;
	q.setFound(true);
	q.setProbability(p);
#ifdef VERBOSE
	cerr << q.getTerm() << " = " << p.width << "/" << p.total << endl;
//cerr << q.getTerm() << " = " << p.width << "/" << p.total << " en modelo -1" << endl;
#endif
}