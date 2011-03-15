#ifndef __bitexceptions_hpp__
#define __bitexceptions_hpp__
#include <string>
#include <exception>

namespace bits {
class BitBufferOverflow:public std::exception {
public:
  BitBufferOverflow(const std::string msg2);
  virtual const char* what() const throw();
private:
  const std::string& msg;
};
}
#endif /* __bitexceptions_hpp__ */
