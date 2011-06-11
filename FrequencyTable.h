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
			virtual void compress(Query &q);
			virtual void compressEof(Query &q);
			std::string show();
		protected:
			probabilityType calculateAndUpdateWidth(char c);
			probabilityType calculateSkip(Query& q);
			probabilityType calculateEscWidth(Query& q);
			probabilityType calculateSkipEof(Query& q);
			probabilityType calculateTotal(Query& q);
		private:
			std::map<char,size_t> freq;
			void insert(char c);
			void updateExclusion(Query& q);
		friend class FrequencyTableTest;
	};
}

#endif  // _ppmc_frequency_table_h_