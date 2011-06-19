#ifndef __hexdecoder_hpp__
#define __hexdecoder_hpp__

#include <string>
/*
 * 
 *
 */
class HexDecoder {
public:
  HexDecoder();
  ~HexDecoder();
  void decode(std::string& ii);
  char* getCharBufferPtr();
  char* getCharBufferCopy();
  std::string getAsString();
  unsigned int getSize();
private:
  int map_digit(char digit, char min, char max,int offset);
  int decode_digit(char digit);
  char* output;
  unsigned int size;
};
  
#endif /* __hexdecoder_hpp__ */

