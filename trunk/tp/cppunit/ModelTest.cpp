#include "ModelTest.h"
#include "../PPMC.h"
#include "../Model.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ModelTest );


void ModelTest::setUp(){

}


void ModelTest::tearDown(){
}                               


void ModelTest::testConstructor(){
	
}

void ModelTest::testFind() {
	Model m;
	ContextSelector cs(2);
	cs.add('a');
	cs.add('a');
	ContextTable* ct1 = m.find(cs, 1);
	ContextTable* ct2 = m.find(cs, 1);
	ContextTable* ct3 = m.find(cs, 2);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Not the same context table", ct1, ct2);
//	bool comp = (ct1 == ct3);
//	CPPUNIT_ASSERT_MESSAGE("Bad context table", comp);
	delete(ct1);
	delete(ct3);
}

