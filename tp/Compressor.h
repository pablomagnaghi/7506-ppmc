#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
#include "FileWriter.h"
#include "FileReader.h"


namespace ppmc {
	class Compressor:public Arithmetic {
		public:
			Compressor();
			~Compressor();
			void compress(util::FileReader& reader, util::FileWriter& writer);
		friend class CompressorTest;
	};
}
#endif //_ppmc_compressor_h_