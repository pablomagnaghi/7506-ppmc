#ifndef _ppmc_frequency_table_test_h_
#define _ppmc_frequency_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../FrequencyTable.h"

namespace ppmc {
	class FrequencyTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( FrequencyTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCompress_a );
		CPPUNIT_TEST( testCompress_a_b );
		CPPUNIT_TEST( testCompress_a_b_c );
		CPPUNIT_TEST( testCompress_a_a );
		CPPUNIT_TEST( testCompress_a_a_a );
		CPPUNIT_TEST( testCompress_b_a_b );
		CPPUNIT_TEST( testCompress_b_a_b_with_context );
		CPPUNIT_TEST( testCompress_eof );
		CPPUNIT_TEST( testCompress_a_b_eof );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testCompress_a();
		void testCompress_a_b();
		void testCompress_a_b_c();
		void testCompress_a_a();
		void testCompress_a_a_a();
		void testCompress_b_a_b();
		void testCompress_b_a_b_with_context();
		void testCompress_eof();
		void testCompress_a_b_eof();
	};
}

#endif //_ppmc_frequency_table_test_h_