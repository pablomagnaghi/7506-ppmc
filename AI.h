#ifndef AI_H_
#define AI_H_
#include <map>
#include <string>
#include "FileReader.h"

namespace util {
	class AI {
		public:
			AI(FileReader& in, const std::string n);
			~AI(){};
			size_t evaluate();
		private:
			FileReader& file;
			std::string name;
			std::map<std::string,int> ext;
	};
}

#endif /* AI_H_ */