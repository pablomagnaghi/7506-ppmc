#include "ContextTest.h"

#include "../PPMC.h"
#include "../Context.h"
#include "../Query.h"
#include "../Response.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ContextTest );


void ContextTest::setUp(){

}


void ContextTest::tearDown(){
}                               


void ContextTest::testConstructor(){
	
}

void ContextTest::testEval_a(){
	Context c;
	Query q;
	q.setChar('a');
	Response r = c.eval(q);
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, r.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 1,p.total);
}

void ContextTest::testEval_a_b(){
	Context c;
	Query q;
	q.setChar('a');
	c.eval(q);
	
	q.setChar('b');
	Response r = c.eval(q);
	
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, r.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 2,p.total);

//	std::list<char> exclusion;
//	exclusion.push_front('a');
//	exclusion.push_front('b');
	
	// test for 'ab' and only 'ab' in exclusion list
}

void ContextTest::testEval_a_b_c(){
	Context c;
	Query q;
	q.setChar('a');
	c.eval(q);
	
	q.setChar('b');
	c.eval(q);
	
	q.setChar('c');
	
	Response r = c.eval(q);
	
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", false, r.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip", (unsigned int) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width",(unsigned int) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 4,p.total);

//	std::list<char> exclusion;
//	exclusion.push_front('a');
//	exclusion.push_front('b');
//	exclusion.push_front('c');

	// test for 'abc' and only 'abc' in exclusion list
}


void ContextTest::testEval_a_a(){
	Context c;
	Query q;
	std::list<char> exclusion;
	exclusion.push_front('a');
	q.setChar('a');
	c.eval(q);
	Response r = c.eval(q);
	
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, r.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 2,p.total);	
}

void ContextTest::testEval_a_a_a(){
	Context c;
	Query q;
	q.setChar('a');
	c.eval(q);
	c.eval(q);
	Response r = c.eval(q);
	
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Found", true, r.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (unsigned int) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (unsigned int) 3,p.total);
	
}