#ifndef _ppmc_model_h_
#define _ppmc_model_h_


#include <map>
#include <list>
#include <string>
#include "PPMC.h"
#include "FrequencyTable.h"

namespace ppmc {
	class Model {
		public:
			Model();
			~Model();
			FrequencyTable* find(const std::string& contextName);
			std::string show();
		private:
			std::map<std::string, FrequencyTable*> frequencyTables;
		
		friend class ModelTest;

	};
}

#endif  // _ppmc_model_h_