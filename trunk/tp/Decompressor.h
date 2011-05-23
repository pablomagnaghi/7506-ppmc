#ifndef _ppmc_decompressor_h_
#define _ppmc_decompressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
#include "IFileWriter.h"
#include "IFileReader.h"

namespace ppmc {
	class Decompressor:public Arithmetic {
		public:
			Decompressor(size_t o);
			~Decompressor();
			void decompress(util::IFileReader* reader, util::IFileWriter* writer);
		friend class DecompressorTest;
	};
}
#endif //_ppmc_decompressor_h_