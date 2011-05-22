#ifndef _ppmc_m_1frequency_table_h_
#define _ppmc_m_1frequency_table_h_

#include <map>

#include "PPMC.h"
#include "Query.h"
#include "FrequencyTable.h"

namespace ppmc {
	class M_1FrequencyTable:public FrequencyTable {
		public:
			M_1FrequencyTable();
			virtual ~M_1FrequencyTable(){};
			virtual void compress(Query &q);
		friend class M_1FrequencyTableTest;

	};
}

#endif  // _ppmc_m_1frequency_table_h_