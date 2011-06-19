#include "NodeTest.hpp"
#include "../Huffman.hpp"
#include "../Node.hpp"

using namespace huffman;

CPPUNIT_TEST_SUITE_REGISTRATION( NodeTest );


void NodeTest::setUp(){

}


void NodeTest::tearDown(){
}                               


void NodeTest::testConstructor(){
  unsigned char value = 'a';
  unsigned int zero = 0;
  Node node(value);
  CPPUNIT_ASSERT_EQUAL(value , node.value );
  CPPUNIT_ASSERT_EQUAL(empty , node.parent );
  CPPUNIT_ASSERT_EQUAL(empty , node.zero );
  CPPUNIT_ASSERT_EQUAL(empty , node.one );
  CPPUNIT_ASSERT_EQUAL(zero , node.count );
  
}
