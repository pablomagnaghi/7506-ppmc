#ifndef _util_i_file_writer_h_
#define _util_i_file_writer_h_

#include <string>
#include "util.h"

namespace util {
	class IFileWriter {
		public:
			virtual ~IFileWriter(){};
			virtual void write(char c)=0;
			virtual void write(std::string s)=0;
	};
}
#endif //_util_i_file_writer_h_