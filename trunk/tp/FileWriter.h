#ifndef _util_file_writer_h_
#define _util_file_writer_h_

#include "util.h"
#include "IFileWriter.h"

namespace util {
	class FileWriter: public IFileWriter{
		public:
			FileWriter();
			~FileWriter();
			void write(char c);
		friend class FileWriterTest;
	};
}
#endif //_util_file_writer_h_