#ifndef _ppmc_frequency_table_test_h_
#define _ppmc_frequency_table_test_h_

#include <cppunit/extensions/HelperMacros.h>

#include "../FrequencyTable.h"

namespace ppmc {
	class FrequencyTableTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE( FrequencyTableTest );
		CPPUNIT_TEST( testConstructor );
		CPPUNIT_TEST( testInsert );
		CPPUNIT_TEST( testCalculateSkip );
		CPPUNIT_TEST( testCalculateTotalNotFound );
		CPPUNIT_TEST( testCalculateTotalFound );
		CPPUNIT_TEST( testCalculateTotalFoundWithExclusion );
		CPPUNIT_TEST( testUpdateExclusion );
		CPPUNIT_TEST( testCompress_a );
		CPPUNIT_TEST( testCompress_a_b );
		CPPUNIT_TEST( testCompress_a_b_c );
		CPPUNIT_TEST( testCompress_a_a );
		CPPUNIT_TEST( testCompress_a_a_a );
		CPPUNIT_TEST( testCompress_b_a_b );
		CPPUNIT_TEST( testCompress_b_a_b_c_WithExclusion );
		CPPUNIT_TEST( testCompress_b_a_b_a_WithExclusion );
		CPPUNIT_TEST( testCompress_a_b_d_a_WithExclusion );
		CPPUNIT_TEST( testCompress_a_b_d_a );
		CPPUNIT_TEST( testCompress_eof );
		CPPUNIT_TEST( testCompressEof_a_b_eof );
		CPPUNIT_TEST( testExclusionAfterCompress );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();
		void testConstructor();
		void testInsert();
		void testCalculateSkip();
		void testCalculateTotalNotFound();
		void testCalculateTotalFound();
		void testCalculateTotalFoundWithExclusion();
		void testUpdateExclusion();
		void testCompress_a();
		void testCompress_a_b();
		void testCompress_a_b_c();
		void testCompress_a_a();
		void testCompress_a_a_a();
		void testCompress_b_a_b();
		void testCompress_b_a_b_c_WithExclusion();
		void testCompress_b_a_b_a_WithExclusion();
		void testCompress_a_b_d_a_WithExclusion();
		void testCompress_a_b_d_a();
		void testCompress_eof();
		void testCompressEof_a_b_eof();
		void testExclusionAfterCompress();
	};
}

#endif //_ppmc_frequency_table_test_h_