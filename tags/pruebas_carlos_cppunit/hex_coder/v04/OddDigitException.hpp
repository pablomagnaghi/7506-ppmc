#ifndef __odddigitexception_hpp__
#define __odddigitexception_hpp__
#include <exception>

class OddDigitException: public std::exception {
public:
  OddDigitException();
  OddDigitException(const char* message);
  OddDigitException(const std::string& message);

  virtual const char* what() throw();

  ~OddDigitException() throw();

private:
  std::string message;

};

#endif /* __odddigitexception_hpp__ */


