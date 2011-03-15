#include "tool.hpp"

#include <iostream>

using namespace std;

void binary_show(int value, int len) {
//               123456789012345678
  char linea[]="                  0";
  int pos = 18;
  while (value > 0) {
    if (value & 1) {
      linea[pos]='1';
    } else {
      linea[pos]='0';
    }
    value /= 2;
    --pos;
  }
  cout << linea ;
}

