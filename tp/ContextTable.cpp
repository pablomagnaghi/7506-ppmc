#include "ContextTable.h"

using namespace ppmc;
using namespace std;

ContextTable::ContextTable():esc(1),count(0){

}
void ContextTable::compress(Query & q){
	Probability p;
	
	map<char,size_t> fixedFreq;
	
	
	
	q.setFound(false);
	
	
	map<char,size_t>::iterator iter;
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first) ) {
			if (iter->first == q.getTerm() ) {
				q.setFound(true);
				break;
			}
			p.skip+=iter->second;
		}
	}
	
	if( q.isFound() ) {
		p.width = iter->second;
		p.total = count + freq.size();
		iter->second++;
	} else {
		if (freq.size() == 0) {
			p.width = 1;
			p.total = 1;
		} else {
			p.width = freq.size();
			p.total = count + freq.size() ;
		}
		freq.insert(make_pair(q.getTerm(),1));
	}
	count++;
	
	q.setProbability(p);
	
	std::map<char,size_t>::iterator it;
	for(it = freq.begin(); it != freq.end(); it++) {
		q.addExclusion(it->first);
	}
}