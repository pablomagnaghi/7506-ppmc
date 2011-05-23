#ifndef _ppmc_arithmetic_h_
#define _ppmc_arithmetic_h_

#include <vector>
#include "PPMC.h"
#include "Model.h"
#include "ContextSelector.h"
#include "algorithm"

namespace ppmc {
	class Arithmetic {
		public:
			Arithmetic();
			u_int64_t getTop();
			u_int64_t getBottom();
			void setNewLimits(u_int64_t, u_int64_t);
			virtual ~Arithmetic();
		protected:
			std::vector<Model*> models;
			ContextSelector contextSelector;
			FrequencyTable frequencyTable;
			//std::map<char, std::size_t> table;
			// necesito mapa de probabilidades, <frecuencia, total>
		private:
			u_int64_t top;
			u_int64_t bottom;
			u_int64_t buffer;
			u_int8_t bits_in_buffer;
			u_int8_t underflow_counter;
			/*
			 * Agrego el bit al buffer
			 */
			void addBitToBuffer(u_int8_t);

			/*
			 * Funcion que se usa para mandar el buffer de bits al fileWriter
			 */
			void putBufferInFileWriter();
			void solve_underflow();
			void solve_overflow();

			/*
			 * Funcion que se llama al final del aritmetico para flushear los ultimos bits
			 */
			void clean_buffer();
	};
}
#endif //_ppmc_arithmetic_h_