#ifndef __bitchunk8_hpp__
#define __bitchunk8_hpp__

namespace bits {

struct BitChunk8 {
  BitChunk8(unsigned char dd, unsigned int ll){
    data=dd;
    length=ll;
  }
  unsigned char data;
  unsigned int length;  
  

};

}


#endif /* __bitchunk8_hpp__ */
