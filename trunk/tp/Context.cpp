#include "Context.h"


using namespace ppmc;
using namespace std;

Context::Context():esc(0){

}
Response Context::eval(Query q){
	Probability p;
	Response r;
	p.skip = 0;
	p.width = 1;
	p.total = 1;
	r.setProbability(p);
	return r;
}