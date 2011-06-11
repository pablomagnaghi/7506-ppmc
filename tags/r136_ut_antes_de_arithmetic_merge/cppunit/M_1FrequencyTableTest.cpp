#include "M_1FrequencyTableTest.h"

#include "../PPMC.h"
#include "../M_1FrequencyTable.h"
#include "../Query.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( M_1FrequencyTableTest );


void M_1FrequencyTableTest::setUp(){

}


void M_1FrequencyTableTest::tearDown(){
}                               


void M_1FrequencyTableTest::testConstructor(){
	
}

void M_1FrequencyTableTest::testCompress_zero(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('\0');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);	
	
}

void M_1FrequencyTableTest::testCompressEof(){
	M_1FrequencyTable c;
	Query q;
	c.compressEof(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 256,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
	
}

void M_1FrequencyTableTest::testCompressEof_a_excluded(){
	M_1FrequencyTable c;
	Query q;
	q.addExclusion('a');
	c.compressEof(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 255,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 256,p.total);	
}

void M_1FrequencyTableTest::testCompressEof_all_excluded(){
	M_1FrequencyTable c;
	Query q;
	for (int i=0; i < 256; i++) {
		q.addExclusion((char)i);
	}
	c.compressEof(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);	
}


void M_1FrequencyTableTest::testCompress_1(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('\1');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
}

void M_1FrequencyTableTest::testCompress_2(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('\2');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (probabilityType) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
}

void M_1FrequencyTableTest::testCompress_c(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('c');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (probabilityType) 99,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
}



void M_1FrequencyTableTest::testCompress_a_with_context() {
	M_1FrequencyTable c;
	Query q;
	q.addExclusion('A');
	q.addExclusion('B');
	q.addExclusion('C');
	q.setTerm('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 94,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 254,p.total);
}