#include "Query.h"


using namespace ppmc;
using namespace std;

Query::Query(){

}

Query::~Query(){


}

void Query::setChar(char cc) {
	c=cc;
}

char Query::getChar(){
	return c;
}

std::list<char> Query::getExclusions() {
	return exclusion;
}

void Query::setExclusions(std::list<char> exc) {
	exclusion = exc;
}
