#include "Response.h"


using namespace ppmc;
using namespace std;

Response::Response():found(false){

}

Response::~Response(){


}

std::list<char> Response::getExclusions() {
	return exclusion;
}

void Response::setExclusions(std::list<char> exc) {
	exclusion = exc;
}

Probability Response::getProbability(){
	return p;
}

void Response::setProbability(Probability pp){
	p = pp;
}

void Response::setFound(bool f) {
	found = f;
}

bool Response::isFound() {
	return found;
}