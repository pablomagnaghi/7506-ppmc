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
			std::size_t getFrecuenciaChar();
			std::size_t getFrecuenciaEsc();
			u_int64_t getNewBottom();
			u_int64_t getNewTop();
			void setUpLimits(u_int64_t, u_int64_t, char);
			bool find(char);
			void addCharacter(char);
			void getStringExc(std::string&);
			void show();
			void update(FrequencyTable*);
			void clear();
		private:
			std::map<char, std::size_t> table;
			std::size_t esc;
			std::size_t frecuencia;
			u_int64_t bottom;
			u_int64_t top;
			u_int32_t total;
			bool primerPasada;
	};
}



#endif // _ppmc_frequency_table_h_
