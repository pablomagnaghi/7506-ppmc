#ifndef hexdecoder_test_hpp
#define hexdecoder_test_hpp

#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "../OddDigitException.hpp"
#include "../InvalidDigitException.hpp"

class HexDecoderTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HexDecoderTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testDecode );
  CPPUNIT_TEST( testDecodeInvalidDigit );
  CPPUNIT_TEST( testDecodeOddDigit );
  CPPUNIT_TEST_EXCEPTION( testDecodeInvalidDigit, InvalidDigitException);
  CPPUNIT_TEST_EXCEPTION( testDecodeOddDigit, OddDigitException);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testDecode(); 
  void testGetCharBufferPtr();
  void testGetCharBufferCopy();
  void testGetAsString();
  void testDecodeInvalidDigit();
  void testDecodeOddDigit();
private:
  std::string input;
  static unsigned char expected[];
};

#endif  // hexdecoder_test_hpp

