#ifndef _ppmc_model_test_h_
#define _ppmc_model_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Model.h"

namespace ppmc {
	class ModelTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ModelTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testFind );
		CPPUNIT_TEST( testEmptyFind );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testFind();
		void testEmptyFind();
	};
}

#endif //_ppmc_model_test_h_