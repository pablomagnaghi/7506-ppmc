#ifndef _mtf_encoder_hpp_
#define _mtf_encoder_hpp_
#include <sstream>


#include <iostream>
#include <sstream>
#include "MTF.hpp"

namespace mtf {

  class Encoder {
    public:
    Encoder();
    ~Encoder();
    void reset();
    void encode(std::istream & in);
    //std::stringstream readBuffer();
    private:
    char buffer[buffer_size];      
    char index[buffer_size];
    unsigned int count;
    unsigned int find(char c);
    void rearrange(unsigned int i);
   
    friend class EncoderTest;
    friend std::istream& operator>>(std::istream& i, Encoder& e ){
       e.encode(i);
      return i; 
    }
    friend std::ostream& operator<<(std::ostream& o, const Encoder& e){
      for (unsigned int i= 0; i < e.count ; i++) {
        o << e.buffer[i]; 
      }
      return o ;     
    }

  };
 
}

#endif // _mtf_encoder_hpp_
