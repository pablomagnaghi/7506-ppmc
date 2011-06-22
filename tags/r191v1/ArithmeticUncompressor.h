#ifndef ARITHMETICUNCOMPRESSOR_H_
#define ARITHMETICUNCOMPRESSOR_H_

#include <queue>
#include <algorithm>

#include "PPMC.h"
#include "Constants.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace ppmc {
	class ArithmeticUncompressor {
		private:
			u_int64_t bottom;
			u_int64_t top;
			u_int32_t number;
			int bitsInNumber;
			char buffer;
			int bitsInBuffer;
			std::queue<u_int16_t> charQueue;
			util::FileWriter *writer;
			util::FileReader *reader;
		protected:
			size_t size;
			size_t order;
		public:
			ArithmeticUncompressor(util::FileReader* r, util::FileWriter* w);
			void solveOverflow();
			void solveUnderflow();
			virtual bool process (char a) = 0;
			void uncompress();
			u_int16_t extract();
			void addToQueue(u_int16_t c);
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
			virtual ~ArithmeticUncompressor();
		};
}
#endif /* ARITHMETICUNCOMPRESSOR_H_ */
