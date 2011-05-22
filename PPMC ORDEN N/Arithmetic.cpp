#include "Arithmetic.h"


using namespace ppmc;
using namespace std;

Arithmetic::Arithmetic(){
	for (size_t i=0; i<(ORDEN + 1);i++) {
		models.push_back(new Model());
	}
}

Arithmetic::~Arithmetic(){
	for (size_t i=0; i<(ORDEN + 1);i++) {
		delete models[i];
	}
}
