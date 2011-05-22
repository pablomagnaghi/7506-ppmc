#ifndef _ppmc_frequency_table_h_
#define _ppmc_frequency_table_h_

#include <map>

#include "PPMC.h"
#include "Query.h"

namespace ppmc {
	class FrequencyTable {
		public:
			FrequencyTable();
			~FrequencyTable(){};
			void compress(Query &q);
		private:
			std::map<char,size_t> freq;
		friend class FrequencyTableTest;

	};
}

#endif  // _ppmc_frequency_table_h_