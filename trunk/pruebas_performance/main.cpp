#include <iostream>
#include <stdexcept>
#include "FileReader.h"
#include "FileWriter.h"

using namespace util;
using namespace std;

int main(int argc, char* argv[]) {
	FileReader reader(argv[1]);
	FileWriter writer(argv[2]);

	size_t count = 0;
	while (!reader.eof() ) {
		++count;
		char c = reader.read();
		writer.write(c);
	}
		
	cout << count << endl;
}
