#include <sys/stat.h>
#include <netinet/in.h>

#include "FileReader.h"

using namespace util;
using namespace std;

FileReader::FileReader(const char* name, size_t bs){
	file.open(name);
	if (! file.good()) throw ios_base::failure("no se pudo abrir archivo de entrada");
	bufferSize = bs;
	buffer     = new char[bufferSize];
	cursor     = 0;
	maxCursor  = 0;
	
	size_t begin = file.tellg();
	file.seekg (0, ios::end);
	size_t end = file.tellg();
	size = end - begin;
	file.seekg(0,ios::beg);
}

FileReader::~FileReader() {
	delete[] buffer;
}

/**
 * @precondition eof()
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

size_t FileReader::getSize(){
	return size;
}

size_t FileReader::getSizeFromHeader(){
	union adapter_type {
		u_int32_t byteOrdered;
		char buffer[4];
	} adapter;
	file.read(adapter.buffer,4);
	return ntohl(adapter.byteOrdered);
}