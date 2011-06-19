
#include "bitbuffer.hpp"
#include "../hex_coder/v03/hexencoder.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
using namespace bits;

int main(int argc, char* argv[]){
  if (argc!= 2) {
   throw "mal argumentos";
  }
  
  BitBuffer bb(100);
  if ( !strcmp(argv[1],"test")) {
    bb.test();
    return 0;
  }

  HexEncoder he;

  char * target;
  ofstream file ("file.bin", ios::out|ios::binary);


  unsigned int i_full  = 0xffffffff;
  unsigned int i_empty = 0x0;
  unsigned int i_1    = 0x000000ff;
  unsigned int i_2    = 0x0000ff00;
  unsigned int i_3    = 0x00ff0000;
  unsigned int i_4    = 0xff000000;

  unsigned char c_full  = 0xff; // 11111111
  unsigned char c_empty = 0x00; // 00000000
  unsigned char c_a     = 0x01; // 00000001
  unsigned char c_b     = 0x02; // 00000010
  unsigned char c_c     = 0x03; // 00000011
  unsigned char c_d     = 0x04; // 00000100
  unsigned char c_e     = 0x05; // 00000101
  unsigned char c_f     = 0x0a; // 00001010

  BitChunk8 bc8_1(0x01,1);
  BitChunk8 bc8_2(0x02,2);
  BitChunk8 bc8_3(0x03,2);
  BitChunk8 bc8_4(0x04,3);

  if ( !strcmp(argv[1], "integer")) {
    cerr << "TESTING INTEGER" << endl;
    try {
      bb.append(i_1,8);
      bb.append(i_2,16);
      bb.append(i_3,24);
      bb.append(i_4,32);
    } catch (BitBufferOverflow& e) {
      cerr << "Overflow " << e.what() << " " << bb.getByteCount() << endl;
    }
    target = new char[bb.getByteCount()]; 
    *target = 0xffff;
    cerr << "00000000  ff ff 00 ff 00 00 ff 00  00 00" << endl;
    delete[] target;
  } else if ( !strcmp(argv[1], "bitchunk8")) {
    cerr << "TESTING BIT CHUNK 8" <<  endl;
    try {
      bb.append(bc8_1);
      bb.append(bc8_2);
      bb.append(bc8_3);
      bb.append(bc8_4);
    } catch (BitBufferOverflow& e) {
      cerr << "Overflow " << e.what() << " " << bb.getByteCount() << endl;
    }
    cerr << "00000000  ff ff 00 ff 00 00 ff 00  00 00" << endl;
    return 0;
  } else if ( !strcmp(argv[1], "char" )) {
    cerr << "TESTING CHAR" << endl;

    bb.append(c_full,2);
    bb.append(c_empty,2);
    bb.append(c_full,2);
    bb.append(c_empty,2); // 8

    bb.append(c_full,1);
    bb.append(c_empty,2);
    bb.append(c_full,3);
    bb.append(c_empty,3);  // 17
 
    bb.append(c_full,5);
    bb.append(c_empty,4);  // 26

    bb.append(c_full,7);
    bb.append(c_empty,2); //35

    bb.append(c_full,3);
    bb.append(c_empty,2); // 40 CC9C7C3F9C

    bb.append(c_full,6);
    bb.append(c_empty,3);
    bb.append(c_full,2), // 51
 
    bb.append(c_empty,3);
    bb.append(c_full,5);
    bb.append(c_empty,2); //61

    bb.append(c_a,3);
    bb.append(c_b,3);
    bb.append(c_c,3);
    bb.append(c_d,3);
    bb.append(c_e,3);
    bb.append(c_f,4);    // 80 FC63E14E5A

    cerr << "00000000  cc 9c 7c 3f 9c fc 63 e1  4e 5a" << endl;

    cerr << "          cc 9c 7c 7f fc fc 7f f1  4e 5a" << endl;
  }
  
  cout << he.encode(bb.getBuffer(),(unsigned int)bb.getByteCount());
  
  file.write(bb.getBuffer(), bb.getByteCount()); 
  return 0;
}
