#include <netinet/in.h>
#include <vector>

#include "FileWriter.h"


using namespace util;

FileWriter::FileWriter(const char* name, size_t bs){
	file.open (name);
	if (! file.good()) throw ios_base::failure("no se pudo abrir archivo de salida");
	bufferSize = bs;
	buffer = new char[bufferSize];
	if (!buffer) throw bad_alloc();
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
	vector<unsigned char> buffer;
	
	while (size > 127) {
		size_t chunk = size % 128;
		buffer.push_back( (unsigned char) chunk);
		size /= 128;
	}
	
	size += 128;
	buffer.push_back( (unsigned char) size);
	
	char * last = new char[buffer.size()];
	
	copy(buffer.begin(), buffer.end(), last);

	file.write(last,buffer.size());
	delete[] last;
}

