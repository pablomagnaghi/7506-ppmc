#ifndef _ppmc_model_h_
#define _ppmc_model_h_


#include <map>
#include <list>
#include <string>
#include "PPMC.h"
#include "Context.h"

namespace ppmc {
	class Model {
		public:
			Model();
			~Model();
		private:
			std::map<std::string, Context*> contexts;
		
		friend class ModelTest;

	};
}

#endif  // _ppmc_model_h_