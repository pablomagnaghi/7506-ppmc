#include "ContextSelectorTest.h"
#include "../PPMC.h"
#include "../ContextSelector.h"

#include <sstream>
#include <iostream>

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ContextSelectorTest );


void ContextSelectorTest::setUp(){

}


void ContextSelectorTest::tearDown(){
}                               


void ContextSelectorTest::testConstructor(){
	string expectedName("");
	size_t expectedSize = 3;
	ContextSelector cs(expectedSize);
	
  CPPUNIT_ASSERT_EQUAL(expectedSize , cs.size );
	CPPUNIT_ASSERT_EQUAL(expectedName , cs.name );
}

void ContextSelectorTest::testBadConstructor(){
	//ContextSelector e(16);
//	CPPUNIT_ASSERT_THROW( ContextSelector cs(15), std::length_error* );
}

void ContextSelectorTest::testAdd(){
	ContextSelector cs(3);
	
	cs.add('a');
	CPPUNIT_ASSERT_EQUAL(string("a"),cs.get(1));
	cs.add('b');
	CPPUNIT_ASSERT_EQUAL(string("b"),cs.get(1));
	CPPUNIT_ASSERT_EQUAL(string("ab"),cs.get(2));
	cs.add('c');
	CPPUNIT_ASSERT_EQUAL(string("c"),cs.get(1));
	CPPUNIT_ASSERT_EQUAL(string("bc"),cs.get(2));
	CPPUNIT_ASSERT_EQUAL(string("abc"),cs.get(3));
	cs.add('d');
	CPPUNIT_ASSERT_EQUAL(string("d"),cs.get(1));
	CPPUNIT_ASSERT_EQUAL(string("cd"),cs.get(2));
	CPPUNIT_ASSERT_EQUAL(string("bcd"),cs.get(3));
}

void ContextSelectorTest::testGet() {
	ContextSelector cs(3);
	CPPUNIT_ASSERT_EQUAL(string(""),cs.get(0));
	CPPUNIT_ASSERT_EQUAL(string(""),cs.get(1));
	CPPUNIT_ASSERT_EQUAL(string(""),cs.get(2));
	CPPUNIT_ASSERT_EQUAL(string(""),cs.get(3));

}
