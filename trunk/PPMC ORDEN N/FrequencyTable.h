#ifndef _ppmc_frequency_table_h_
#define _ppmc_frequency_table_h_

#include "PPMC.h"
#include <map>
#include <string>
#include "algorithm"

namespace ppmc {
	class FrequencyTable {
		public:
			FrequencyTable();
			virtual ~FrequencyTable();
			std::map<char, std::size_t>::iterator tableBegin();
			std::map<char, std::size_t>::iterator tableEnd();
			std::size_t getFrequencyChar();
			std::size_t getFrequencyEsc();
			u_int32_t getNewBottom();
			u_int32_t getNewTop();
			u_int32_t getTotal();
			void setUpLimitsWithEscape(u_int32_t, u_int32_t);
			void setUpLimitsWithCharacter(u_int32_t, u_int32_t, u_int8_t);
			void setUpLimitsOnLastModel(u_int32_t, u_int32_t, u_int8_t, const std::string&);
			void setUpLimitsWithEOF(u_int32_t, u_int32_t, const std::string&);
			bool find(char);
			void addCharacter(char);
			void getStringExc(std::string&);
			void exc(const std::string&);
			std::size_t getNumberOfChars();
			void show();
			void update(FrequencyTable*);
			void clear();
		private:
			std::map<char, std::size_t> table;
			std::size_t esc;
			std::size_t frequency;
			u_int32_t bottom;
			u_int32_t top;
			u_int32_t total;
			bool firstPass;
			u_int32_t getPreviousFrequences(u_int8_t);
			u_int32_t getPreviousFrequencesForEscape();
			void calculateValues(u_int32_t, u_int32_t, u_int32_t);
	};
}



#endif // _ppmc_frequency_table_h_
