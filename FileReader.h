#ifndef _util_file_reader_h_
#define _util_file_reader_h_

#include <fstream>
#include "util.h"
#include "IFileReader.h"


namespace util {
	class FileReader:public IFileReader {
		public:
			FileReader(const char* name,size_t bs);
			~FileReader();
			virtual char read();
			virtual bool eof();
		private:
			char* buffer;
			size_t cursor;
			size_t maxCursor;
			size_t bufferSize;
			std::ifstream file;
	};
}
#endif //_util_file_reader_h_
