#ifndef _ppmc_context_table_test_h_
#define _ppmc_context_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../ContextTable.h"

namespace ppmc {
	class ContextTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ContextTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCompress_a );
		CPPUNIT_TEST( testCompress_a_b );
		CPPUNIT_TEST( testCompress_a_b_c );
		CPPUNIT_TEST( testCompress_a_a );
		CPPUNIT_TEST( testCompress_a_a_a );
		CPPUNIT_TEST( testCompress_b_a_b );
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
	};
}

#endif //_ppmc_context_table_test_h_