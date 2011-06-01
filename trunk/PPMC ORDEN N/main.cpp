#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "FileWriter.h"
#include "FileReader.h"

using namespace ppmc;
using namespace util;
using namespace std;

int main(int argc, char* argv[]) {
	FileReader r("/home/luispaniagua/Desktop/ABDABABABD.txt");
	FileWriter w("ABDABABABD.z");

	Compressor compresor(&r,&w);

	cout<<"Comprimiendo..."<<std::endl;

	char c = r.read();
	while (!r.eof() ) {
		compresor.compress(c);
		c = r.read();
	}
	
	compresor.compressEof();
	compresor.clean_buffer();
	return 0;

}
