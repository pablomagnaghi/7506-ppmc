#ifndef _ppmc_context_selector_test_h_
#define _ppmc_context_selector_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../ContextSelector.h"

namespace ppmc {
	class ContextSelectorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ContextSelectorTest );
		CPPUNIT_TEST( testConstructor );
//		CPPUNIT_TEST( testBadConstructor);
//		CPPUNIT_TEST_EXCEPTION( testBadConstructor, std::length_error);
		CPPUNIT_TEST( testAdd );
//		CPPUNIT_TEST_EXCEPTION( testAddBadSize0, std::length_error);
//		CPPUNIT_TEST_EXCEPTION( testAddBadSize, std::length_error);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testBadConstructor();
		void testAdd();
	};
}
#endif  // _ppmc_context_selector_test_h_
