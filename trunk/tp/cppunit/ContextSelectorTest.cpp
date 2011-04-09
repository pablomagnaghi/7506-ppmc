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
	CPPUNIT_ASSERT_EQUAL(expectedName , e.contextName );
}

void ContextSelectorTest::testBadConstructor(){
	size_t expectedSize = 3;
	ContextSelector e(expectedSize);
	
}
void ContextSelectorTest::testAdd(){
//	ContextSelector e(3);
//	unsigned int pos = 97;
//	CPPUNIT_ASSERT_EQUAL(pos, e.find('a') );
}

void ContextSelectorTest::testGet(){
//	ContextSelector e(3);
//	unsigned int pos = 0;
//	CPPUNIT_ASSERT_EQUAL(pos, e.find('\0') );
}

void ContextSelectorTest::testAddBadSize() {
	
}

void ContextSelectorTest::testAddBadSize0() {
	
}
