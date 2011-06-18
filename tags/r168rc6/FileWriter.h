#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <fstream>
#include <cstdlib>
#include <netinet/in.h>

#include "util.h"

using namespace std;

namespace util {
	class FileWriter{
		public:
			FileWriter(const char* name, size_t bs);
			~FileWriter();
			void write(char c);
			void writeSizeInHeader(size_t o, size_t size);
		private:
			char* buffer;
			size_t cursor;
			size_t bufferSize;
			ofstream file;
	};
}
#endif //_util_file_writer_h_
