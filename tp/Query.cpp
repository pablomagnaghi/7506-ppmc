#include "Query.h"


using namespace ppmc;
using namespace std;

Query::Query(){
	clear();
}

Query::~Query(){

}

void Query::clear(){
	setFound(false);
	exclusion.clear();
}


probabilityType Query::getExclusionSize(){
	return (probabilityType) exclusion.size();
}

void Query::addExclusion(char c){
	if (! isExcluded(c)) {
		exclusion.insert(c);
	}
}

bool Query::isExcluded(char c){
	return ( exclusion.end() != exclusion.find(c));
}

Probability Query::getProbability(){
	return p;
}

void Query::setProbability(Probability pp){
	p = pp;
}

char Query::getTerm(){
	return c;
}

void Query::setTerm(char cc){
	c = cc;
}

bool Query::isFound(){
	return found;
}

void Query::setFound(bool f){
	found = f;
}