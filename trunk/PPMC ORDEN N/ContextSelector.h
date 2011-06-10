#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <string>

#include "PPMC.h"

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector();
			~ContextSelector(){};
			void add(char c);
			const std::string& getContext();
			void show();
		private:
			std::string context;
	};
}


#endif //_ppmc_context_selector_h_
