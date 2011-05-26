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
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);	
	
}

void M_1FrequencyTableTest::testCompress_eof(){
	M_1FrequencyTable c;
	Query q;
	c.compressEof(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 256,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);	
	
}

void M_1FrequencyTableTest::testCompress_1(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('\1');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
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
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
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
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (probabilityType) 99,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
}



void M_1FrequencyTableTest::testCompress_a_with_context() {
	M_1FrequencyTable c;
	Query q;
	q.addExclusion('A');
	q.setTerm('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 97,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 257,p.total);
}