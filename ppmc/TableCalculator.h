#ifndef TABLECALCULATOR_H_
#define TABLECALCULATOR_H_

#include <algorithm>
#include <math.h>

#include "Constants.h"
#include "FrequencyTable.h"


namespace ppmc{
	class TableCalculator {
		private:
			bool isInString(u_int8_t, std::string);
		public:
			TableCalculator();
			void getLimits (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* newTop, FrequencyTable table);
			bool getLimitsLastModel (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * newBottom, u_int64_t* newTop, std::string ex);

			int findCharModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, FrequencyTable table);
			int findCharLastModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, std::string ex);

			virtual ~TableCalculator();
	};
}
#endif /* TABLECALCULATOR_H_ */
