#ifndef _ppmc_m_1frequency_table_test_h_
#define _ppmc_m_1frequency_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../M_1FrequencyTable.h"

namespace ppmc {
	class M_1FrequencyTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( M_1FrequencyTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCompress_zero );
		CPPUNIT_TEST( testCompressEof );
		CPPUNIT_TEST( testCompressEof_a_excluded );
		CPPUNIT_TEST( testCompressEof_all_excluded );
		CPPUNIT_TEST( testCompress_1 );
		CPPUNIT_TEST( testCompress_2 );
		CPPUNIT_TEST( testCompress_c );
		CPPUNIT_TEST( testCompress_a_with_context );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testCompress_zero();
		void testCompressEof();
		void testCompressEof_a_excluded();
		void testCompressEof_all_excluded();
		void testCompress_1();
		void testCompress_2();
		void testCompress_c();
		void testCompress_a_with_context();
	};
}

#endif //_ppmc_m_1frequency_table_test_h_