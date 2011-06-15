#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <string>

#include "PPMC.h"

using namespace std;

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector();
			~ContextSelector(){};
			void add(char c);
			const string& getContext();
			void show();
		private:
			string context;
	};
}


#endif //_ppmc_context_selector_h_
