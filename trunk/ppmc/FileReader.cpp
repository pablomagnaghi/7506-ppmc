#include <sys/stat.h>
#include <vector>

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

pair<char,size_t> FileReader::getSizeFromHeader(){
	char oneCharBuffer[1] = {0};
	vector<char> tr;
	size_t size = 0;
	char order[1];
	file.read(order,1);
	while (oneCharBuffer[0] >= 0 ) {
		file.read(oneCharBuffer,1);
		tr.push_back(oneCharBuffer[0]);
	}
	
	file.seekg(tr.size() + 1 ,ios::beg);
	
	int mult = 1;
	unsigned int i;
	for(i=0; i < tr.size() -1 ; ++i) {
		size += tr[i] * mult;
		mult *= 128;
	}
	tr[i] -= 128;
	size += tr[i] * mult;
	
	return make_pair(order[0],size) ;
}

