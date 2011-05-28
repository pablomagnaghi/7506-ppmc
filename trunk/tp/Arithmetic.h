#ifndef _ppmc_arithmetic_h_
#define _ppmc_arithmetic_h_

#include <vector>

#include "PPMC.h"
#include "Model.h"
#include "IFileWriter.h"
#include "IFileReader.h"

namespace ppmc {
	class Arithmetic {
		public:
			Arithmetic(size_t o);
			virtual ~Arithmetic();
		protected:
			std::vector<Model*> models;
			size_t order;
			baseType ceiling;
			baseType floor;
			
			util::IFileReader* reader;
			util::IFileWriter* writer;
			
			baseType buffer;
			u_int8_t bits_in_buffer;
			u_int8_t underflow_counter;
			void addBitToBuffer(u_int8_t);
			void putBufferInFileWriter();
			void solve_underflow();
			void solve_overflow();
			void clean_buffer();
			void print_in_bin(baseType x);
			void setNewLimits();
		friend class CompressorTest;
	};
}
#endif //_ppmc_arithmetic_h_