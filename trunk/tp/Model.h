#ifndef _ppmc_model_h_
#define _ppmc_model_h_


#include <map>
#include <list>
#include <string>
#include "PPMC.h"
#include "ContextTable.h"
#include "ContextSelector.h"

namespace ppmc {
	class Model {
		public:
			Model();
			~Model();
			ContextTable* find(ContextSelector& cs, size_t depth);
		private:
			std::map<std::string, ContextTable*> contextTables;
		
		friend class ModelTest;

	};
}

#endif  // _ppmc_model_h_