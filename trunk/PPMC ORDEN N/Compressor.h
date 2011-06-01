#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include "PPMC.h"
#include "Arithmetic.h"

namespace ppmc {
	class Compressor:public Arithmetic {
		public:
			Compressor(util::FileReader* r, util::FileWriter* w);
			~Compressor();
			void compress(u_int8_t);
			void compressEof();
	};
}
#endif //_ppmc_compressor_h_
