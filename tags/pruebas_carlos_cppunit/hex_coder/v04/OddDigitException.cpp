#include <string>

#include "OddDigitException.hpp"


OddDigitException::OddDigitException(){}

OddDigitException::OddDigitException(const char* message):
  std::exception(),
  message(message) {
}

OddDigitException::OddDigitException(const std::string& message):
  std::exception(),
  message(message) {
}

const char* OddDigitException::what() throw(){
  return this->message.c_str();
}

OddDigitException::~OddDigitException() throw(){ }



