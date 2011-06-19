#ifndef _mtf_encoder_test_hpp
#define _mtf_encoder_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"
namespace mtf {
class EncoderTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( EncoderTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testEncode );
  CPPUNIT_TEST( testFind );
  CPPUNIT_TEST( testRearrange );
//  CPPUNIT_TEST(  );
//  CPPUNIT_TEST_EXCEPTION( testDecodeOddDigit, OddDigitException);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testEncode();
  void testFind();
  void testRearrange();
};
}
#endif  // _mtf_xxx_test_hpp
