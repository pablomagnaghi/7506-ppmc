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
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('a'));
	q.setTerm('a');
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion after setTerm", ! q.isExcluded('a'));
	q.addExclusion('a');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (probabilityType) 1, q.getExclusionSize());
	q.addExclusion('a');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (probabilityType) 1, q.getExclusionSize()); 
	q.addExclusion('b');
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Exclusion not found", q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (probabilityType) 2, q.getExclusionSize());
	
}

void QueryTest::testFound(){
	Query q;
	q.setFound(true);
	CPPUNIT_ASSERT_MESSAGE("Bad found", q.isFound());
	q.setFound(false);
	CPPUNIT_ASSERT_MESSAGE("Bad found", ! q.isFound());
	
}

void QueryTest::testClear() {
	Query q;
	q.setFound(true);
	q.addExclusion('a');
	
	q.clear();
	CPPUNIT_ASSERT_MESSAGE("Bad found", ! q.isFound());
	CPPUNIT_ASSERT_MESSAGE("Bad exclusion", ! q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Exclusion Size", (probabilityType) 0, q.getExclusionSize());
}

void QueryTest::testTerm() {
	Query q;
	q.setTerm('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad term", 'a', q.getTerm());
	q.setTerm('b');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad term", 'b', q.getTerm());
}

void QueryTest::testGetExclusionSize() {
	Query q;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad size", (probabilityType) 0, q.getExclusionSize());
	q.addExclusion('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad size", (probabilityType) 1, q.getExclusionSize());
}

void QueryTest::testTermAndExclusion() {
	Query q;
	q.addExclusion('a');
	q.setTerm('b');
	CPPUNIT_ASSERT_MESSAGE("Bad exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
}
