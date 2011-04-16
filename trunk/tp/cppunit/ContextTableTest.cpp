#include "ContextTableTest.h"

#include "../PPMC.h"
#include "../ContextTable.h"
#include "../Query.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ContextTableTest );


void ContextTableTest::setUp(){

}


void ContextTableTest::tearDown(){
}                               


void ContextTableTest::testConstructor(){
	
}

void ContextTableTest::testCompress_a(){
	ContextTable c;
	Query q;
	q.setChar('a');
	c.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 1,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 1, q.exclusion.size());
	
}

void ContextTableTest::testCompress_a_b(){
	ContextTable c;
	Query q;
	q.setChar('a');
	c.compress(q);
	
	q.setChar('b');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 2,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 2, q.exclusion.size());
}

void ContextTableTest::testCompress_a_b_c(){
	ContextTable c;
	Query q;
	q.setChar('a');
	c.compress(q);
	
	q.setChar('b');
	c.compress(q);
	
	q.setChar('c');
	
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 4,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('c'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 3, q.exclusion.size());

}


void ContextTableTest::testCompress_a_a(){
	ContextTable c;
	Query q;
	q.setChar('a');
	c.compress(q);
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 2,p.total);	
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 1, q.exclusion.size());
}

void ContextTableTest::testCompress_a_a_a(){
	ContextTable c;
	Query q;
	q.setChar('a');
	c.compress(q);
	c.compress(q);
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 3,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 1, q.exclusion.size());
	
}

void ContextTableTest::testCompress_b_a_b(){
	ContextTable c;
	Query q;
	q.setChar('b');
	c.compress(q);
	q.setChar('a');
	c.compress(q);
	q.setChar('b');
	c.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 4,p.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion", true, q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 2, q.exclusion.size());
	
}