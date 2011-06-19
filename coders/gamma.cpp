#include "unary.hpp"
#include "gamma.hpp"
#include <cmath>

void gamma_encode(int number, int* gamma_value, int* gamma_len ) {
   int unary_value;
   int unary_len;

   int log = floor(log2(number));

   unary_encode(log + 1, &unary_value, &unary_len);

   int remainder = number - pow(2,log);

   *gamma_len=unary_len + log;
   *gamma_value= (unary_value << log) + remainder;
}

