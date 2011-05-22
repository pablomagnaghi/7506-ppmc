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
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 257,p.total);	
	
}

void M_1FrequencyTableTest::testCompress_a(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 257,p.total);
}

void M_1FrequencyTableTest::testCompress_b(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	
	q.setTerm('b');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 257,p.total);
}

void M_1FrequencyTableTest::testCompress_c(){
	M_1FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	
	q.setTerm('b');
	c.compress(q);
	
	q.setTerm('c');
	
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 257,p.total);
}



void M_1FrequencyTableTest::testCompress_a_with_context() {
	M_1FrequencyTable c;
	Query q;
	q.addExclusion('A');
	q.setTerm('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 257,p.total);
}