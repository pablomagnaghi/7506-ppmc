#include <iostream>
#include "ContextSelector.h"


using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(size_t contextSize) throw (std::length_error):size(contextSize){
	cerr << "---ContextSelector: new" << endl;
	if (size > max_models) {
		throw new length_error("Invalid size");
	}
}

void ContextSelector::add(char c) {
	name += c;
	if (name.size() > size) {
		name=name.substr(1);
	}
	cerr << "---ContextSelector: add " << c << " -> " << name << endl;
}

std::string ContextSelector::get(size_t contextSize) throw (std::length_error) {
	if (contextSize > size ) {
		throw new length_error("Invalid size");
	}
	cerr << "---ContextSelector: get " << contextSize << " -> ";
	if (contextSize == 0 || name.size() == 0) {
		cerr << "(empty)" << endl;
		return "";
	}
	cerr << name.substr(name.size() - contextSize ) << endl;
	return name.substr(name.size() - contextSize );
}
