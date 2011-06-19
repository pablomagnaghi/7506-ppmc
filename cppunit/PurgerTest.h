#ifndef _ppmc_purger_test_h_
#define _ppmc_purger_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Purger.h"

namespace ppmc {
	class PurgerTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( PurgerTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
	};
}

#endif //_ppmc_purger_test_h_