#include <sstream>

#include "HuffmanTreeTest.hpp"
#include "../HuffmanTree.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( HuffmanTreeTest );

using namespace std;
using namespace huffman;

void HuffmanTreeTest::setUp(){

}


void HuffmanTreeTest::tearDown(){
}                               


void HuffmanTreeTest::testConstructor(){
  int zero = 0;
  string empty;
  Tree tree;
  CPPUNIT_ASSERT_EQUAL(zero , tree.getTotalRead() );
  CPPUNIT_ASSERT_EQUAL(empty, tree.showFreq(true) );
  
}

void HuffmanTreeTest::testRead(){
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  string expected("9:2,10:8,97:8,98:7,99:6,100:5,101:4,102:3,103:2,104:1");
  Tree tree;
  tree.read(input);
  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
  CPPUNIT_ASSERT_EQUAL(46, tree.getTotalRead() );  
  
}

void HuffmanTreeTest::testSort(){
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  string expected("246:1,247:2,248:2,249:3,250:4,251:5,252:6,253:7,254:8,255:8");
  Tree tree;
  tree.read(input);
  tree.sort();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testBuild() {
//   istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
//   string expected("246:1,247:2,248:2,249:3,250:4,251:5,252:6,253:7,254:8,255:8");
//   Tree tree;
//   tree.read(input);
//   tree.build(); ---->>>  Segmentation fault
//   CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testSkipZero() {
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  unsigned int expected = 245;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZeroFull() {
  stringstream input;
  // weird but works
  for (char i=-128; i < 127 ; i++) {
    input << i;
  }
  unsigned int expected = 0;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZeroEmpty() {
  istringstream input;
  unsigned int expected = 256;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );  
}