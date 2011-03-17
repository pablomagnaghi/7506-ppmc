#include "hexdecoder_test.hpp"
#include "hexdecoder.hpp"

#include <cstring>
#include <string>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( HexDecoderTest );


void HexDecoderTest::setUp(){
  input = "4b50040300140003000068af2e9a8b235d7d0045000000390000000800006e696f66742e7478c929225d804d4ea8e565e358a5a2967cdaba214204f4da6fff2451682af9e88fabc03d2a5b4037e06e551d910aa625f1d5d527b6562c25852d2f5eafa1dbd6ca0b48825a506a014b1402140003000000af009a68232e7d8b455d000039000000080000000000000001002000b600008100006900666e2e6f78745074054b0006000001000100360000006b0000000000000023ffaba100fa0000";

}


void HexDecoderTest::tearDown(){
}


void HexDecoderTest::testConstructor(){
  unsigned int zero = 0;
  HexDecoder he;
  CPPUNIT_ASSERT_EQUAL(zero , he.getSize() );
}



unsigned char HexDecoderTest::expected[]={ 
    0x4b, 0x50, 0x04, 0x03, 0x00, 0x14, 0x00, 0x03, 0x00, 0x00, 0x68, 0xaf ,0x2e, 0x9a, 0x8b, 0x23,
    0x5d, 0x7d, 0x00, 0x45, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x08 ,0x00, 0x00, 0x6e, 0x69,
    0x6f, 0x66, 0x74, 0x2e, 0x74, 0x78, 0xc9, 0x29, 0x22, 0x5d, 0x80, 0x4d, 0x4e, 0xa8, 0xe5, 0x65,
    0xe3, 0x58, 0xa5, 0xa2, 0x96, 0x7c, 0xda, 0xba, 0x21, 0x42, 0x04, 0xf4, 0xda, 0x6f, 0xff, 0x24,
    0x51, 0x68, 0x2a, 0xf9, 0xe8, 0x8f, 0xab, 0xc0, 0x3d, 0x2a, 0x5b, 0x40, 0x37, 0xe0, 0x6e, 0x55,
    0x1d, 0x91, 0x0a, 0xa6, 0x25, 0xf1, 0xd5, 0xd5, 0x27, 0xb6, 0x56, 0x2c, 0x25, 0x85, 0x2d, 0x2f,
    0x5e, 0xaf, 0xa1, 0xdb, 0xd6, 0xca, 0x0b, 0x48, 0x82, 0x5a, 0x50, 0x6a, 0x01, 0x4b, 0x14, 0x02,
    0x14, 0x00, 0x03, 0x00, 0x00, 0x00, 0xaf, 0x00, 0x9a, 0x68, 0x23, 0x2e, 0x7d, 0x8b, 0x45, 0x5d,
    0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x20, 0x00, 0xb6, 0x00, 0x00, 0x81, 0x00, 0x00, 0x69, 0x00, 0x66, 0x6e, 0x2e, 0x6f, 0x78, 0x74,
    0x50, 0x74, 0x05, 0x4b, 0x00, 0x06, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x36, 0x00, 0x00, 0x00,
    0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0xff, 0xab, 0xa1, 0x00, 0xfa, 0x00, 0x00
};

void HexDecoderTest::testDecode(){
    HexDecoder hd;
    hd.decode(input);
    int result = memcmp(expected, hd.getCharBufferPtr(), hd.getSize());
    CPPUNIT_ASSERT_EQUAL(0, result);
}

void HexDecoderTest::testGetAsString(){


}
/*
	

void HexDecoderTest::testGetCharBufferPtr(){

}

void HexDecoderTest::testGetCharBufferCopy(){


}

*/