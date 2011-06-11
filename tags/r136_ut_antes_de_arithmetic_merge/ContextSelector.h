#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <stdexcept>
#include <string>

#include "PPMC.h"

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector(size_t contextSize) throw (std::length_error);
			~ContextSelector(){};
			void add(char c);
			std::string get(size_t contextSize) throw (std::length_error);
		private:
			std::string name;
			size_t size;
		friend class ContextSelectorTest;
	};
}


#endif //_ppmc_context_selector_h_
