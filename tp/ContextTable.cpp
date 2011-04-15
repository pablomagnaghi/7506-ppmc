#include "ContextTable.h"

using namespace ppmc;
using namespace std;

ContextTable::ContextTable():esc(1),count(0){

}
void ContextTable::compress(Query & q){
	Probability p;

	map<char,size_t>::iterator iter;
	
	q.setFound(false);

	for( iter = freq.begin(); iter != freq.end(); ++iter ) {
		if (iter->first == q.getChar() ) {
			q.setFound(true);
			break;
		}
		p.skip+=iter->second;
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
		freq.insert(make_pair(q.getChar(),1));
	}
	count++;
	
	q.setProbability(p);
	
	//q.setExclusions();
	
}