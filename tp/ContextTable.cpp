#include "ContextTable.h"

using namespace ppmc;
using namespace std;

ContextTable::ContextTable():esc(1),count(0){

}
Response ContextTable::compress(Query q){
	Probability p;
	Response r;

	map<char,size_t>::iterator iter;
	
	r.setFound(false);

	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (iter->first == q.getChar() ) {
			r.setFound(true);
			break;
		}
		p.skip+=iter->second;
	}
	
	if( r.isFound() ) {
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
		freq.insert(make_pair(q.getChar(),1));
	}
	count++;
	
	r.setProbability(p);
	
	//r.setExclusions();
	return r;
}