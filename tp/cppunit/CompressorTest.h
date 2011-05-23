#ifndef _ppmc_compressor_test_h_
#define _ppmc_compressor_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Compressor.h"

namespace ppmc {
	class CompressorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( CompressorTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCompress );
		CPPUNIT_TEST_SUITE_END();
  
	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testCompress();
	};
}

#endif //_ppmc_compressor_test_h_