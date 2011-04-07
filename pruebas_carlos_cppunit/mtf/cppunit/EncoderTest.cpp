#include "EncoderTest.hpp"
#include "../MTF.hpp"
#include "../Encoder.hpp"

#include <sstream>
#include <iostream>

using namespace mtf;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( EncoderTest );


void EncoderTest::setUp(){

}


void EncoderTest::tearDown(){
}                               


void EncoderTest::testConstructor(){
  //CPPUNIT_ASSERT_EQUAL(zero , node.count );
}

void EncoderTest::testFind(){
  Encoder e;
  unsigned int pos = 97;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('a') );
  pos = 10;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\n') );
  pos = 0;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\0') );
}

void EncoderTest::testRearrange(){
  Encoder e;
  unsigned int pos = 0;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\0') );
  e.rearrange(0);
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\0') );
  
  pos = 10;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\n') );
  e.rearrange(10);
  pos = 0;
  CPPUNIT_ASSERT_EQUAL(pos, e.find('\n') );
  
}


void EncoderTest::testEncode(){
  Encoder e;
  stringstream  inputString("aaaaaaa");
  inputString >> e;
  cout << e ;
}

