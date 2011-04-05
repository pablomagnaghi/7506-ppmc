#include "xxxTest.hpp"
#include "../mtf.hpp"
#include "../xxx.hpp"

using namespace mtf;

CPPUNIT_TEST_SUITE_REGISTRATION( xxxTest );


void xxxTest::setUp(){

}


void xxxTest::tearDown(){
}                               


void xxxTest::testConstructor(){
  unsigned char value = 'a';
  unsigned int zero = 0;
  xxx xxx(value);
  CPPUNIT_ASSERT_EQUAL(value , node.value );
  CPPUNIT_ASSERT_EQUAL(empty , node.parent );
  CPPUNIT_ASSERT_EQUAL(empty , node.zero );
  CPPUNIT_ASSERT_EQUAL(empty , node.one );
  CPPUNIT_ASSERT_EQUAL(zero , node.count );
  
}
