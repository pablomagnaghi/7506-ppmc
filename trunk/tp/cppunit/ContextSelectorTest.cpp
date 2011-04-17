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
	ContextSelector e(expectedSize);
	
  CPPUNIT_ASSERT_EQUAL(expectedSize , e.size );
	CPPUNIT_ASSERT_EQUAL(expectedName , e.name );
}

void ContextSelectorTest::testBadConstructor(){
	//ContextSelector e(16);
//	CPPUNIT_ASSERT_THROW( ContextSelector e(15), std::length_error* );
}

void ContextSelectorTest::testAdd(){
	ContextSelector e(3);
	
	e.add('a');
	CPPUNIT_ASSERT_EQUAL(string("a"),e.get(1));
	e.add('b');
	CPPUNIT_ASSERT_EQUAL(string("b"),e.get(1));
	CPPUNIT_ASSERT_EQUAL(string("ab"),e.get(2));
	e.add('c');
	CPPUNIT_ASSERT_EQUAL(string("c"),e.get(1));
	CPPUNIT_ASSERT_EQUAL(string("bc"),e.get(2));
	CPPUNIT_ASSERT_EQUAL(string("abc"),e.get(3));
	e.add('d');
	CPPUNIT_ASSERT_EQUAL(string("d"),e.get(1));
	CPPUNIT_ASSERT_EQUAL(string("cd"),e.get(2));
	CPPUNIT_ASSERT_EQUAL(string("bcd"),e.get(3));

}
