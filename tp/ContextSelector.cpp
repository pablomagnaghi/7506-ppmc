#include <iostream>
#include "ContextSelector.h"


using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(size_t contextSize) throw (std::length_error):size(contextSize){
	if (size > max_models) {
		throw new length_error("Invalid size");
	}
}

void ContextSelector::add(char c) {
	name += c;
	if (name.size() > size) {
		name=name.substr(1);
	}
}

std::string ContextSelector::get(size_t contextSize) throw (std::length_error) {
	if (contextSize > size ) {
		throw new length_error("Invalid size");
	}
	return name.substr(name.size() - contextSize );
}
