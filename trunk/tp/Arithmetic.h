#ifndef _ppmc_arithmetic_h_
#define _ppmc_arithmetic_h_

#include <vector>

#include "PPMC.h"
#include "Model.h"

/**
 * unsigned long int depende de la arquitectura, asi que no lo podemos usar.
 * Usamos unsigned int en lugar de unsigned long long int pues sino 
 * necesitariamos dos implementaciones
 */
namespace ppmc {
	class Arithmetic {
		public:
			Arithmetic(size_t o);
			virtual ~Arithmetic();
		protected:
			std::vector<Model*> models;
			size_t order;
			unsigned int ceiling;
			unsigned int floor;
		friend class CompressorTest;
	};
}
#endif //_ppmc_arithmetic_h_