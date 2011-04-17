#ifndef _ppmc_context_table_h_
#define _ppmc_context_table_h_

#include <map>

#include "PPMC.h"
#include "Query.h"

namespace ppmc {
	class ContextTable {
		public:
			ContextTable();
			~ContextTable(){};
			void compress(Query &q);
		private:
			std::map<char,size_t> freq;
		friend class ContextTableTest;

	};
}

#endif  // _ppmc_context_table_h_