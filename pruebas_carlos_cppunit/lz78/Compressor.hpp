#ifndef _lz78_compressor_hpp_
#define _lz78_compressor_hpp_
#include "Lz78.hpp"
#include <string>
#include <vector>

#include "../../tp/IFileWriter.h"
#include "../../tp/IFileReader.h"

namespace lz78 {
	class Compressor {
		public:
			Compressor(size_t mb);
			void compress(util::IFileReader* reader, util::IFileWriter* writer);
			void decompress(util::IFileReader* reader, util::IFileWriter* writer);
		private:
			size_t max_bits;
			size_t bits;
			size_t cache;
			std::vector<std::string>* code_table;
			bool find(std::string match);
			void add(std::string match);
			std::string encode(std::string match);
			std::string decode(std::string match);
			std::string compressedRead(util::IFileReader* reader);
		friend class CompressorTest;
	};
}

#endif // _lz78_compressor_hpp_