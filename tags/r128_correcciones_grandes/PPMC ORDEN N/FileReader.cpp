#include "FileReader.h"


using namespace util;
using namespace std;

FileReader::FileReader(const char* name){
	file.open(name);
	if (! file.good()) throw FileErrorOpenForReading();
}

char FileReader::read(){
	char c;
	if (! file.good()) throw FileErrorRead();
	file >> c;
	return c;
}

bool FileReader::eof(){
	return file.eof();
}