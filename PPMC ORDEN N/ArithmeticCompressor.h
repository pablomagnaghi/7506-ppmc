#ifndef ARITHMETICCOMPRESSOR_H_
#define ARITHMETICCOMPRESSOR_H_

#include <vector>
#include "PPMC.h"
#include "Model.h"
#include "ContextSelector.h"
#include "algorithm"
#include "FileWriter.h"
#include "FileReader.h"

namespace ppmc {
class ArithmeticCompressor {
private:
	u_int64_t bottom;
	u_int64_t top;
	char underflowCounter;
	char buffer;
	char bitsInBuffer;
protected:
	util::FileReader *reader;
	util::FileWriter *writer;
public:
	ArithmeticCompressor(util::FileReader* r, util::FileWriter* w);
	virtual void process(u_int16_t a)=0;
	u_int64_t getBottom();
	u_int64_t getTop();
	void setBottom(u_int64_t bottom);
	void setTop(u_int64_t top);
	void solveOverflow();
	void solveUnderflow();
	void putBitInBuffer(char bit);
	void putBufferInOutput();
	void cleanBuffer();
	void show();
	virtual ~ArithmeticCompressor();
};
}
#endif /* ARITHMETICCOMPRESSOR_H_ */
