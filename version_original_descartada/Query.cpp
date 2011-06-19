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
#ifdef EXTRA_VERBOSE
		cerr << "+++ excluding " << c << " from ";
		std::set<char>::iterator it;
		for (it=exclusion.begin(); it!= exclusion.end(); ++it) {
			cerr << *it <<", " ;
		}
		cerr << endl;
#endif
		exclusion.insert(c);
	}
}

bool Query::isExcluded(char c){
// 	if (exclusion.end() != exclusion.find(c)) {
// 		std::set<char>::iterator it;
// 		cerr << "+++ " << c << " excluded from ";
// 		for (it=exclusion.begin(); it!= exclusion.end(); ++it) {
// 			cerr << *it <<", " ;
// 		}
// 		cerr <<endl;
// 	}
	
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