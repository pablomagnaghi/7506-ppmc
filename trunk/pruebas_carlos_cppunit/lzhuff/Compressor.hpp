#ifndef _lzHuff_compressor_hpp_
#define _lzHuff_compressor_hpp_
#include "LzHuff.hpp"
#include <string>
#include <vector>

#include "../../tp/IFileWriter.h"
#include "../../tp/IFileReader.h"

namespace lzHuff {
	class Compressor {
		public:
			Compressor(size_t ws,size_t min_m, size_t max_m);
			void compress(util::IFileReader* reader, util::IFileWriter* writer);
			void decompress(util::IFileReader* reader, util::IFileWriter* writer);
		private:
			std::string window;
			size_t window_size;
			size_t min_match;
			size_t max_match;
			void windowAdd(char c);
/*			std::vector<std::string>* code_table;
			std::string last_match;*/
// 			bool find(std::string match);
// 			void add(std::string match);
// 			std::string encode(std::string match);
// 			std::string decode(std::string match);
// 			std::string compressedRead(util::IFileReader* reader);
		friend class CompressorTest;
	};
}

#endif // _lzHuff_compressor_hpp_