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

void CompressorTest::testFind(){
	Compressor *c = new Compressor(10);
	string match;

	match = '\0';
	CPPUNIT_ASSERT_MESSAGE("Not found", c->find(match));

	match = '\255';
	CPPUNIT_ASSERT_MESSAGE("Not found", c->find(match));

	CPPUNIT_ASSERT_MESSAGE("Not found", c->find("eof")); // toy value
	CPPUNIT_ASSERT_MESSAGE("Bogus found", ! c->find("eof1")); // toy value
	CPPUNIT_ASSERT_MESSAGE("Not found", c->find("/"));
	CPPUNIT_ASSERT_MESSAGE("Bogus found", ! c->find("//"));

	delete c;
}

void CompressorTest::testAdd(){
	Compressor *c = new Compressor(10);
	c->add("//");
	CPPUNIT_ASSERT_MESSAGE("Not found",c->find("//"));
	
	CPPUNIT_ASSERT_MESSAGE("Bogus found", ! c->find("///"));
	c->add("///");
	CPPUNIT_ASSERT_MESSAGE("Not found",c->find("//"));
	CPPUNIT_ASSERT_MESSAGE("Not found",c->find("///"));
	
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

void CompressorTest::testDecompress_a(){
	string reference="a";
	MockedFileReader* in = new MockedFileReader("a'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testDecompress_ab(){
	string reference="ab";
	MockedFileReader* in = new MockedFileReader("ab'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_aba(){
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

void CompressorTest::testDecompress_aba(){
	string reference="aba";
	MockedFileReader* in = new MockedFileReader("aba'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_person(){
	string reference="PEP/'257RSON'260'258E'262'266RT'256";
	MockedFileReader* in = new MockedFileReader("PEP/PERSON/PEPERS/PERT");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testDecompress_person(){
	string reference="PEP/PERSON/PEPERS/PERT";
	MockedFileReader* in = new MockedFileReader("PEP/'257RSON'260'258E'262'266RT'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_ABAABAAC() {
	string reference="ABA'257'259C'256";
	MockedFileReader* in = new MockedFileReader("ABAABAAC");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testDecompress_ABAABAAC() {
	string reference="ABAABAAC";
	MockedFileReader* in = new MockedFileReader("ABA'257'259C'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_ABAAABACABACA(){
	string reference="ABA'259'258C'257A'262'256";
	MockedFileReader* in = new MockedFileReader("ABAAABACABACA");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testDecompress_ABAAABACABACA(){
	string reference="ABAAABACABACA";
	MockedFileReader* in = new MockedFileReader("ABA'259'258C'257A'262'256");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(10);
	c->decompress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}