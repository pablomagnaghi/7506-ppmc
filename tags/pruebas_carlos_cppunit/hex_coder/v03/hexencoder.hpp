#ifndef __hexencoder_hpp__
#define __hexencoder_hpp__

#include <string>
#include <sstream>

class HexEncoder {
public:
  HexEncoder();
  ~HexEncoder();
  std::string encode(const char* buffer, unsigned int size);
  std::string encode(std::istream& input);
private:


};



#endif /* __hexencoder_hpp__ */
