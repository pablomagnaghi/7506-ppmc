#include "FileReader.h"


using namespace util;
using namespace std;

FileReader::FileReader(const char* name, size_t bs){
	file.open(name);
	//if (! file.good()) throw 'c';
	bufferSize = bs;
	buffer     = new char[bufferSize];
	cursor     = 0;
	maxCursor  = 0;
	
}

FileReader::~FileReader() {
	delete[] buffer;
}

/**
 * @precondition: eof()
 *
 */
char FileReader::read(){
	return buffer[cursor++];
}

bool FileReader::eof(){
	if (cursor == maxCursor) {
		file.read(buffer, bufferSize);
		maxCursor = file.gcount();
		cursor = 0;
	}
	return (maxCursor == 0);
}
