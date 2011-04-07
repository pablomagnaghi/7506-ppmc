//#include <iomanip>

#include <sstream>
#include "Encoder.hpp"

using namespace mtf;
using namespace std;

Encoder::Encoder() {
  reset();
  count=0;
}
Encoder::~Encoder(){

}

void Encoder::reset() {
  for (int i=0; i< 255; i++) {
    index[i]=i;
  } 
}

unsigned int Encoder::find(char c) {
  for (unsigned int i=0; i< buffer_size; i++) {
    if (index[i] == c) {
      return i;
      break;
    }
  }
}

void Encoder::rearrange(unsigned int pos) {
  char c;
  for (unsigned int i=pos; i> 0; i--) {
    c = index[i];
    index[i] = index[i - 1];
    index[i -1] = c;
  }
}

void Encoder::encode(std::istream & in ) {
   while ( in.good() and ! in.eof() ) {
      in.read(buffer,buffer_size);
      count = in.gcount();
      for(unsigned int i=0; i < count; i++) {
        char c = find(buffer[i]);
        rearrange((unsigned int) c);
        buffer[i]=c;
      }
   }
}