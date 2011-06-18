#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <string>

#include "PPMC.h"


namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector();
			~ContextSelector(){};
			void setOrder(size_t o);
			void add(char c);
			const std::string& getContext();
			void show();
		private:
			std::string context;
			size_t order;
	};
}


#endif //_ppmc_context_selector_h_
