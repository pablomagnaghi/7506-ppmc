#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <string>
#include <fstream>
#include <cstdlib>

#include "util.h"

namespace util {
	class FileWriter{
		public:
			FileWriter(const char* name);
			~FileWriter();
			void write(char c);
		private:
			char* buffer;
			size_t cursor;
			size_t bufferSize;
			std::ofstream file;
	};
}
#endif //_util_file_writer_h_
