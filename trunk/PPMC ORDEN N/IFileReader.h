#ifndef _util_i_file_reader_h_
#define _util_i_file_reader_h_

#include "util.h"

namespace util {
	class IFileReader {
		public:
			virtual ~IFileReader(){};
			virtual char read()=0;
			virtual bool eof()=0;
	};
}
#endif //_util_i_file_reader_h_