#ifndef _ppmc_compressor_test_h_
#define _ppmc_compressor_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../Compressor.h"

namespace ppmc {
	class CompressorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( CompressorTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testCalculateCeiling_0_1_1 );
		CPPUNIT_TEST( testCalculateCeiling_0_1_2 );
		CPPUNIT_TEST( testCalculateCeiling_1_1_2 );
//		CPPUNIT_TEST( testCalculateCeiling );
		CPPUNIT_TEST( testCalculateFloor_0_1_1 );
		CPPUNIT_TEST( testCalculateFloor_0_1_2 );
		CPPUNIT_TEST( testCalculateFloor_1_1_2 );
		//CPPUNIT_TEST( testCalculateFloor );
		CPPUNIT_TEST( testCalculate_c );
		CPPUNIT_TEST( testCompressWithM_1);
		CPPUNIT_TEST( testCompressWithModels_0);
//		CPPUNIT_TEST( testCompressWithModels_1);
//		CPPUNIT_TEST( testCompressWithModels_2);
//		CPPUNIT_TEST( testCompressEof_M_1() );
//		CPPUNIT_TEST( testCompressEof_M0() );
//		CPPUNIT_TEST( testCompressEof_M1() );
//		CPPUNIT_TEST( testCompress );
		CPPUNIT_TEST_SUITE_END();
		
	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testCompress();
		void testCalculateCeiling_0_1_1();
		void testCalculateCeiling_0_1_2();
		void testCalculateCeiling_1_1_2();
		void testCalculateCeiling();
		void testCalculateFloor_0_1_1();
		void testCalculateFloor_0_1_2();
		void testCalculateFloor_1_1_2();
		void testCalculateFloor();
		void testCalculate_c();
		void testCompressWithM_1();
		void testCompressWithModels_0();
		void testCompressWithModels_1();
		void testCompressWithModels_2();
		void testCompressEof_M_1();
		void testCompressEof_M0();
		void testCompressEof_M1();
		static baseType delta;
	};
}

#endif //_ppmc_compressor_test_h_