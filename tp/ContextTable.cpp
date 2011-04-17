#include "ContextTable.h"

using namespace ppmc;
using namespace std;

ContextTable::ContextTable(){

}
void ContextTable::compress(Query & q){
	Probability p;
	size_t count = 0;
	q.setFound(false);
	
	map<char,size_t>::iterator iter;
	
	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (!q.isExcluded(iter->first) ) {
			count+=iter->second;
			if (iter->first == q.getTerm() ) {
				q.setFound(true);
				p.width = iter->second;
				iter->second++;
			} else {
				p.skip+=iter->second;
			}
			
		}
	}
	
	if( q.isFound() ) {
		p.total = count + freq.size();
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
	
	q.setProbability(p);
	
	std::map<char,size_t>::iterator it;
	for(it = freq.begin(); it != freq.end(); it++) {
		q.addExclusion(it->first);
	}
}