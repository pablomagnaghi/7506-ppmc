#ifndef _ppmc_response_h_
#define _ppmc_response_h_

#include <list>
#include "PPMC.h"
#include "Probability.h"

namespace ppmc {
	class Response {
		public:
			Response();
			~Response();
			void setChar(char cc);
			void setExclusions(std::list<char> exc);
			std::list<char> getExclusions();
			void setProbability(Probability p);
			Probability getProbability();
			void setFound(bool f);
			bool isFound();
		private:
			std::list<char> exclusion;
			Probability p;
			bool found;
		friend class ResponseTest;
	};
}
#endif //_ppmc_response_h_