#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <string>
#include <fstream>
#include <cstdlib>

#include "util.h"
#include "IFileWriter.h"

namespace util {
	class FileWriter: public IFileWriter{
		public:
			FileWriter(const char* name);
			~FileWriter();
			void write(char c);
			void write(std::string s);
			void write(u_int32_t buffer);
			void write(u_int64_t buffer);
		private:
			std::ofstream file;
		friend class FileWriterTest;
	};
}
#endif //_util_file_writer_h_