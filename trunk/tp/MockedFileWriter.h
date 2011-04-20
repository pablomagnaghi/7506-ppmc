#ifndef _util_mocked_file_writer_h_
#define _util_mocked_file_writer_h_

#include <string>
#include "util.h"
#include "IFileWriter.h"

namespace util {
	class MockedFileWriter: public IFileWriter {
		public:
			MockedFileWriter();
			~MockedFileWriter();
			virtual void write(char c);
		private:
			std::string data;
	};
}
#endif //_util_mocked_file_writer_h_