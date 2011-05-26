#ifndef _ppmc_query_test_h_
#define _ppmc_query_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Query.h"

namespace ppmc {
	class QueryTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( QueryTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testExclusion );
		CPPUNIT_TEST( testFound );
		CPPUNIT_TEST( testTerm );
		CPPUNIT_TEST( testClear );
		CPPUNIT_TEST( testProbability );
		CPPUNIT_TEST_SUITE_END();
  
	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testExclusion();
		void testFound();
		void testTerm();
		void testClear();
		void testProbability();
	};
}

#endif //_ppmc_query_test_h_