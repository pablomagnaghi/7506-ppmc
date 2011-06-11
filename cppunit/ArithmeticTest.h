#ifndef _ppmc_arithmetic_test_h_
#define _ppmc_arithmetic_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Arithmetic.h"

namespace ppmc {
	class ArithmeticTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( ArithmeticTest );
		CPPUNIT_TEST( testConstructorOrder0 );
		CPPUNIT_TEST( testConstructorOrder1 );
		CPPUNIT_TEST_SUITE_END();
		
	public:
		void setUp();
		void tearDown();
		void testConstructorOrder0();
		void testConstructorOrder1();

	private:
		
	};
}
#endif //_ppmc_arithmetic_test_h_