#ifndef PPMCCOMPRESSOR_H_
#define PPMCCOMPRESSOR_H_

#include <vector>
#include <algorithm>

#include "ArithmeticCompressor.h"
#include "Model.h"
#include "ContextSelector.h"


namespace ppmc {
class PPMCCompressor: public ArithmeticCompressor {
private:
	std::vector<Model*> models;
	ContextSelector contextSelector;
	FrequencyTable frequencyTable;
public:
	PPMCCompressor(util::FileReader *r, util::FileWriter *w);
	void compress();
	void process(u_int8_t a);
	void processEof(u_int16_t a);
	void show();
	virtual ~PPMCCompressor();
};
}
#endif /* PPMCCOMPRESSOR_H_ */
