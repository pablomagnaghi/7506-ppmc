#ifndef __bitchunk32_hpp__
#define __bitchunk32_hpp__

namespace bits {

struct BitChunk32 {
  BitChunk32(unsigned int dd, unsigned int ll){
    data=dd;
    length=ll;
  }
  unsigned int data;
  unsigned int length;  
  

};

}


#endif /* __bitchunk32_hpp__ */
