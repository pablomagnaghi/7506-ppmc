#ifndef _lz78_compressor_test_hpp
#define _lz78_compressor_test_hpp

#include <cppunit/extensions/HelperMacros.h>

namespace lz78 {
class CompressorTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( CompressorTest );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testFind);
	CPPUNIT_TEST( testAdd);
	CPPUNIT_TEST( testCompress_a );
	CPPUNIT_TEST( testCompress_ab );
	CPPUNIT_TEST( testCompress_ABAAABACABACA );
	CPPUNIT_TEST( testCompress_ABAABAAC );
	CPPUNIT_TEST( testCompress_person);
	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void testConstructor();
	void testFind();
	void testAdd();
	void testCompress_a();
	void testCompress_ab();
	void testCompress_ABAAABACABACA();
	void testCompress_ABAABAAC();
	void testCompress_person();
};
}
#endif  // _lz78_compressor_test_hpp
