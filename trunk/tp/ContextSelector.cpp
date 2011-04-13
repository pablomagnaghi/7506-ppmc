#include <iostream>
#include "ContextSelector.h"


using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(size_t contextSize) throw (std::length_error):size(contextSize){
	if (size > max_models) {
		throw new length_error("Invalid size");
	}
}

void ContextSelector::set(std::string contextName) throw (std::length_error) {
	if (contextName.size() > size) {
		throw new length_error("String to big");
	}
	name = contextName;
}

void ContextSelector::add(char c) {
	name += c;
}

void ContextSelector::add(std::string s) {
	name += s;
}

std::string ContextSelector::get(size_t contextSize) throw (std::length_error) {
	if (contextSize > size ) {
		throw new length_error("Invalid size");
	}
	return name.substr(contextSize);
}
