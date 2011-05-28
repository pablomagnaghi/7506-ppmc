#ifndef _util_file_reader_h_
#define _util_file_reader_h_

#include <fstream>
#include "util.h"
#include "IFileReader.h"

namespace util {
	class FileReader: public IFileReader {
		public:
			FileReader(const char* name);
			virtual char read();
			virtual bool eof();
		private:
			std::ifstream file;
		friend class FileReaderTest;
	};
}
#endif //_util_file_reader_h_