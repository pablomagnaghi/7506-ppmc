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
	string reference("a");
	string expected_1("ab");
	string expected_0("abc");
	
	e.set(reference);
	CPPUNIT_ASSERT_EQUAL(reference,e.get(0));
	e.add(string("b"));
	CPPUNIT_ASSERT_EQUAL(expected_1, e.get(0));
	e.add('c');
	CPPUNIT_ASSERT_EQUAL(expected_0, e.get(0));

}

void ContextSelectorTest::testSet(){
	ContextSelector e(3);
	string reference("abc");
	e.set(reference);
	CPPUNIT_ASSERT_EQUAL(reference,e.get(0));
}

void ContextSelectorTest::testGet(){
	ContextSelector e(3);
	string reference("abc");
	string expected_0("abc");
	string expected_1("bc");
	string expected_2("c");
	string expected_3("");
	e.set(reference);
	CPPUNIT_ASSERT_EQUAL(expected_0, e.get(0));
	CPPUNIT_ASSERT_EQUAL(expected_1, e.get(1));
	CPPUNIT_ASSERT_EQUAL(expected_2, e.get(2));
	CPPUNIT_ASSERT_EQUAL(expected_3, e.get(3));
}

void ContextSelectorTest::testAddBadSize() {
	
}

void ContextSelectorTest::testAddBadSize0() {
	
}
