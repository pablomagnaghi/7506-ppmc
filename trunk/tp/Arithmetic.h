#ifndef _ppmc_arithmetic_h_
#define _ppmc_arithmetic_h_

#include <vector>
#include "PPMC.h"
#include "Model.h"


namespace ppmc {
	class Arithmetic {
		public:
			Arithmetic();
			virtual ~Arithmetic();
		protected:
			std::vector<Model*> models;
			size_t order;
		friend class CompressorTest;
	};
}
#endif //_ppmc_arithmetic_h_