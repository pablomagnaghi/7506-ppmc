#ifndef _ppmc_context_test_h_
#define _ppmc_context_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Context.h"

namespace ppmc {
	class ContextTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ContextTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
	};
}

#endif //_ppmc_context_test_h_