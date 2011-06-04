#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Uncompressor.h"

using namespace ppmc;
using namespace util;
using namespace std;

int main(int argc, char* argv[]) {
//	FileReader r("/home/luis/Escritorio/ABDABABABD.txt");
//	FileWriter w("/home/luis/Escritorio/ABDABABABD.ttt");
//	Compressor compresor(&r,&w);
//
//	cout<<"Comprimiendo..."<<std::endl;
//
//	char c = r.read();
//	while (!r.eof() ) {
//		compresor.compress(c);
//		c = r.read();
//	}
//
//	compresor.compressEof();
//	compresor.clean_buffer();


	FileReader r("/home/luis/Escritorio/ABDABABABD.ttt");
	FileWriter w("/home/luis/Escritorio/ABDABABABD.luis");
	Uncompressor uncompressor(&r, &w);
	uncompressor.uncompress();
	
	return 0;

}
