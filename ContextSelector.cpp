#include "ContextSelector.h"

using namespace ppmc;

ContextSelector::ContextSelector(size_t o):orden(o){

}

void ContextSelector::add(char c) {
	context += c;
	if (context.size() > orden) {
		context = context.substr(1);
	}
}

const string& ContextSelector::getContext() {
	return context;
}

void ContextSelector::show() {
	cout << context << endl;
}
