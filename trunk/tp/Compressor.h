#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
namespace ppmc {
	class Compressor:public Arithmetic {
		public:
			Compressor();
			~Compressor();
		friend class CompressorTest;
	};
}
#endif //_ppmc_compressor_h_