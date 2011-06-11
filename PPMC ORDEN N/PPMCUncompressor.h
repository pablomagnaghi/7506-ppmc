#ifndef PPMCUNCOMPRESSOR_H_
#define PPMCUNCOMPRESSOR_H_

#include <vector>
#include <algorithm>
#include "ArithmeticDescompressor.h"
#include "Model.h"
#include "ContextSelector.h"


namespace ppmc{
class PPMCUncompressor: public ArithmeticDescompressor {
private:
	std::vector<Model*> models;
	ContextSelector contextSelector;
	FrequencyTable frequencyTable;
	std::string currentContext;
	std::string exclusionChars;
	std::string firstContext;
	int state;
	bool solveLastModel(std::string, std::string, int *);
public:
	PPMCUncompressor(util::FileReader* r, util::FileWriter* w);
	bool process (char a);
	void show();
	virtual ~PPMCUncompressor();
};
}
#endif /* PPMCUNCOMPRESSOR_H_ */
