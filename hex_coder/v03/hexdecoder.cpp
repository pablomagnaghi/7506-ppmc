#include "hexdecoder.hpp"

#include <string>

using namespace std;

/**
 * 
 *
 */
int HexDecoder::map_digit(char digit, char min, char max,int offset){
  if ( digit >= min && digit <= max) {
    return (digit - min + offset);
  }
  return -1;
}

int HexDecoder::decode_digit(char digit) {
  int decoded;
  decoded=map_digit(digit,'0','9',0);
  if (decoded != -1) {
    return decoded;
  }
  decoded=map_digit(digit,'a','f',10);
  if (decoded != -1) {
    return decoded;
  }
  
  // @todo raise exception instead of returning -1
  return map_digit(digit,'A','F',10);
}


unsigned int HexDecoder::getSize() {
  return size;
}

char* HexDecoder::getCharBufferPtr() {
  return output;
}

char* HexDecoder::getCharBufferCopy() {
throw 1;
  return 0;  
}

std::string HexDecoder::getAsString(){
  string result(output);
  return result;
}

HexDecoder::HexDecoder() {
  size=0;
}

void HexDecoder::decode(std::string& input) {
  size=input.size();
  output = new char[size]; 

  char * outputCursor = output;
  char * bufferEnd = &output[input.size()];
  string::iterator it=input.begin();

  while( it != input.end() && outputCursor != bufferEnd) {
    int digit = 0;
    int decoded = decode_digit(*it);
    if (decoded == -1) {
      // not in 0-9a-fA-F range
      throw 1;
    } 
    digit = decoded * 16;

    ++it;
    if (it == input.end()) {
      // odd characters provided
      throw 1;
    }

    decoded = decode_digit(*it);
    if (decoded == -1) {
      // not in 0-9a-fA-F range
      throw 1;
    }
    digit += decoded;
    ++it;

    if (*it == ' ') {
      ++it;
    }

    *outputCursor=digit;
    ++outputCursor;
  }
  size = ( outputCursor - output);
}

HexDecoder::~HexDecoder(){
  delete[] output;
}

