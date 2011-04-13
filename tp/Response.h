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
		private:
			std::list<char> exclusion;
			Probability p;
		friend class ResponseTest;
	};
}
#endif //_ppmc_response_h_