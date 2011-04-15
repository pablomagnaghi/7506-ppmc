#ifndef _ppmc_query_h_
#define _ppmc_query_h_

#include <set>
#include "PPMC.h"
#include "Probability.h"

namespace ppmc {
	class Query {
		public:
			Query();
			~Query();

			void addExclusion(char c);
			bool isExcluded(char c);
			
			void setFound(bool f);
			bool isFound();
			
			void setChar(char cc);
			char getChar();
			
			Probability getProbability();
			void setProbability(Probability pp);
			
		private:
			std::set<char> exclusion;
			bool found;
			char c;
			Probability p;
		friend class QueryTest;
	};
}
#endif //_ppmc_query_h_