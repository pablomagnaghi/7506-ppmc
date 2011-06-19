#ifndef _util_mocked_file_reader_h_
#define _util_mocked_file_reader_h_

#include <string>

#include "util.h"
#include "IFileReader.h"

namespace util {
	class MockedFileReader: public IFileReader {
		public:
			MockedFileReader();
			~MockedFileReader();
			MockedFileReader(const std::string& dd);
			virtual char read();
			virtual bool eof();
		private:
			std::string data;
			std::string::iterator iter;
	};
}
#endif //_util_mocked_file_reader_h_