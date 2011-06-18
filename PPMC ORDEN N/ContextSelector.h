#ifndef _ppmc_context_selector_h_
#define _ppmc_context_selector_h_

#include <string>

#include "PPMC.h"

using namespace std;

namespace ppmc {
	class ContextSelector {
		public:
			ContextSelector(size_t orden);
			~ContextSelector(){};
			void add(char c);
			const string& getContext();
			void show();
		private:
			string context;
			size_t orden;
	};
}


#endif //_ppmc_context_selector_h_
