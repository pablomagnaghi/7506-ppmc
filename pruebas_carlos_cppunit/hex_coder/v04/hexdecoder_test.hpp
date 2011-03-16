#ifndef hexdecoder_h
#define hexdecoder_h

#include <cppunit/extensions/HelperMacros.h>

class HexDecoderTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HexDecoderTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testDecode );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testDecode(); 
  void testGetCharBufferPtr();
  void testGetCharBufferCopy();
};

#endif  // hexdecoder_h

