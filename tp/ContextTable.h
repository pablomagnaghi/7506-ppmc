#ifndef _ppmc_context_table_h_
#define _ppmc_context_table_h_

#include <map>

#include "PPMC.h"
#include "Response.h"
#include "Query.h"

namespace ppmc {
	class ContextTable {
		public:
			ContextTable();
			~ContextTable(){};
			Response compress(Query q);
		private:
			size_t esc;
			size_t count;
			std::map<char,size_t> freq;
		friend class ContextTableTest;

	};
}

#endif  // _ppmc_context_table_h_