#include "Query.h"


using namespace ppmc;
using namespace std;

Query::Query(){

}

Query::~Query(){


}

void Query::addExclusion(char c){
	exclusion.insert(c);
}

bool Query::isExcluded(char c){
	set<char>::iterator it;
	it=exclusion.find(c);
	return it!=exclusion.end();
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