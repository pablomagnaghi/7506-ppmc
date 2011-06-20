#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include <fstream>

namespace util {
	class FileWriter{
		public:
			FileWriter(const char* name, size_t bs);
			~FileWriter();
			void write(char c);
			void writeHeader(size_t o, size_t size);
		private:
			char* buffer;
			size_t cursor;
			size_t bufferSize;
			std::ofstream file;
	};
}
#endif //_util_file_writer_h_
