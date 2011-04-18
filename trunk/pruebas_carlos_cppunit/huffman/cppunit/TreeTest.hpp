#ifndef _huffman_tree_test_hpp
#define _huffman_tree_test_hpp

#include <cppunit/extensions/HelperMacros.h>

//#include "../OddDigitException.hpp"
//#include "../InvalidDigitException.hpp"
namespace huffman {
class TreeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TreeTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testRead );
  CPPUNIT_TEST( testSort );
  CPPUNIT_TEST( testSemiSort );
  CPPUNIT_TEST( testBinary );
  CPPUNIT_TEST( testUniqueCount );
  CPPUNIT_TEST( testBuildAll );
  CPPUNIT_TEST( testBuild0 );
  CPPUNIT_TEST( testBuild1 );
  CPPUNIT_TEST( testBuild2 );
  CPPUNIT_TEST( testBuild3 );
  CPPUNIT_TEST( testBuild4 );
  CPPUNIT_TEST( testBuild5 );
  CPPUNIT_TEST( testBuildRandom1 );
  CPPUNIT_TEST( testBuildRandom2 );
  CPPUNIT_TEST( testBuildChar2CodeMap1 );
  CPPUNIT_TEST( testBuildChar2CodeMap3 );
  CPPUNIT_TEST( testBuildChar2CodeMap4 );
  CPPUNIT_TEST( testBuildChar2CodeMap5 );
  CPPUNIT_TEST( testBuildParentage );
  CPPUNIT_TEST( testSkipZero );
  CPPUNIT_TEST( testSkipZero_255 );
  CPPUNIT_TEST( testSkipZero_254 );
  CPPUNIT_TEST( testSkipZero_253 );
  CPPUNIT_TEST( testSkipZero_empty );
  CPPUNIT_TEST( testSkipZero_full );
  CPPUNIT_TEST( testSkipZero_0 );
  CPPUNIT_TEST( testSkipZero_1 );
  CPPUNIT_TEST( testRepeatedRead );
 // CPPUNIT_TEST( testRepeatedReadBuildAll );
  //CPPUNIT_TEST( testRepeatedSort );
  CPPUNIT_TEST( testSameSort );
  
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
  void testSameSort();
  void testBuildAll();
  void testBuild0();
  void testBuild1();
  void testBuild2();
  void testBuild3();
  void testBuild4();
  void testBuild5();
  void testBuildRandom1();
  void testBuildRandom2();
  void testBuildChar2CodeMap1();
  void testBuildChar2CodeMap3();
  void testBuildChar2CodeMap4();
  void testBuildChar2CodeMap5();
  void testBuildParentage();
  void testSkipZero();
  void testSkipZero_255();
  void testSkipZero_254();
  void testSkipZero_253();
  void testSkipZero_empty();
  void testSkipZero_full();
  void testSkipZero_0();
  void testSkipZero_1();
  void testRepeatedRead();
  void testRepeatedReadBuildAll();
  void testRepeatedSort();
private:
//  std::string input;
//  static unsigned char expected[];
};
}
#endif  // _huffman_tree_test_hpp

