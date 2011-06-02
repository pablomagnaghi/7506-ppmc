#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include "PPMC.h"
#include "Arithmetic.h"
#include "Probability.h"
#include "Query.h"
#include "ContextSelector.h"

namespace ppmc {
	class Compressor:public Arithmetic {
		public:
			Compressor(size_t o);
			~Compressor();
			void compress(util::IFileReader* r, util::IFileWriter* w);
			void calculate(Probability& p);
		private:
			Query q;
			static size_t increasingOrder;
			void compressWithM_1(ContextSelector& cs, char c);
			void compressWithModels(ContextSelector& cs);
			void compressEof(ContextSelector& cs);
		friend class CompressorTest;
	};
}
#endif //_ppmc_compressor_h_