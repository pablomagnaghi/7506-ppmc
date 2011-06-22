#ifndef _ppmc_frequency_table_h_
#define _ppmc_frequency_table_h_

#include <map>
#include <string>
#include <algorithm>

#include "PPMC.h"
#include "Constants.h"

namespace ppmc {
	class FrequencyTable {
		public:
			FrequencyTable();
			virtual ~FrequencyTable();
			std::map<u_int16_t, size_t>::iterator tableBegin();
			std::map<u_int16_t, size_t>::iterator tableEnd();
			size_t getFrequencyChar();
			size_t getFrequencyEsc();
			u_int32_t getNewBottom();
			u_int32_t getNewTop();
			u_int32_t getTotal();
			bool find(u_int16_t);
			void addCharacter(u_int8_t);
			void getStringExc(std::string&);
			void exc(const std::string&);
			size_t getNumberOfChars();
			std::string show();
			void update(FrequencyTable*);
			void clear();
			std::map<u_int16_t, size_t> getTable();
		private:
			std::map<u_int16_t, size_t> table;
			size_t esc;
			size_t frequency;
			u_int32_t bottom;
			u_int32_t top;
			u_int32_t total;
			bool firstPass;
	};
}

#endif // _ppmc_frequency_table_h_
