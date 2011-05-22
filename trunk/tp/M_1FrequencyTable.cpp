#include "M_1FrequencyTable.h"

using namespace ppmc;
using namespace std;

M_1FrequencyTable::M_1FrequencyTable():FrequencyTable(){

}

void M_1FrequencyTable::compressEof(Query &q){
	Probability p;
	p.total = 257;
	p.skip  = 256;
	p.width = 1;
	q.setProbability(p);
	q.setFound(true);
}

void M_1FrequencyTable::compress(Query & q){
	Probability p;
	int total = 257;
	int skip  =   0;
	
	
	
	for(int i=0; i<q.getTerm(); i++) {
		if (q.isExcluded(i) ) {
			total--;
			skip++;
		}
	}
	p.total = total;
	p.skip  = q.getTerm() - skip;
	p.width = 1;
	
	q.setProbability(p);
	q.setFound(true);
}