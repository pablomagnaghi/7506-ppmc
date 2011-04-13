#ifndef _ppmc_probability_h_
#define _ppmc_probability_h_

#include "PPMC.h"

namespace ppmc {
	class Probability {
		public:
			Probability();
			~Probability();
		private:
			unsigned char skip;
			unsigned char width;
			unsigned char total;
		friend class ProbabilityTest;
	};
}
#endif //_ppmc_probability_h_