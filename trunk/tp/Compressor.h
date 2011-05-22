#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
#include "IFileWriter.h"
#include "IFileReader.h"


namespace ppmc {
	class Compressor:public Arithmetic {
		public:
			Compressor(size_t o);
			~Compressor();
			void compress(util::IFileReader* reader, util::IFileWriter* writer);
		friend class CompressorTest;
	};
}
#endif //_ppmc_compressor_h_