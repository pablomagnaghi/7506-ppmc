#include "Arithmetic.h"


using namespace ppmc;
using namespace std;

Arithmetic::Arithmetic(){
	for (size_t i=0; i<order;i++) {
		models.push_back(new Model);
	}
}

Arithmetic::~Arithmetic(){
	//No need to delete models content as it is calling the destructors by itself

}