#ifndef _util_file_reader_h_
#define _util_file_reader_h_

#include "util.h"
#include "IFileReader.h"

namespace util {
	class FileReader: public IFileReader {
		public:
			virtual char read();
		friend class FileReaderTest;
	};
}
#endif //_util_file_reader_h_