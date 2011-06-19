#include <iostream>
#include "ContextSelector.h"


using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(size_t contextSize) throw (std::length_error):size(contextSize){
#ifdef VERBOSE
	cerr << "---ContextSelector: new" << endl;
#endif
	if (size > max_models) {
		throw new length_error("Invalid size");
	}
}

void ContextSelector::add(char c) {
	name += c;
	if (name.size() > size) {
		name=name.substr(1);
	}
#ifdef VERBOSE
	cerr << "---ContextSelector: add " << c << " -> " << name << endl;
#endif
}

std::string ContextSelector::get(size_t contextSize) throw (std::length_error) {
	if (contextSize > size ) {
		throw new length_error("Invalid size");
	}
#ifdef VERBOSE	
	cerr << "---ContextSelector: get " << contextSize << " -> ";
#endif
	if (contextSize == 0 || name.size() == 0) {
#ifdef VERBOSE
		cerr << "(empty)" << endl;
#endif
		return "";
	}
#ifdef VERBOSE
	cerr << name.substr(name.size() - contextSize ) << endl;
#endif
	return name.substr(name.size() - contextSize );
}
