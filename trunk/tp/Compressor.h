#ifndef _ppmc_compressor_h_
#define _ppmc_compressor_h_

#include <vector>
#include "PPMC.h"
#include "Model.h"


namespace ppmc {
	class Compressor {
		public:
			Compressor();
			~Compressor();
		private:
			std::vector<Model> models;
		friend class CompressorTest;
	};
}
#endif //_ppmc_compressor_h_