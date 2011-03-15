#include "unary.hpp"
#include "gamma.hpp"
#include "delta.hpp"
#include "tool.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

void test_decode(int start, int stop, int (*f)(int)){
  int unary_value;
  int unary_len;

  for (int i=start; i < stop ; ++i) {
    unary_encode(i,&unary_value, &unary_len);
    cout << setfill(' ') << setw(2) << i;
    binary_show(unary_value, unary_len);
    cout << setfill(' ') << setw(4) << f(unary_value) << endl;
  }
}

void test_encode(int start, int stop,void (*f)(int,int*,int*)) {
  int value = 0;
  int len   = 0;

  for (int i=start; i<stop; ++i){
    f(i,&value, &len);
    cout << setfill(' ') << setw(4) << i;
    binary_show(value, len);
    cout << endl; 
  }
}

