#ifndef _ppmc_probability_h_
#define _ppmc_probability_h_

#include "PPMC.h"

namespace ppmc {
	struct Probability {
			Probability();
			~Probability();
			unsigned int skip;
			unsigned int width;
			unsigned int total;
		friend class ProbabilityTest;
	};
}
#endif //_ppmc_probability_h_