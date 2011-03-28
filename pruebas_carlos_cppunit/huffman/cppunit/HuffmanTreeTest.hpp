#ifndef _huffman_tree_test_hpp
#define _huffman_tree_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"
namespace huffman {
class HuffmanTreeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HuffmanTreeTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testRead );
  CPPUNIT_TEST( testSort );
  CPPUNIT_TEST( testSemiSort );
  CPPUNIT_TEST( testBinary );
  CPPUNIT_TEST( testUniqueCount );
  CPPUNIT_TEST( testBuild );
  CPPUNIT_TEST( testSkipZero );
  CPPUNIT_TEST( testSkipZero_255 );
  CPPUNIT_TEST( testSkipZero_254 );
  CPPUNIT_TEST( testSkipZero_253 );
  CPPUNIT_TEST( testSkipZero_empty );
  CPPUNIT_TEST( testSkipZero_full );
  CPPUNIT_TEST( testSkipZero_0 );
  CPPUNIT_TEST( testSkipZero_1 );
//  CPPUNIT_TEST(  );
//  CPPUNIT_TEST_EXCEPTION( testDecodeOddDigit, OddDigitException);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testRead(); 
  void testBinary();
  void testUniqueCount();
  void testSort(); 
  void testSemiSort();
  void testBuild();
  void testSkipZero();
  void testSkipZero_255();
  void testSkipZero_254();
  void testSkipZero_253();
  void testSkipZero_empty();
  void testSkipZero_full();
  void testSkipZero_0();
  void testSkipZero_1();
private:
//  std::string input;
//  static unsigned char expected[];
};
}
#endif  // _huffman_tree_test_hpp


