#include "ModelTest.h"
#include "../PPMC.h"
#include "../Model.h"
#include "../ContextSelector.h"
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
	FrequencyTable* ft1 = m.find(cs.get(1));
	FrequencyTable* ft2 = m.find(cs.get(1));
	FrequencyTable* ft3 = m.find(cs.get(2));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Not the same context table", ft1, ft2);
	bool comp = (ft1 != ft3);
	CPPUNIT_ASSERT_MESSAGE("Bad context table", comp);
	delete(ft1);
	delete(ft3);
}

