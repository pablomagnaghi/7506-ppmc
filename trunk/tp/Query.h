#ifndef _ppmc_query_h_
#define _ppmc_query_h_

#include <list>
#include "PPMC.h"

namespace ppmc {
	class Query {
		public:
			Query();
			~Query();
			void setChar(char cc);
			void setExclusions(std::list<char> exc);
			std::list<char> getExclusions();
		private:
			std::list<char> exclusion;
			char c;
		friend class QueryTest;
	};
}
#endif //_ppmc_query_h_