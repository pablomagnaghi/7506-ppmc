#include "FileReader.h"
#include <iostream>

using namespace util;
using namespace std;

FileReader::FileReader(const char* name){
	file.open(name);
	if (! file.good()) throw FileErrorOpenForReading();
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
	//cout << "R" << endl;
	//if (! file.good()) throw FileErrorRead();
	return buffer[cursor++];
}

bool FileReader::eof(){
	//cout << "E";
	if (cursor == maxCursor) {
		//cout << "M";
		file.read(buffer, 2048);
		maxCursor = file.gcount();
		cursor = 0;
	}
	return (maxCursor == 0);
}