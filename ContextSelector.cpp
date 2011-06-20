#include "ContextSelector.h"

using namespace ppmc;
using namespace std;

ContextSelector::ContextSelector(){

}

void ContextSelector::setOrder(size_t o){
	order= o;
}

void ContextSelector::add(char c) {
	context += c;
	if (context.size() > order) {
		context = context.substr(1);
	}
}

const string& ContextSelector::getContext() {
	return context;
}

void ContextSelector::show() {
	cout << context << endl;
}
