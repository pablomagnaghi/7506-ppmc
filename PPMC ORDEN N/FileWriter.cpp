#include <netinet/in.h>
#include "FileWriter.h"

using namespace util;

FileWriter::FileWriter(const char* name, size_t bs){
	file.open (name);
	if (! file.good()) throw 1;
	bufferSize = bs;
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

void FileWriter::writeSizeInHeader(size_t size) {
	union adapter_type {
		u_int32_t byteOrdered;
		char buffer[4];
	} adapter;
	adapter.byteOrdered = htonl (size);
	file.write(buffer,4);
}

