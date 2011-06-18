#ifndef PPMCCOMPRESSOR_H_
#define PPMCCOMPRESSOR_H_

#include <vector>
#include <algorithm>

#include "ArithmeticCompressor.h"
#include "Model.h"
#include "ContextSelector.h"
#include "Constants.h"
#include "TableCalculator.h"

using namespace std;
using namespace util;

namespace ppmc {
	class PPMCCompressor: public ArithmeticCompressor {
		private:
			vector<Model*> models;
			ContextSelector contextSelector;
			FrequencyTable frequencyTable;
		public:
			PPMCCompressor(FileReader *r, FileWriter *w);
			void compress();
			void process(u_int16_t a);
			void show();
			virtual ~PPMCCompressor();
	};
}
#endif /* PPMCCOMPRESSOR_H_ */
