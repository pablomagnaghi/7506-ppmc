#ifndef TABLECALCULATOR_H_
#define TABLECALCULATOR_H_

#include <algorithm>
#include <math.h>
#include <stdio.h>

#include "TableCalculator.h"
#include "Constants.h"
#include "FrequencyTable.h"

using namespace std;

namespace ppmc{
	class TableCalculator {
		private:
			bool isInString(u_int8_t, string);
		public:
			TableCalculator();
			void getEnds (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* newTop, FrequencyTable table);
			bool getEndsLastModel (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * newBottom, u_int64_t* newTop, string ex);

			int foundedCharModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, FrequencyTable table);
			int foundedCharLastModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, string ex);

			virtual ~TableCalculator();
	};
}
#endif /* TABLECALCULATOR_H_ */
