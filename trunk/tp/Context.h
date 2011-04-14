#ifndef _ppmc_context_h_
#define _ppmc_context_h_

#include <map>

#include "PPMC.h"
#include "Response.h"
#include "Query.h"

namespace ppmc {
	class Context {
		public:
			Context();
			~Context(){};
		private:
			size_t esc;
			size_t count;
			std::map<char,size_t> freq;
			Response eval(Query q);
		friend class ContextTest;

	};
}

#endif  // _ppmc_context_h_