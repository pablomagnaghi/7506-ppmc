#include "bitexceptions.hpp"
using namespace bits;
BitBufferOverflow::BitBufferOverflow(const std::string msg2):msg(msg2){}

const char* BitBufferOverflow::what() const throw() {
    return msg.c_str();
  }

