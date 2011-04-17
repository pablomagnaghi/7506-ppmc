#include "QueryTest.h"
#include "../PPMC.h"
#include "../Query.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( QueryTest );


void QueryTest::setUp(){

}


void QueryTest::tearDown(){
}                               


void QueryTest::testConstructor(){
	
}

void QueryTest::testExclusion() {
	Query q;
	q.addExclusion('a');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 1, q.exclusion.size());
	q.addExclusion('a');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 1, q.exclusion.size());
	q.addExclusion('b');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (size_t) 2, q.exclusion.size());
	
}

void QueryTest::testFound(){
	Query q;
	q.setFound(true);
	CPPUNIT_ASSERT_MESSAGE("Bad found", q.isFound());
	q.setFound(false);
	CPPUNIT_ASSERT_MESSAGE("Bad found", ! q.isFound());
	
}

void QueryTest::testTerm() {
	Query q;
	q.setTerm('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad term", 'a', q.getTerm());
	q.setTerm('b');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad term", 'b', q.getTerm());
}

void QueryTest::testProbability() {

}

