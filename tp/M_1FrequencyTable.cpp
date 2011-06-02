#include "M_1FrequencyTable.h"

using namespace ppmc;
using namespace std;

M_1FrequencyTable::M_1FrequencyTable():FrequencyTable(){

}

void M_1FrequencyTable::compressEof(Query &q){
	Probability p;
	p.skip = 256 - q.getExclusionSize();
	p.total = p.skip + 1;
	p.width = 1;
	q.setFound(true);
	q.setProbability(p);
	cout << "EOF = " << p.width << "/" << p.total << endl;
	//cout << "EOF = " << p.width << "/" << p.total << " en modelo -1" << endl;
}

void M_1FrequencyTable::compress(Query & q){
	Probability p;
	int total = 257;
	int skip  =   0;
	for(char i=0; i<q.getTerm(); i++) {
		if (q.isExcluded(i) ) {
			total--;
			skip++;
		}
	}
	p.total = total;
	p.skip  = q.getTerm() - skip;
	p.width = 1;
	q.setFound(true);
	q.setProbability(p);
	cout << q.getTerm() << " = " << p.width << "/" << p.total << endl;
	//cout << q.getTerm() << " = " << p.width << "/" << p.total << " en modelo -1" << endl;
}