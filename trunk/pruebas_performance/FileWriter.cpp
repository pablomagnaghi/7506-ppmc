#include "FileWriter.h"
#include <netinet/in.h>

using namespace util;
using namespace std;

FileWriter::FileWriter(const char* name){
	file.open (name);
	if (! file.good()) throw 1;
	bufferSize = 2048;
	buffer = new char[bufferSize];
	cursor = 0;
	
}

FileWriter::~FileWriter(){
	if (cursor) {
		file.write(buffer,cursor);
	}
	file.close();
	delete[] buffer;
}
void FileWriter::write(char c){
	if (cursor < bufferSize) {
		buffer[cursor++] = c;
	} else {
		file.write(buffer,bufferSize);
		cursor = 0;
		write(c);
	}
}
