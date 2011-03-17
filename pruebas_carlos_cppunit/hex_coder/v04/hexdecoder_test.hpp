#ifndef hexdecoder_h
#define hexdecoder_h

#include <string>

#include <cppunit/extensions/HelperMacros.h>

class HexDecoderTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( HexDecoderTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testDecode );
  CPPUNIT_TEST( testGetAsString);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testDecode(); 
  void testGetCharBufferPtr();
  void testGetCharBufferCopy();
  void testGetAsString();
private:
  std::string input;
  static unsigned char expected[];
};

#endif  // hexdecoder_h

