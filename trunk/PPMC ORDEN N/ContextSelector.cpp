#include "ContextSelector.h"

using namespace ppmc;

ContextSelector::ContextSelector(){

}

void ContextSelector::add(char c) {
	context += c;
	if (context.size() > ORDEN) {
		context = context.substr(1);
	}
}

const std::string& ContextSelector::getContext() {
	return context;
}

void ContextSelector::show() {
	std::cout << context << std::endl;
}
