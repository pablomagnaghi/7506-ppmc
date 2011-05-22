#ifndef _ppmc_compressor_h_
#define _ppmc_decompressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
namespace ppmc {
	class Decompressor:public Arithmetic {
		public:
			Decompressor(size_t o);
			~Decompressor();
		friend class DecompressorTest;
	};
}
#endif //_ppmc_compressor_h_