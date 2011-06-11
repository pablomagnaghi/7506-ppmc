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
			FrequencyTable* find(const std::string&);
			void show();
			void update(const std::string&, char);
			std::size_t getSize();
		private:
			std::map<std::string, FrequencyTable*> model;
			std::size_t size;
	};
}

#endif  // _ppmc_model_h_
