#include <string>
#include "CompressorTest.hpp"
#include "../Compressor.hpp"
#include "../../../tp/MockedFileReader.h"
#include "../../../tp/MockedFileWriter.h"

using namespace std;
using namespace lz78;
using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( CompressorTest );


void CompressorTest::setUp(){

}


void CompressorTest::tearDown(){
}                               


void CompressorTest::testConstructor(){
	size_t max_bits = 10;
	size_t bits = 9;
	Compressor *c = new Compressor(max_bits);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("max bits storage error", max_bits , c->max_bits );
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bits bad construction", bits , c->bits );
	
	delete c;
  
}
void CompressorTest::testCompress_a(){
	string reference="a'256";
	MockedFileReader* in = new MockedFileReader("a");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
  CPPUNIT_ASSERT_EQUAL(reference, out->get());
	
	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_ab(){
	string reference="aba'256";
	MockedFileReader* in = new MockedFileReader("aba");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
  CPPUNIT_ASSERT_EQUAL(reference, out->get());
	
	delete in;
	delete out;
	delete c;
}
void CompressorTest::testCompress_ababab(){
	string reference="PEP/'257RSON'260'258E262'266RT'256";
	MockedFileReader* in = new MockedFileReader("PEP/PERSON/PEPERS/PERT");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
  CPPUNIT_ASSERT_EQUAL(reference, out->get());
	
	delete in;
	delete out;
	delete c;
}