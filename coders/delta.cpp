#include "gamma.hpp"
#include <cmath>


void delta_encode(int  number, int* delta_value, int* delta_len ) {
   int gamma_value;
   int gamma_len;

   int log = floor(log2(number));

   gamma_encode(log + 1, &gamma_value, &gamma_len);

   int remainder = number - pow(2,log);

   *delta_len=gamma_len + log;
   *delta_value= (gamma_value << log) + remainder;

}

