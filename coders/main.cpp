#include "unary.hpp"
#include "gamma.hpp"
#include "delta.hpp"
#include "test_coders.hpp"
#include "tool.hpp"

#include <stdlib.h>

#include <iostream>
#include <string>


void buffer_add(char* buffer, int* offset, int value, int len){
  int bitoffset = *offset % 8;
  int charoffset = *offset / 8;
  value = value << ( (sizeof(value)*8)-len-bitoffset) ;
  buffer[charoffset] |= value;
  *offset += len;
}

using namespace std;

int main(int argc, char* argv[]) {
  string cmd(argv[1]);
  string type(argv[2]);
  

  if (! cmd.compare("encode")) {
    void (*f) (int,int*,int*)=NULL;
    if (! type.compare("unary")) {
      f=unary_encode;    
    } else if (! type.compare("gamma")) {
      f=gamma_encode;
    } else if ( ! type.compare("delta")) {
      f=delta_encode;
    } else {
      return 1;
    }
    test_encode(atoi(argv[3]), atoi(argv[4]),f);
  } else if (! cmd.compare("decode")) {
    int (*f) (int)=NULL;
    if  (! type.compare("unary")) {
      f=unary_decode;
    } else {
      return 2;
    }
    test_decode(atoi(argv[3]), atoi(argv[4]),f);
  } else {
    return 3;
  }
  return 0;
}
