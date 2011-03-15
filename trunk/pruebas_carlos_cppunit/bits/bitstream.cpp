#include "bitstream.hpp"

using namespace bits;

BitStream::BitStream(std::ostream& o):buffer(10),out(o){

}

BitStream& BitStream::operator<<(const BitChunk8& bc) {
  buffer.append(bc);
  return *this;
}


