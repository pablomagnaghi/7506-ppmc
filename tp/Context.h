#ifndef _ppmc_context_h_
#define _ppmc_context_h_

#include <map>

#include "PPMC.h"

namespace ppmc {
	class Context {
		public:
			Context();
			~Context(){};
		private:
			size_t esc;
			std::map<char,size_t> freq;
		friend class ContextTest;

	};
}

#endif  // _ppmc_context_h_