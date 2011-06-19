#include "unary.hpp"
#include <cmath>

void unary_encode(int number, int* unary_value, int* len){
  *len = floor(log2(number));
  *unary_value = pow(2,number) - 2;
}

int unary_decode(int unary){
  int count=1;
  unary = unary >> 1;
  while (unary & 1) {
    unary = unary >> 1;
    ++count;
  }
  return count;

}

