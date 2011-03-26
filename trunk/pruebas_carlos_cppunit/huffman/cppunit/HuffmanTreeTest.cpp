#include <sstream>

#include "HuffmanTreeTest.hpp"
#include "../HuffmanTree.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( HuffmanTreeTest );

using namespace std;
using namespace huffman;

void HuffmanTreeTest::setUp(){
//  input = "4b50040300140003000068af2e9a8b235d7d0045000000390000000800006e696f66742e7478c929225d804d4ea8e565e358a5a2967cdaba214204f4da6fff2451682af9e88fabc03d2a5b4037e06e551d910aa625f1d5d527b6562c25852d2f5eafa1dbd6ca0b48825a506a014b1402140003000000af009a68232e7d8b455d000039000000080000000000000001002000b600008100006900666e2e6f78745074054b0006000001000100360000006b0000000000000023ffaba100fa0000";                                
}


void HuffmanTreeTest::tearDown(){
}                               


void HuffmanTreeTest::testConstructor(){
  int zero = 0;
  string empty;
  Tree tree;
  CPPUNIT_ASSERT_EQUAL(zero , tree.getTotal() );
  CPPUNIT_ASSERT_EQUAL(empty, tree.getFreq(true) );
  
}

void HuffmanTreeTest::testRead(){
  istringstream input("\t\tabcdefgh\nabcdefg\nabcdef\nabcde\nabcd\nabc\nab\na\n");
  string frequencies("9:2,10:8,97:8,98:7,99:6,100:5,101:4,102:3,103:2,104:1");
  Tree tree;
  tree.read(input);
  CPPUNIT_ASSERT_EQUAL(frequencies, tree.getFreq(true) );
  
  
  
}