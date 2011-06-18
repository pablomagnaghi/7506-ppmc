#ifndef _ppmc_model_h_
#define _ppmc_model_h_

#include <map>
#include <list>
#include <string>
#include <sstream>

#include "PPMC.h"
#include "FrequencyTable.h"

using namespace std;

namespace ppmc {
	class Model {
		public:
			Model();
			~Model();
			FrequencyTable* find(const string&);
			string show();
			void update(const string&, u_int8_t);
			size_t getSize();
		private:
			map<string, FrequencyTable*> model;
			size_t size;
	};
}

#endif  // _ppmc_model_h_
