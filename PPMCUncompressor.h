#ifndef PPMCUNCOMPRESSOR_H_
#define PPMCUNCOMPRESSOR_H_

#include <vector>
#include <algorithm>

#include "ArithmeticDescompressor.h"
#include "Model.h"
#include "ContextSelector.h"
#include "PPMCCompressor.h"
#include "Constants.h"
#include "TableCalculator.h"

using namespace std;

namespace ppmc{
	class PPMCUncompressor: public ArithmeticDescompressor {
		private:
			vector<Model*> models;
			ContextSelector contextSelector;
			FrequencyTable frequencyTable;
			string currentContext;
			string exclusionChars;
			string firstContext;
			int state;
			bool solveLastModel(string, string, int *);
		public:
			PPMCUncompressor(FileReader* r, FileWriter* w);
			bool process (char a);
			void show();
			virtual ~PPMCUncompressor();
	};
}
#endif /* PPMCUNCOMPRESSOR_H_ */
