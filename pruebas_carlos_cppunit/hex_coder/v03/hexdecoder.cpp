#include "hexdecoder.hpp"

#include <string>

using namespace std;

int HexDecoder::map_digit(char digit, char min, char max,int offset){
  if ( digit >= min && digit <= max) {
    return (digit - min + offset);
  }
  return -1;
}

int HexDecoder::decode_digit(char digit) {
  int res;
  res=map_digit(digit,'0','9',0);
  if (res != -1) {
    return res;
  }
  res=map_digit(digit,'a','f',10);
  if (res != -1) {
    return res;
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
  throw 1;
  return "";
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
  it+=2;
  bool spaced = ((*it)== ' ');

  it=input.begin();

  while( it != input.end() && outputCursor != bufferEnd) {
    int digit = 0;
    int tmp = decode_digit(*it);
    if (tmp == -1) {
      throw 1;
    } 
    digit = tmp * 16;

    ++it;
    if (it == input.end()) {
      throw 1;
    }

    tmp = decode_digit(*it);
    if (tmp == -1) {
      throw 1; //@todo exception
    }
    digit += tmp;
    ++it;

    if (spaced && it != input.end()) {
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

