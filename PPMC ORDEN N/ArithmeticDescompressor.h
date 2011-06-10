#ifndef ARITHMETICDESCOMPRESSOR_H_
#define ARITHMETICDESCOMPRESSOR_H_

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include "Constants.h"
#include "algorithm"
#include <queue>
#include "FileWriter.h"
#include "FileReader.h"

namespace ppmc {
	class ArithmeticDescompressor {
		private:
			u_int64_t bottom;
			u_int64_t top;
			u_int32_t number;
			int bitsInNumber;
			char buffer;
			int bitsInBuffer;
			std::queue<char> cola;
			util::FileReader *reader;
			util::FileWriter *writer;
		public:
			ArithmeticDescompressor(util::FileReader* r, util::FileWriter* w);
			void solveOverflow();
			void solveUnderflow();
			virtual bool process (char a) = 0;
			void uncompress();
			char extract();
			void addToQueue(char c);
			u_int64_t getBottom();
			u_int64_t getTop();
			void setBottom(u_int64_t bottom);
			void setTop(u_int64_t top);
			void setBuffer(char a);
			u_int32_t getNumber();
			int getBitsInNumber();
			int getBitsInBuffer();
			void dropBufferInNumber();
			void removeBits (int cant);
			virtual ~ArithmeticDescompressor();
		};
}
#endif /* ARITHMETICDESCOMPRESSOR_H_ */
