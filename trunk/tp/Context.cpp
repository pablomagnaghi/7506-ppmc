#include "Context.h"


using namespace ppmc;
using namespace std;

Context::Context():esc(1),count(0){

}
Response Context::eval(Query q){
	Probability p;
	Response r;

	map<char,size_t>::iterator iter = freq.find(q.getChar());
	
	if( iter == freq.end() ) {
		r.setFound(false);
		if (freq.size() == 0) {
			p.skip = 0;
			p.width = 1;
			p.total = 1;
		} else {
			p.skip = freq.size();
			p.width = freq.size();
			p.total = count + freq.size() ;
		}
		freq.insert(make_pair(q.getChar(),1));
	} else {
		p.skip = 0;
		p.width = iter->second;
		r.setFound(true);
		p.total = count + freq.size();
		iter->second++;
	}
	count++;
	
	r.setProbability(p);
	
	return r;
}