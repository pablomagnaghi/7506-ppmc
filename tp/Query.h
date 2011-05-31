#ifndef _ppmc_query_h_
#define _ppmc_query_h_

//#include <string>
#include <set>
#include "PPMC.h"
#include "Probability.h"

namespace ppmc {
	class Query {
		public:
			Query();
			~Query();

			void clear();
			
			void addExclusion(char c);
			bool isExcluded(char c);
			
			void setFound(bool f);
			bool isFound();
			
			void setTerm(char cc);
			char getTerm();
			
			Probability getProbability();
			void setProbability(Probability pp);

			probabilityType getExclusionSize();
		private:
			//std::string exclusion;
			std::set<char> exclusion;
			bool found;
			char c;
			Probability p;
			Query( const Query& q );
			Query& operator=( const Query& q );
		friend class QueryTest;
	};
}
#endif //_ppmc_query_h_