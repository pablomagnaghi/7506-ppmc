#include "FileReader.h"


using namespace util;
using namespace std;

FileReader::FileReader(const char* name){
	file.open(name);
	if (! file.good()) throw 1;
}

char FileReader::read(){
	char c;
	file >> c;
	if (! file.good()) throw 1;
	return c;
}

bool FileReader::eof(){
	return file.eof();
}