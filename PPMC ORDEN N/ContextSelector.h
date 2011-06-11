#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <stdexcept>
#include <string>

#include "PPMC.h"

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector();
			~ContextSelector(){};
			void add(char c);
			std::string getContext();
			void show();
		private:
			std::string context;
	};
}


#endif //_ppmc_context_selector_h_
