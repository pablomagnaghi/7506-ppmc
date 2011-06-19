#include "ArithmeticTest.h"
#include "../PPMC.h"
#include "../Arithmetic.h"


using namespace ppmc;
using namespace std;
using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( ArithmeticTest );

void ArithmeticTest::setUp(){
	
}


void ArithmeticTest::tearDown(){
}                               


void ArithmeticTest::testConstructorOrder0(){
	Arithmetic *c = new Arithmetic(0);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad models size", (size_t) 1, c->models.size());
	delete(c);
}

void ArithmeticTest::testConstructorOrder1(){
	Arithmetic *c = new Arithmetic(1);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad models size", (size_t) 2, c->models.size());
	delete(c);
}
