#ifndef _ppmc_context_table_test_h_
#define _ppmc_context_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../ContextTable.h"

namespace ppmc {
	class ContextTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ContextTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testEval_a );
		CPPUNIT_TEST( testEval_a_b );
		CPPUNIT_TEST( testEval_a_b_c );
		CPPUNIT_TEST( testEval_a_a );
		CPPUNIT_TEST( testEval_a_a_a );
		CPPUNIT_TEST( testEval_b_a_b );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testEval_a();
		void testEval_a_b();
		void testEval_a_b_c();
		void testEval_a_a();
		void testEval_a_a_a();
		void testEval_b_a_b();
	};
}

#endif //_ppmc_context_table_test_h_