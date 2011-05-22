#ifndef _ppmc_m_1frequency_table_test_h_
#define _ppmc_m_1frequency_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../M_1FrequencyTable.h"

namespace ppmc {
	class M_1FrequencyTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( M_1FrequencyTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCompress_zero );
		CPPUNIT_TEST( testCompress_a );
		CPPUNIT_TEST( testCompress_b );
		CPPUNIT_TEST( testCompress_c );
		CPPUNIT_TEST( testCompress_a_with_context );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testCompress_zero();
		void testCompress_a();
		void testCompress_b();
		void testCompress_c();
		void testCompress_a_with_context();
	};
}

#endif //_ppmc_m_1frequency_table_test_h_