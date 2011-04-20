#include <iostream>
#include "PPMC.h"
#include "Compressor.h"
#include "MockedFileReader.h"
#include "FileWriter.h"
using namespace ppmc;
using namespace util;

int main(int argc, char* argv[]) {
	MockedFileReader* in = new MockedFileReader("aabac");
	FileWriter* out = new FileWriter();
	Compressor c;
	c.compress(*in, *out);

}
