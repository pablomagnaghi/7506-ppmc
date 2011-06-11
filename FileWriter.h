#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <fstream>
#include <cstdlib>

#include "util.h"
#include "IFileWriter.h"

namespace util {
	class FileWriter:public IFileWriter{
		public:
			FileWriter(const char* name, size_t bs);
			~FileWriter();
			void write(char c);
			void write(std::string s);
		private:
			char* buffer;
			size_t cursor;
			size_t bufferSize;
			std::ofstream file;
	};
}
#endif //_util_file_writer_h_
