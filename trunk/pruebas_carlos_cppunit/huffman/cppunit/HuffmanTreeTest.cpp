#include <sstream>

#include "HuffmanTreeTest.hpp"
#include "../HuffmanTree.hpp"

using namespace huffman;

CPPUNIT_TEST_SUITE_REGISTRATION( HuffmanTreeTest );

using namespace std;


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

void HuffmanTreeTest::testSemiSort(){
  stringstream input;
  unsigned char zero  = 0;
  unsigned char last  = 255;
  input << last << zero << last;
  string expected("0:1,255:2");
  Tree tree;
  tree.read(input);
  tree.semiSort();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testBuild0() {
  istringstream input;
  string expected;
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild1() {
  istringstream input("a");
  string expected("@:000 $:a(61) #:1");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuildParentage() {
  istringstream input("abc");
  string expected("@:000 $:a(61) #:1");
  Tree tree;
  tree.read(input);
  cout << endl << "read: " << tree.showFreq(true) << endl;;
  tree.build();
  cout << "build freq: " << tree.showFreq(true) << endl;;
  cout << "build tree: " << tree.showTree(true) << endl;;
  tree.buildParentage();
  cout << "parentage freq: " << tree.showFreqMax(true) << endl;;
  //cout << "parentage tree: " << tree.showTree(true) << endl;;
//  cout << showFreq(true);
//  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testBuild2() {
  istringstream input("ab");
  string expected("@:000 $:b(62) #:1\n@:001 $:a(61) #:1\n@:002 $:_(00) #:2[0][1]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild3() {
  istringstream input("abc");
  string expected("@:000 $:a(61) #:1\n@:001 $:b(62) #:1\n@:002 $:c(63) #:1\n@:003 $:_(00) #:2[0][1]\n@:004 $:_(00) #:3[2][3]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild4() {
  istringstream input("abcd");
  string expected("@:000 $:d(64) #:1\n@:001 $:a(61) #:1\n@:002 $:b(62) #:1\n@:003 $:c(63) #:1\n@:004 $:_(00) #:2[2][3]\n@:005 $:_(00) #:2[0][1]\n@:006 $:_(00) #:4[4][5]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild5() {
  istringstream input("abcde");
  string expected("@:000 $:e(65) #:1\n@:001 $:a(61) #:1\n@:002 $:b(62) #:1\n@:003 $:c(63) #:1\n@:004 $:d(64) #:1\n@:005 $:_(00) #:2[2][3]\n@:006 $:_(00) #:2[0][1]\n@:007 $:_(00) #:3[4][5]\n@:008 $:_(00) #:5[6][7]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuildRandom1() {
  istringstream input("abcdabcaba");
  string expected_freq("97:4,98:3,99:2,100:1");
  string expected_sorted("100:1,99:2,98:3,97:4");
  string expected_empty;
  string expected_tree("@:000 $:d(64) #:1\n@:001 $:c(63) #:2\n@:002 $:_(00) #:3[0][1]\n@:003 $:b(62) #:3\n@:004 $:a(61) #:4\n@:005 $:_(00) #:6[2][3]\n@:006 $:_(00) #:10[4][5]");
  
  Tree tree;
  tree.read(input);
  CPPUNIT_ASSERT_EQUAL(expected_freq, tree.showFreq(true) );
  tree.sort();
  CPPUNIT_ASSERT_EQUAL(expected_sorted, tree.showFreq(true) );
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected_empty, tree.showFreq(true) );
  CPPUNIT_ASSERT_EQUAL(expected_tree, tree.showTree(true) );
}

void HuffmanTreeTest::testBuildRandom2() {
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  string expected_freq("9:2,10:8,97:8,98:7,99:6,100:5,101:4,102:3,103:2,104:1");
  string expected_sorted("104:1,9:2,103:2,102:3,101:4,100:5,99:6,98:7,10:8,97:8");
  string expected_empty;
  string expected_tree("@:000 $:h(68) #:1\n@:001 $:_(09) #:2\n@:002 $:g(67) #:2\n@:003 $:_(00) #:3[0][1]\n@:004 $:f(66) #:3\n@:005 $:e(65) #:4\n@:006 $:_(00) #:5[2][3]\n@:007 $:d(64) #:5\n@:008 $:c(63) #:6\n@:009 $:_(00) #:7[4][5]\n@:010 $:b(62) #:7\n@:011 $:_(0a) #:8\n@:012 $:a(61) #:8\n@:013 $:_(00) #:10[6][7]\n@:014 $:_(00) #:13[8][9]\n@:015 $:_(00) #:15[10][11]\n@:016 $:_(00) #:18[12][13]\n@:017 $:_(00) #:28[14][15]\n@:018 $:_(00) #:46[16][17]");
  
  Tree tree;
  tree.read(input);
  CPPUNIT_ASSERT_EQUAL(expected_freq, tree.showFreq(true) );
  tree.sort();
  CPPUNIT_ASSERT_EQUAL(expected_sorted, tree.showFreq(true) );
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected_empty, tree.showFreq(true) );
  CPPUNIT_ASSERT_EQUAL(expected_tree, tree.showTree(true) );
}

// void HuffmanTreeTest::testBuildParentage() {
//   istringstream input("abcdabcaba");
//   string expected_freq("61:4,62:3,63:2,100:1");
//   string expected_sorted("100:1,63:2,62:3,61:4");
//   string expected_tree("\n@:0 $:d(64) #:1\n@:001 $:c(63) #:2\n@:002 $:_(00) #:3[0][1]\n@:003 $:b(62) #:3\n@:004 $:a(61) #:4\n@:005 $:_(00) #:6[2][3]\n@:006 $:_(00) #:10[4][5]");
//   
//   Tree tree;
//   tree.read(input);
//   CPPUNIT_ASSERT_EQUAL(expected_freq, tree.showFreq(true) );
//   tree.sort();
//   CPPUNIT_ASSERT_EQUAL(expected_sorted, tree.showFreq(true) );
//   tree.build();
//   CPPUNIT_ASSERT_EQUAL(expected_empty, tree.showFreq(true) );
//   CPPUNIT_ASSERT_EQUAL(expected_tree, tree.showTree(true) );
//   
// }


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