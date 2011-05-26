#include "FrequencyTable.h"

using namespace ppmc;
using namespace std;

FrequencyTable::FrequencyTable(){

}

void FrequencyTable::compressEof(Query &q){
	Probability p;
	p.total = 257;
	p.skip  = 256;
	p.width = 1;
	q.setProbability(p);
	q.setFound(true);
}

void FrequencyTable::compress(Query & q){
	Probability p;
	size_t count = 0;
	q.setFound(false);
	
	map<char,size_t>::iterator iter;
	
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first) ) {
			p.total+=iter->second;
			count++;
			if (iter->first == q.getTerm() ) {
				q.setFound(true);
				p.width = iter->second;
				iter->second++;
			} else {
				p.skip+=iter->second;
			}
		}
	}
	
	p.total += count;
	
	if( !q.isFound() ) {
		if (freq.size() == 0) {
			p.width = 1;
			p.total = 1;
		} else {
			p.width = count;
		}
		freq.insert(make_pair(q.getTerm(),1));
	}
	
	q.setProbability(p);
	
	std::map<char,size_t>::iterator it;
	for(it = freq.begin(); it != freq.end(); it++) {
		q.addExclusion(it->first);
	}
}