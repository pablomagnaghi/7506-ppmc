#ifndef __bitbuffer_hpp__
#define __bitbuffer_hpp__

#include "bitchunk8.hpp"
#include "bitchunk32.hpp"
#include "bitexceptions.hpp"

namespace bits {
/**
 * Class for bit buffer manipulation
 */
class BitBuffer {
public:
  /** 
   * Constructor with buffer length in bytes (8 bits)
   */
  BitBuffer(int size);

  /**
   *
   */
  ~BitBuffer();

  /**
   * @return true if the buffer is empty
   */
  bool isEmpty() const;

  /**
   * @return true if the buffer is full
   */
  bool isFull() const;

  /**
   * @return true if there is overflow
   */
  bool isOverflow() const;

  /**
   * Appends length bits of a right aligned char pointer into the buffer
   * @return free space
   */
  unsigned int append(const BitChunk8& bc)  throw (BitBufferOverflow);

  /**
   * Appends length bits of a right aligned char into the buffer
   * @return free space
   */
  unsigned int append(unsigned char data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Appends length bits of a right aligned int into the buffer
   * @return free space
   */
  unsigned int append(unsigned int data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Append length bits of a right aligned long int into the buffer
   * @return free space
   */
  unsigned int append(unsigned long int data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Appends length bits of a left aligned char into the buffer
   * @return free space
   */
  unsigned int appendLA(unsigned char data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Appends length bits of a left aligned int into the buffer
   * @return free space
   */
  unsigned int appendLA(unsigned int data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Append length bits of a left aligned long int into the buffer
   * @return free space
   */
  unsigned int appendLA(unsigned long int data, unsigned int length) throw (BitBufferOverflow);

  /**
   * Moves the overflow to the buffer
   * @return free space
   */
  unsigned int appendOverflow();

  /**
   * Clears the buffer
   * @return free space
   */
  unsigned int clear(); 

  /**
   * Clears the buffer and the overflow
   * @return free space
   */
  unsigned int reset();

  /**
   * Clears the overflow
   */
  void clearOF();

  /**
   * Gets a pointer to the buffer
   */
  const char* getBuffer() const;

  /**
   * Gets the used buffer size in bytes
   */
  int getByteCount() const;

  void test();
  
private:
  char* buffer;
  unsigned int bufferSize;
  unsigned int bufferCursor;
  BitBuffer(BitBuffer&);
  BitBuffer& operator=(BitBuffer&);

};

}

#endif /* __bitbuffer_hpp__ */
