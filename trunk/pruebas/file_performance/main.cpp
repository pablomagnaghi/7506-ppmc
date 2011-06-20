#include <cstdlib>

#include "FileReader.h"
#include "FileWriter.h"

using namespace util;
using namespace std;

int main(int argc, char* argv[]) {
	FileReader reader(argv[1],atoi(argv[3]));
	FileWriter writer(argv[2],atoi(argv[3]));
	size_t count = 0;
	while (!reader.eof() ) {
		++count;
		writer.write(reader.read());
	}
}
