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

void ContextTest::testEval(){
	Context c;
	Query q;
	std::list<char> exclusion;
	//exclusion.push_front('l');
	q.setChar('a');
	Response r = c.eval(q);
	Probability p = r.getProbability();
	CPPUNIT_ASSERT_EQUAL((unsigned int) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL((unsigned int) 1,p.width);
	CPPUNIT_ASSERT_EQUAL((unsigned int) 1,p.total);
}
