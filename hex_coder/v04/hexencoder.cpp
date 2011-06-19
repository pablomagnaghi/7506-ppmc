#include "hexencoder.hpp"



#include <iostream>
#include <iomanip>


using namespace std;

HexEncoder::HexEncoder(){

}

HexEncoder::~HexEncoder(){

}
/**
 * Encodes as hexadecimal string representation the content of a buffer filled 
 * with bytes
 * 
 */
std::string HexEncoder::encode(const char* buffer, unsigned int size) {
  unsigned char uc;
  unsigned int ui;
  stringstream ss;
  string output; 
  for (unsigned int cursor=0; cursor < size; ++cursor){
    uc = buffer[cursor];
    ui = uc;
    ss << hex << uppercase << setfill('0') << setw(2) << ui;
  }
  ss >> output;
  return output;
}

/**
 * Encodes as hexadecimal string representation a stream
 *
 */
std::string HexEncoder::encode(std::istream& input){
  char c;
  unsigned char uc;
  unsigned int ui;
  stringstream ss;
  string output;
  input.read(&c,1);
  while (! input.eof()) {
    uc = c;
    ui = uc;
    ss << hex << uppercase << setfill('0') << setw(2) << ui ;
    input.read(&c,1);
  }
  ss >> output;
  return output;
}
