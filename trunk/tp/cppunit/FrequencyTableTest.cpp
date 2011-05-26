#include "FrequencyTableTest.h"

#include "../PPMC.h"
#include "../FrequencyTable.h"
#include "../Query.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( FrequencyTableTest );


void FrequencyTableTest::setUp(){

}


void FrequencyTableTest::tearDown(){
}                               


void FrequencyTableTest::testConstructor(){
	
}

void FrequencyTableTest::testCompress_a(){
	FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
}

void FrequencyTableTest::testCompress_a_b(){
	FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	
	q.setTerm('b');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (probabilityType) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
}

void FrequencyTableTest::testCompress_a_b_c(){
	FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	
	q.setTerm('b');
	c.compress(q);
	
	q.setTerm('c');
	
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (probabilityType) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(probabilityType) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 4,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('c'));
}


void FrequencyTableTest::testCompress_a_a(){
	FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	q.setTerm('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);	
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
}

void FrequencyTableTest::testCompress_a_a_a(){
	FrequencyTable c;
	Query q;
	q.setTerm('a');
	c.compress(q);
	q.setTerm('a');
	c.compress(q);
	q.setTerm('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 3,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
}

void FrequencyTableTest::testCompress_b_a_b(){
	FrequencyTable c;
	Query q;
	q.setTerm('b');
	c.compress(q);
	q.setTerm('a');
	c.compress(q);
	q.setTerm('b');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 4,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
}

void FrequencyTableTest::testCompress_b_a_b_with_context() {
	FrequencyTable c;
	Query q;
	
	q.setTerm('a');
	c.compress(q);
	q.setTerm('b');
	c.compress(q);
	q.setTerm('b');
	q.addExclusion('a');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
	
	
}