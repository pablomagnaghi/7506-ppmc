#ifndef _util_file_reader_h_
#define _util_file_reader_h_

#include <fstream>
#include <utility>

namespace util {
	class FileReader {
		public:
			FileReader(const char* name,size_t bs);
			~FileReader();
			virtual char read();
			virtual bool eof();
			size_t getSize();
			std::pair<char,size_t> getSizeFromHeader();
		private:
			char* buffer;
			size_t cursor;
			size_t maxCursor;
			size_t bufferSize;
			size_t size;
			std::ifstream file;
	};
}
#endif //_util_file_reader_h_
