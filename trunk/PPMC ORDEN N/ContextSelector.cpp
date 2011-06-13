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

const string& ContextSelector::getContext() {
	return context;
}

void ContextSelector::show() {
	cout << context << endl;
}
