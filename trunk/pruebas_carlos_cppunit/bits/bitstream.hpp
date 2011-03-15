#ifndef __bitstream_hpp__
#define __bitstream_hpp__

#include "bitbuffer.hpp"
#include "bitchunk8.hpp"
#include "bitchunk32.hpp"

#include <ostream>

namespace bits {

class BitStream {
public:
  BitStream(std::ostream& o);
  BitStream& operator<<(const BitChunk8& bc);
private:
  BitBuffer buffer;
  std::ostream& out;

};

}
#endif /* __bitstream_hpp__ */
