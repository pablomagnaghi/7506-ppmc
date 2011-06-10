#include "FileReader.h"


using namespace util;
using namespace std;

FileReader::FileReader(const char* name){
	file.open(name);
	if (! file.good()) throw 1;
}

char FileReader::read(){
	char c;
	if (! file.good()) throw 1;
	c = file.get();
	return c;
}

bool FileReader::eof(){
	return file.eof();
}
