#ifndef TABLECALCULATOR_H_
#define TABLECALCULATOR_H_

#include "FrequencyTable.h"
#include "algorithm"

namespace ppmc{
class TableCalculator {
private:
	bool isInString(u_int8_t, std::string);
public:
	TableCalculator();
	void getEnds (u_int8_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* newTop, FrequencyTable table);
	void getEndsLastModel (u_int8_t a, u_int64_t bottom, u_int64_t top, u_int64_t * newBottom, u_int64_t* newTop, std::string ex);

	void getEndsEof (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* new_top, FrequencyTable table);
	void getEndsLastModelEof (u_int16_t a, u_int64_t bottom, u_int64_t top, u_int64_t * new_bottom, u_int64_t* new_top, std::string ex);

	int foundedCharModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, FrequencyTable table);
	int foundedCharLastModel (u_int64_t number, int size, u_int64_t bottom, u_int64_t top, u_int64_t *temporalBottom, u_int64_t * temporalTop, std::string ex);

	virtual ~TableCalculator();
};
}
#endif /* TABLECALCULATOR_H_ */
