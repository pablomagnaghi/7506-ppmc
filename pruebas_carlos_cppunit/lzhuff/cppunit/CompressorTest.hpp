#ifndef _lzHuff_compressor_test_hpp
#define _lzHuff_compressor_test_hpp

#include <cppunit/extensions/HelperMacros.h>

namespace lzHuff {
class CompressorTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( CompressorTest );
	CPPUNIT_TEST( testConstructor );
// 	CPPUNIT_TEST( testFind);
// 	CPPUNIT_TEST( testAdd);
 	CPPUNIT_TEST( testWindowAdd );
	CPPUNIT_TEST( testCompress_A );
	CPPUNIT_TEST( testCompress_ABE );
	CPPUNIT_TEST( testCompress_ABECBE );
	//CPPUNIT_TEST( testCompress_ABECBECBECBEDBE );
// 	CPPUNIT_TEST( testCompress_ABAAABACABACA );
// 	CPPUNIT_TEST( testCompress_ABAABAAC );
// 	CPPUNIT_TEST( testCompress_person);
// 	
// 	CPPUNIT_TEST( testDecompress_a );
// 	CPPUNIT_TEST( testDecompress_ab );
// 	CPPUNIT_TEST( testDecompress_aba );
// 	CPPUNIT_TEST( testDecompress_ABAAABACABACA );
// 	CPPUNIT_TEST( testDecompress_ABAABAAC );
// 	CPPUNIT_TEST( testDecompress_person );
	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void testConstructor();
// 	void testFind();
 	void testWindowAdd();
	void testCompress_A();
	void testCompress_ABE();
	void testCompress_ABECBE();
	void testCompress_ABECBECBECBEDBE();
// 	void testCompress_ABAAABACABACA();
// 	void testCompress_ABAABAAC();
// 	void testCompress_person();
// 	void testDecompress_a();
// 	void testDecompress_ab();
// 	void testDecompress_aba();
// 	void testDecompress_ABAAABACABACA();
// 	void testDecompress_ABAABAAC();
// 	void testDecompress_person();
	
};
}
#endif  // _lzHuff_compressor_test_hpp
