#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <string>
#include "util.h"
#include "IFileWriter.h"

namespace util {
	class FileWriter: public IFileWriter{
		public:
			FileWriter();
			~FileWriter();
			void write(char c);
			void write(std::string s);
		friend class FileWriterTest;
	};
}
#endif //_util_file_writer_h_