#ifndef _huffman_node_test_hpp
#define _huffman_node_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"
namespace huffman {
class HuffmanNodeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HuffmanNodeTest );
  CPPUNIT_TEST( testConstructor );
//  CPPUNIT_TEST(  );
//  CPPUNIT_TEST_EXCEPTION( testDecodeOddDigit, OddDigitException);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
};
}
#endif  // _huffman_node_test_hpp