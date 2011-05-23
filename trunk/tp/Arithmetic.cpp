#include <climits>

#include "Arithmetic.h"


using namespace ppmc;
using namespace std;

Arithmetic::Arithmetic(size_t o):order(o){
	for (size_t i=0; i<order;i++) {
		models.push_back(new Model);
	}
	floor = 0;
	ceiling = UINT_MAX;
}

Arithmetic::~Arithmetic(){
	for (size_t i=0; i<order;i++) {
		delete models[i];
	}
}