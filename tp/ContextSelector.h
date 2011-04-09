#ifndef _context_selector_h_
#define _context_selector_h_

#include <stdexcept>
#include <string>
#include <cstddef>

#include "PPMC.h"

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector(size_t size);
			~ContextSelector(){};
			void set(std::string name);
			std::string get(size_t size);
		private:
			std::string contextName;
			size_t size;
			friend class ContextSelectorTest;
	};
}


#endif //_context_selector_h_