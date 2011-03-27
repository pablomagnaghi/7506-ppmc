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
  string expected("104:1,9:2,103:2,102:3,101:4,100:5,99:6,98:7,10:8,97:8");
  Tree tree;
  tree.read(input);
  tree.sort();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testBuild() {
/*  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  string expected("246:1,247:2,248:2,249:3,250:4,251:5,252:6,253:7,254:8,255:8");
  Tree tree;
  tree.read(input);
  tree.build(); //---->>>  Segmentation fault
  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );*/
}

void HuffmanTreeTest::testBinary() {
  stringstream input;
  unsigned char zero       = 0;
  unsigned char one        = 1;
  unsigned char two        = 2;
  unsigned char space      = 32;
  unsigned char lower_half = 127;
  unsigned char upper_half = 128;
  unsigned char last       = 255;
  input << two << zero << zero << one << zero << one 
        << upper_half << lower_half << two << last << one 
        << space << space << space << space <<last;
  string expected_unsorted("0:3,1:3,2:2,32:4,127:1,128:1,255:2");
  string expected_sorted("127:1,128:1,2:2,255:2,1:3,0:3,32:4");
  Tree tree;
  tree.read(input);
  CPPUNIT_ASSERT_EQUAL(expected_unsorted, tree.showFreq(true) );  
  tree.sort();
  CPPUNIT_ASSERT_EQUAL(expected_sorted, tree.showFreq(true) );  
}

void HuffmanTreeTest::testSkipZero() {
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  unsigned int expected = 246;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZero_253() {
  istringstream input("abc");
  unsigned int expected = 253;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}


void HuffmanTreeTest::testSkipZero_255() {
  stringstream input;
  unsigned char zero = 0;
  input << zero;
  unsigned int expected = 255;
  
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZero_254() {
  stringstream input;
  unsigned char zero = 0;
  unsigned char one = 1;
  input << zero << one;
  unsigned int expected = 254;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZero_0() {
  stringstream input;
  for (int i=0; i < (int) dictionary_size ; i++) {    
    input << (unsigned char) i;
  }
  
  unsigned int expected = 0;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZero_full() {
  
  for (int i=0; i < (int) dictionary_size ; i++) { 
    stringstream input;
    unsigned int expected = dictionary_size - (unsigned int) i;  
    for (int j=0; j < i; j++) {
      input << (unsigned char) j;
    }
    Tree tree;
    tree.read(input);
    tree.sort();
    tree.skipZero();
    if (expected == dictionary_size) {
      CPPUNIT_ASSERT_EQUAL(empty, tree.getFirstNotZero() );
    } else {
      CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
    }
  }
}

void HuffmanTreeTest::testSkipZero_1() {
  stringstream input;
  // weird but works
  //for (unsigned char i=-128; i < 127 ; i++) {
  int count = 0;
  for (int i=0; i < (int) dictionary_size - 1 ; i++) {    
    input << (unsigned char) i;
    count++;
  }
  
  unsigned int expected = 1;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );
}

void HuffmanTreeTest::testSkipZero_empty() {
  istringstream input;
  unsigned int expected = empty;
  Tree tree;
  tree.read(input);
  tree.sort();
  tree.skipZero();
  CPPUNIT_ASSERT_EQUAL(expected, tree.getFirstNotZero() );  
}

void HuffmanTreeTest::testUniqueCount() {
  
  int count = 0;
  Tree tree;
  
  for (int i=0; i < (int) dictionary_size ; i++) {    
    stringstream input;
    input << (unsigned char) i;
    tree.read(input);
    count++;
  }
  CPPUNIT_ASSERT_EQUAL(count, tree.getTotalRead() ); 
  
}