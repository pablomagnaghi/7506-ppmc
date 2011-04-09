#include "ContextSelector.h"

using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(size_t size):size(size){
	if (size < 0) throw new length_error("Invalid size");
}

void ContextSelector::set(std::string name) {
	if (name.size() > size) {
		throw new length_error("String to big");
	}
	contextName = name;
}

std::string ContextSelector::get(size_t size) {
	if (size > size || size < 0) {
		throw new length_error("Invalid size");
	}
	return contextName;
}
