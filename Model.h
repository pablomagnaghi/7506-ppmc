#ifndef _ppmc_model_h_
#define _ppmc_model_h_

#include <map>
#include <string>
#include <algorithm>
#include "PPMC.h"
#include "FrequencyTable.h"

namespace ppmc {
	class Model {
		public:
			Model();
			~Model();
			FrequencyTable* find(const std::string&);
			std::string show();
			void update(const std::string&, u_int8_t);
			size_t getSize();
		private:
			std::map<std::string, FrequencyTable*> model;
			size_t size;
	};
}

#endif  // _ppmc_model_h_
