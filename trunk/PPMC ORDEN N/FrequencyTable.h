#ifndef _ppmc_frequency_table_h_
#define _ppmc_frequency_table_h_

#include "PPMC.h"
#include <map>
#include <string>

namespace ppmc {
	class FrequencyTable {
		public:
			FrequencyTable();
			virtual ~FrequencyTable();
			std::map<char, std::size_t>::iterator tableBegin();
			std::map<char, std::size_t>::iterator tableEnd();
			std::size_t getFrecuenciaChar();
			std::size_t getFrecuenciaEsc();
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
			bool primerPasada;
	};
}



#endif // _ppmc_frequency_table_h_
