#include "FileWriter.h"
#include <netinet/in.h>

using namespace util;
using namespace std;

FileWriter::FileWriter(const char* name):IFileWriter(){
  file.open (name);
	if (! file.good()) throw 1;
}

FileWriter::~FileWriter(){
	file.close();
}
void FileWriter::write(char c){
	file << c;
	if (! file.good()) throw 1;
}
void FileWriter::write(std::string s){
	file << s;
	if (! file.good()) throw 1;
}

void FileWriter::write(u_int32_t buffer) {
	union adapter_type {
		u_int32_t byteOrdered;
		char buffer[4];
	} adapter;
	adapter.byteOrdered = htonl (buffer);
	for (int i = 0; i < 4; i++) {
		file << adapter.buffer[i];
		if (! file.good()) throw 1;
	}
}

void FileWriter::write(u_int64_t buffer) {
/*	union adapter_type {
		u_int64_t byteOrdered;
		char buffer[8];
	} adapter;

	adapter.byteOrdered = htonl (buffer);

	for (int i = 0; i < 8; i++) {
		file << adapter.buffer[i];
		if (! file.good()) throw 1;
	}*/
}