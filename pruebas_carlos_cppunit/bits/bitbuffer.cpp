/**
 * Bitbuffer implementation
 */
#include "bitbuffer.hpp" 

#include <cstring>
#include <endian.h>

//debug
#include <iostream>
/**
 * Size of buffer overflow
 */
#define OVERFLOWSIZE sizeof(int) 

/**
 * Width of char
 */
//#define WIDTH 8 

static const unsigned int WIDTH=8;

using namespace std;
using namespace bits;

BitBuffer::BitBuffer(int size){
  bufferSize=size * WIDTH;
  buffer = new char[bufferSize + OVERFLOWSIZE * WIDTH]; //@todo hardcoded
  if (!buffer) throw 1; //bad_alloc();
  reset();
}

BitBuffer::~BitBuffer() {
  delete[] buffer;
}

bool BitBuffer::isEmpty() const{
  return bufferCursor==0;
}

bool BitBuffer::isFull() const{
  return bufferCursor>=bufferSize;
}

bool BitBuffer::isOverflow() const{
  return bufferCursor > bufferSize;
}

/*
 *                           bufferCursor                   length (8-1)
 *                                |                            | 
 *                                v                            v
 *   buffer  +--------+--------+--------+--------+     data +--------+
 *                             ^  ^                              
 *                             |  |
 *                             | offset(0-7)
 *                            pos    
 *
 *     offset 01234567
 *   + length 87654321
 *   -----------------          
 *     delta
 *
 *         delta < WIDTH  delta == WIDTH  delta > WIDTH
 *   data     00000xxx       0000xxxx       00xxxxxx
 *   buffer   xx000000       xxxx0000       xxxxx000
 *
 *                          length
 *            1    2     3   4    5    6    7    8
 *         +----------------------------------------
 *      0  | 7|0  6|0  5|0  4|0  3|0  2|0  1|0   =
 *   o  1  | 6|1  5|1  4|1  3|1  2|1  1|1   =   1|1
 *   f  2  | 5|2  4|2  3|2  2|2  1|2   =   1|2  2|1 
 *   f  3  | 4|3  3|3  2|3  1|3   =   1|3  2|2  3|1
 *   s  4  | 3|4  2|4  1|4   =   1|4  2|3  3|2  4|1
 *   e  5  | 2|5  1|5   =   1|5  2|4  3|3  4|2  5|1
 *   t  6  | 1|6   =   1|6  2|5  3|4  4|3  5|2  6|1
 *      7  |  =   1|7  2|6  3|5  4|4  5|3  6|2  7|1
 *
 *
 *  
 *
 *
 */

void BitBuffer::test(){
  cerr << "sizeof(char) " << sizeof(char) << endl;
  cerr << "sizeof(int)  " << sizeof(int) << endl << endl;
  
  cerr << "                        length" << endl;
  cerr << "           1    2     3   4    5    6    7    8" << endl;
  cerr << "        +--------------------------------------- " << endl;
  cerr << "     0  | 7|0  6|0  5|0  4|0  3|0  2|0  1|0   = " << endl;
  cerr << "  o  1  | 7|1  6|1  5|1  4|1  3|1  2|1   =   1|1" << endl;
  cerr << "  f  2  | 7|2  6|2  5|2  4|2  3|2   =   1|2  2|1" << endl;
  cerr << "  f  3  | 7|3  6|3  5|3  4|3   =   1|3  2|2  3|1" << endl;
  cerr << "  s  4  | 7|4  6|4  5|4   =   1|4  2|3  3|2  4|1" << endl;
  cerr << "  e  5  | 7|5  6|5   =   1|5  2|4  3|3  4|2  5|1" << endl;
  cerr << "  t  6  | 7|6   =   1|6  2|5  3|4  4|3  5|2  6|1" << endl;
  cerr << "     7  |  =   1|7  2|6  3|5  4|4  5|3  6|2  7|1" << endl;
  cerr << endl;

  cerr << "         ";
  for (unsigned int length = 1; length <= WIDTH ; ++length) {
    cerr << "  " <<  length << "  ";
  }
  cerr << endl;

  cerr << "        +---------------------------------------" << endl;

  for (unsigned int bufferCursor=0; bufferCursor < WIDTH ; ++bufferCursor) {
    unsigned int offset = bufferCursor % WIDTH;
    cerr << "     " << offset << "  |";
    for (unsigned int length = 1; length <= WIDTH ; ++length) {
      unsigned int  delta = offset + length;
      if (delta < WIDTH) {
        cerr << " " << ( WIDTH - length ) << "|"<< offset <<" ";
      } else if (delta == WIDTH ) {
        cerr << "  =   ";
      } else { // delta > WIDTH 
        cerr << (length + offset - WIDTH) << "|" << ( ( WIDTH - length ) + 1 ) << "  ";
      }
    }
    cerr << endl;
  }
  cerr << endl << endl;
}
unsigned int BitBuffer::append(const BitChunk8& bc) throw (BitBufferOverflow) {
  return append(bc.data, bc.length);
}

unsigned int BitBuffer::append(unsigned char data, unsigned int length) throw (BitBufferOverflow){
  unsigned int    pos = bufferCursor / WIDTH;
  unsigned int offset = bufferCursor % WIDTH;
  unsigned int  delta = offset + length;
  if ( delta < WIDTH ) {
    data <<= ( WIDTH - length);
    data >>= offset;
    buffer[pos] |= data;

  } else if (delta == WIDTH ) {
    data <<= ( WIDTH - length);
    data >>= offset;
    buffer[pos] |=  data;
  } else { // delta > WIDTH 
    unsigned char tmp = data;
    tmp >>= (length + offset - WIDTH);
    buffer[pos] |= tmp;
    data <<= ( ( WIDTH - length ) + 1 );
    ++pos;
    buffer[pos] |= data;
  }

  bufferCursor+=length;

  if (bufferCursor > ( bufferSize + OVERFLOWSIZE)* WIDTH ) {
    throw BitBufferOverflow("error no definido");
  }

  return bufferSize - bufferCursor;
}

unsigned int BitBuffer::append(unsigned int data, unsigned int length) throw (BitBufferOverflow){
  // htobe32(data); //htole32(data);
  union {
    int in;
    unsigned char out[sizeof(int)];
  } conv;

  conv.in = data;

  cerr << endl << "data: " << data << endl;

  for (int charpos = 3; charpos >= 0; --charpos) {
    unsigned int limit = WIDTH * charpos;
    if ( length > limit) {
      cerr << "int appending " << int(conv.out[charpos]) << " with size: " << length - limit << endl;
      append(conv.out[charpos], length - limit);
      length = WIDTH * charpos;
    }
  }
  
  return bufferSize - bufferCursor;
}

unsigned int BitBuffer::append(unsigned long int data, unsigned int length)throw (BitBufferOverflow){
  throw 1;
  return 0;
}

unsigned int BitBuffer::appendLA(unsigned char data, unsigned int length) throw (BitBufferOverflow){
  data >>= WIDTH - length;
  return append(data,length);
}

unsigned int BitBuffer::appendLA(unsigned int data, unsigned int length) throw (BitBufferOverflow){
  throw 1;
  return 0;
}

unsigned int BitBuffer::appendLA(unsigned long int data, unsigned int length) throw (BitBufferOverflow){
  throw 1;
  return 0;
}

unsigned int BitBuffer::appendOverflow(){
  clearOF();
  return 0;
}

void BitBuffer::clearOF(){
  memset(&buffer[bufferSize],0,OVERFLOWSIZE);
}

unsigned int BitBuffer::clear(){
  memset(buffer,0,bufferSize);
  bufferCursor=0;
  return bufferSize;
} 

unsigned int BitBuffer::reset(){
  clearOF();
  return clear();
}

const char* BitBuffer::getBuffer() const{
  return buffer;
}

int BitBuffer::getByteCount() const{
  if (bufferCursor % 8) {
    return (bufferCursor / 8) + 1;
  }
  return bufferCursor / 8;
}

