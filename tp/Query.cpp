#include "Query.h"


using namespace ppmc;
using namespace std;

Query::Query(){

}

Query::~Query(){


}

std::list<char> Query::getExclusions() {
	return exclusion;
}

void Query::setExclusions(std::list<char> exc) {
	exclusion = exc;
}

Probability Query::getProbability(){
	return p;
}

void Query::setProbability(Probability pp){
	p = pp;
}

char Query::getChar(){
	return c;
}

void Query::setChar(char cc){
	c = cc;
}

bool Query::isFound(){
	return found;
}

void Query::setFound(bool f){
	found = f;
}