#ifndef _util_mocked_file_writer_h_
#define _util_mocked_file_writer_h_

#include <sstream>
#include "util.h"
#include "IFileWriter.h"

namespace util {
	class MockedFileWriter: public IFileWriter {
		public:
			MockedFileWriter();
			~MockedFileWriter();
			virtual void write(char c);
			virtual void write(std::string s);
			std::string get();
		private:
			std::stringstream data;
	};
}
#endif //_util_mocked_file_writer_h_