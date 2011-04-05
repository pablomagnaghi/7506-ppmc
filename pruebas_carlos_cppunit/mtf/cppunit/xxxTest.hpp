#ifndef _mtf_xxx_test_hpp
#define _mtf_xxx_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"
namespace mtf {
class xxxTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( XXXTest );
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
#endif  // _mtf_xxx_test_hpp
