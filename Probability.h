#ifndef _ppmc_probability_h_
#define _ppmc_probability_h_

#include "PPMC.h"

namespace ppmc {
	struct Probability {
			Probability();
			~Probability();
			probabilityType skip;
			probabilityType width;
			probabilityType total;
		friend class ProbabilityTest;
	};
}
#endif //_ppmc_probability_h_