#ifndef _huffman_tree_test_hpp
#define _huffman_tree_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"

class HuffmanTreeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HuffmanTreeTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testRead );
  CPPUNIT_TEST( testSort );
  CPPUNIT_TEST( testBuild );
  CPPUNIT_TEST( testSkipZero );
  CPPUNIT_TEST( testSkipZeroFull );
  CPPUNIT_TEST( testSkipZeroEmpty );
//  CPPUNIT_TEST(  );
//  CPPUNIT_TEST_EXCEPTION( testDecodeOddDigit, OddDigitException);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testRead(); 
  void testSort(); 
  void testBuild();
  void testSkipZero();
  void testSkipZeroFull();
  void testSkipZeroEmpty();
private:
//  std::string input;
//  static unsigned char expected[];
};

#endif  // _huffman_tree_test_hpp


