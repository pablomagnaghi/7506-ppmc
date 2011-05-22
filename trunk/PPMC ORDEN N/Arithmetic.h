#ifndef _ppmc_arithmetic_h_
#define _ppmc_arithmetic_h_

#include <vector>
#include "PPMC.h"
#include "Model.h"
#include "ContextSelector.h"

namespace ppmc {
	class Arithmetic {
		public:
			Arithmetic();
			virtual ~Arithmetic();
		protected:
			std::vector<Model*> models;
			ContextSelector contextSelector;
			FrequencyTable frequencyTable;
			//std::map<char, std::size_t> table;
			// necesito mapa de probabilidades, <frecuencia, total>
	};
}
#endif //_ppmc_arithmetic_h_
