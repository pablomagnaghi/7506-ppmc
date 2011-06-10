#include <iostream>
#include <stdexcept>
#include "FileReader.h"

using namespace util;
using namespace std;

int main(int argc, char* argv[]) {
	FileReader reader(argv[1]);

	size_t count = 0;
	while (!reader.eof() ) {
		++count;
		char c = reader.read();
	}
		
	cout << count << endl;
}
