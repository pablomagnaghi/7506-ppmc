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
  string expected("\np:0 v: a(97) c: 1");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuildParentage() {
  istringstream input("a");
  string expected("\np:0 v: a(97) c: 1");
  Tree tree;
  tree.read(input);
  cout << "read: " << tree.showFreq(true) << endl;;
  tree.build();
  cout << "build freq: " << tree.showFreq(true) << endl;;
  cout << "build tree: " << tree.showTree(true) << endl;;
  tree.buildParentage();
  cout << "parentage: " << tree.showFreq(true) << endl;;
//  cout << showFreq(true);
//  CPPUNIT_ASSERT_EQUAL(expected, tree.showFreq(true) );
}

void HuffmanTreeTest::testBuild2() {
  istringstream input("ab");
  string expected("\np:0 v: b(98) c: 1\np:1 v: a(97) c: 1\np:2 v: _(0) c: 2[0][1]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild3() {
  istringstream input("abc");
  string expected("\np:0 v: a(97) c: 1\np:1 v: b(98) c: 1\np:2 v: c(99) c: 1\np:3 v: _(0) c: 2[0][1]\np:4 v: _(0) c: 3[2][3]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild4() {
  istringstream input("abcd");
  string expected("\np:0 v: d(100) c: 1\np:1 v: a(97) c: 1\np:2 v: b(98) c: 1\np:3 v: c(99) c: 1\np:4 v: _(0) c: 2[2][3]\np:5 v: _(0) c: 2[0][1]\np:6 v: _(0) c: 4[4][5]");
  Tree tree;
  tree.read(input);
  tree.build();
  CPPUNIT_ASSERT_EQUAL(expected, tree.showTree(true) );
}

void HuffmanTreeTest::testBuild5() {
  istringstream input("abcde");
  string expected("\np:0 v: e(101) c: 1\np:1 v: a(97) c: 1\np:2 v: b(98) c: 1\np:3 v: c(99) c: 1\np:4 v: d(100) c: 1\np:5 v: _(0) c: 2[2][3]\np:6 v: _(0) c: 2[0][1]\np:7 v: _(0) c: 3[4][5]\np:8 v: _(0) c: 5[6][7]");
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
  string expected_tree("\np:0 v: d(100) c: 1\np:1 v: c(99) c: 2\np:2 v: _(0) c: 3[0][1]\np:3 v: b(98) c: 3\np:4 v: a(97) c: 4\np:5 v: _(0) c: 6[2][3]\np:6 v: _(0) c: 10[4][5]");
  
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
  string expected_tree("\np:0 v: h(104) c: 1\np:1 v: _(9) c: 2\np:2 v: g(103) c: 2\np:3 v: _(0) c: 3[0][1]\np:4 v: f(102) c: 3\np:5 v: e(101) c: 4\np:6 v: _(0) c: 5[2][3]\np:7 v: d(100) c: 5\np:8 v: c(99) c: 6\np:9 v: _(0) c: 7[4][5]\np:10 v: b(98) c: 7\np:11 v: _(10) c: 8\np:12 v: a(97) c: 8\np:13 v: _(0) c: 10[6][7]\np:14 v: _(0) c: 13[8][9]\np:15 v: _(0) c: 15[10][11]\np:16 v: _(0) c: 18[12][13]\np:17 v: _(0) c: 28[14][15]\np:18 v: _(0) c: 46[16][17]");
  
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
//   string expected_freq("97:4,98:3,99:2,100:1");
//   string expected_sorted("100:1,99:2,98:3,97:4");
//   string expected_tree("\np:0 v: d(100) c: 1\np:1 v: c(99) c: 2\np:2 v: _(0) c: 3[0][1]\np:3 v: b(98) c: 3\np:4 v: a(97) c: 4\np:5 v: _(0) c: 6[2][3]\np:6 v: _(0) c: 10[4][5]");
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