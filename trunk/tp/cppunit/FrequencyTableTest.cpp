#include "FrequencyTableTest.h"

#include "../PPMC.h"
#include "../FrequencyTable.h"
#include "../Query.h"

using namespace ppmc;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( FrequencyTableTest );


void FrequencyTableTest::setUp(){

}


void FrequencyTableTest::tearDown(){
}                               


void FrequencyTableTest::testConstructor(){
	
}

/**
 * We expect an ESC(1/1)
 */
void FrequencyTableTest::testCompress_a(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
}

/**
 * We expect an ESC(1/2)
 */
void FrequencyTableTest::testCompress_a_b(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('b');
	ft.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('b'));
}

/**
 * We expect an ESC(2/4)
 */
void FrequencyTableTest::testCompress_a_b_c(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('b');
	ft.compress(q);
	q.clear();
	q.setTerm('c');
	ft.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 2,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 4,p.total);
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('b'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('c'));
}

/**
 * We expect an a(1/2)
 */
void FrequencyTableTest::testCompress_a_a(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('a');
	ft.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);	
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", ! q.isExcluded('a'));
}

/**
 * We expect an a(2/3)
 */
void FrequencyTableTest::testCompress_a_a_a(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('a');
	ft.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 3,p.total);
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", ! q.isExcluded('a'));
}

/**
 * We expect an b(1/4)
 */
void FrequencyTableTest::testCompress_b_a_b(){
	FrequencyTable ft;
	Query q;
	q.setTerm('b');
	ft.compress(q);
	q.clear();
	q.setTerm('a');
	ft.compress(q);
	q.clear();
	q.setTerm('b');
	ft.compress(q);
	
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 1,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 4,p.total);
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", ! q.isExcluded('b'));
}
/**
 * We expect an ESC(1/1)
 */
void FrequencyTableTest::testCompress_b_a_b_c_WithExclusion() {
	FrequencyTable ft;
	Query q;
	Probability p;
	
	q.setTerm('b');
	ft.compress(q);
	q.clear();
	
	q.setTerm('a');
	ft.compress(q);
	q.clear();

	q.setTerm('b');
	ft.compress(q);

	
	q.setTerm('c');
	q.addExclusion('a');
	q.addExclusion('b');

	ft.compress(q);
	p = q.getProbability();
	
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);
	
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('b'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('c'));

}

/**
 * We expect an a(1/2)
 */
void FrequencyTableTest::testCompress_b_a_b_a_WithExclusion() {
	cout << " testCompress_b_a_b_a_WithExclusion " << endl;
	FrequencyTable ft;
	Query q;
	Probability p;
	
	q.setTerm('b');
	ft.compress(q);
	q.clear();
	
	q.setTerm('a');
	ft.compress(q);
	q.clear();

	q.setTerm('b');
	ft.compress(q);

	q.setTerm('a');
	q.addExclusion('b');
	ft.compress(q);

	p = q.getProbability();
	
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);

}

/**
 * We expect an a(1/2)
 */
void FrequencyTableTest::testCompress_a_b_d_a_WithExclusion() {
	cout << " testCompress_a_b_d_a_WithExclusion " << endl;
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	
	q.setTerm('b');
	ft.compress(q);
	
	q.setTerm('d');
	ft.compress(q);
	
	q.setTerm('a');
	ft.compress(q);

	Probability p = q.getProbability();
	
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 2,p.total);
}

/**
 * We expect an a(1/2)
 */
void FrequencyTableTest::testCompress_a_b_d_a() {
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	
	q.setTerm('b');
	ft.compress(q);
	
	q.setTerm('d');
	ft.compress(q);
	
	q.clear();
	q.setTerm('a');
	ft.compress(q);

	Probability p = q.getProbability();
	
	CPPUNIT_ASSERT_MESSAGE("Bad Found", q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 6,p.total);
}

void FrequencyTableTest::testCompress_eof(){
	FrequencyTable ft;
	Query q;
	ft.compressEof(q);
	Probability p = q.getProbability();
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 1,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);
}

void FrequencyTableTest::testCompressEof_a_b_eof(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	q.setTerm('b');
	ft.compress(q);
	q.addExclusion('b');
	ft.compressEof(q);
	Probability p = q.getProbability();
	
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('a'));
	CPPUNIT_ASSERT_MESSAGE("Bad Exclusion", q.isExcluded('b'));
	
	CPPUNIT_ASSERT_MESSAGE("Bad Found", ! q.isFound());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Skip",  (probabilityType) 0,p.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Width", (probabilityType) 2,p.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Total", (probabilityType) 1,p.total);
}

void FrequencyTableTest::testExclusionAfterCompress(){
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.compress(q);
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_MESSAGE("Bad exclusion", q.isExcluded('a'));
}

void FrequencyTableTest::testInsert() {
	FrequencyTable ft;
	ft.insert('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad insertion", (probabilityType) 1, ft.calculateWidth('a'));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bogus insertion", (probabilityType) 0, ft.calculateWidth('b'));
}

void FrequencyTableTest::testCalculateSkip() {
	FrequencyTable ft;
	Query q;
	ft.insert('a');
	q.setTerm('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad skip", (probabilityType)0, ft.calculateSkip(q));
	ft.insert('b');
	q.setTerm('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad skip", (probabilityType)0, ft.calculateSkip(q));
	q.setTerm('b');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad skip", (probabilityType)1, ft.calculateSkip(q));
}

/**
 * Remember that despite of that we expect a total of one because of the ESC,
 * that behavior is resolved in compress()
 */
void FrequencyTableTest::testCalculateTotalNotFound() {
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad total", (probabilityType)0, ft.calculateTotal(q));
}

void FrequencyTableTest::testCalculateTotalFound() {
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.insert('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad total", (probabilityType)1, ft.calculateTotal(q));
}

void FrequencyTableTest::testCalculateTotalFoundWithExclusion() {
	FrequencyTable ft;
	Query q;
	q.setTerm('a');
	ft.insert('a');
	q.addExclusion('a');
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad total", (probabilityType)0, ft.calculateTotal(q));
}

void FrequencyTableTest::testUpdateExclusion() {
	FrequencyTable ft;
	Query q;
	ft.insert('a');
	ft.updateExclusion(q);
	CPPUNIT_ASSERT_MESSAGE("Bogus exclusion", ! q.isExcluded('b'));
	CPPUNIT_ASSERT_MESSAGE("Bad exclusion", q.isExcluded('a'));
}

