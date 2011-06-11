#include "FileReader.h"


using namespace util;
using namespace std;

FileReader::FileReader(const char* name){
	file.open(name);
	if (! file.good()) throw 1;
	buffer = new char[2048];
	cursor = 0;
	maxCursor = 0;
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
		file.read(buffer, 2048);
		maxCursor = file.gcount();
		cursor = 0;
	}
	return (maxCursor == 0);
}
