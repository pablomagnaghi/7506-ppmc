#include <string>
#include "CompressorTest.hpp"
#include "../Compressor.hpp"
#include "../../../tp/MockedFileReader.h"
#include "../../../tp/MockedFileWriter.h"

using namespace std;
using namespace lzHuff;
using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( CompressorTest );


void CompressorTest::setUp(){

}


void CompressorTest::tearDown(){
}                               


void CompressorTest::testConstructor(){
	size_t ws=6;
	size_t min_m=2;
	size_t max_m=5;
	Compressor *c = new Compressor(ws,min_m,max_m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("max bits storage error", ws , c->window_size );
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bits bad construction", min_m , c->min_match );
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bits bad construction", max_m , c->max_match );
	
	delete c;
  
}

// void CompressorTest::testFind(){
// 	Compressor *c = new Compressor(6,2,5);
// 	string match;
// 
// 	match = '\0';
// 	CPPUNIT_ASSERT_MESSAGE("Not found", c->find(match));
// 
// 	match = '\255';
// 	CPPUNIT_ASSERT_MESSAGE("Not found", c->find(match));
// 
// 	CPPUNIT_ASSERT_MESSAGE("Not found", c->find("eof")); // toy value
// 	CPPUNIT_ASSERT_MESSAGE("Bogus found", ! c->find("eof1")); // toy value
// 	CPPUNIT_ASSERT_MESSAGE("Not found", c->find("/"));
// 	CPPUNIT_ASSERT_MESSAGE("Bogus found", ! c->find("//"));
// 
// 	delete c;
// }

void CompressorTest::testWindowAdd(){
 	Compressor *c = new Compressor(6,2,5);
 	c->windowAdd('a');
	string reference("a");
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('b');
	reference="ab";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('c');
	reference="abc";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('d');
	reference="abcd";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('e');
	reference="abcde";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('f');
	reference="abcdef";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('g');
	reference="bcdefg";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	c->windowAdd('h');
	reference="cdefgh";
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Bad Window",reference, c->window);
 	delete c;
}

void CompressorTest::testCompress_A(){
	string reference="A'0eof";
	MockedFileReader* in = new MockedFileReader("A");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(6,2,5);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

// void CompressorTest::testDecompress_a(){
// 	string reference="a";
// 	MockedFileReader* in = new MockedFileReader("a'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }

// void CompressorTest::testDecompress_ab(){
// 	string reference="ab";
// 	MockedFileReader* in = new MockedFileReader("ab'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }

void CompressorTest::testCompress_ABE(){
	string reference="A'0B'0E'0eof";
	MockedFileReader* in = new MockedFileReader("ABE");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(6,2,5);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

void CompressorTest::testCompress_ABECBE(){
	string reference="A'0B'0E'0C'23eof";
	MockedFileReader* in = new MockedFileReader("ABECBE");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(6,2,5);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}
void CompressorTest::testCompress_ABECBECBECBEDBE(){
	string reference="A'0B'0E'0C'53C'0ceof";
//MockedFileReader* in = new MockedFileReader("ABECBECBECBEDBE");
	MockedFileReader* in = new MockedFileReader("ABECBECBEC");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor(6,2,5);
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());

	delete in;
	delete out;
	delete c;
}

// void CompressorTest::testDecompress_aba(){
// 	string reference="aba";
// 	MockedFileReader* in = new MockedFileReader("aba'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }

// void CompressorTest::testCompress_person(){
// 	string reference="PEP/'257RSON'260'258E'262'266RT'256";
// 	MockedFileReader* in = new MockedFileReader("PEP/PERSON/PEPERS/PERT");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->compress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }
// 
// void CompressorTest::testDecompress_person(){
// 	string reference="PEP/PERSON/PEPERS/PERT";
// 	MockedFileReader* in = new MockedFileReader("PEP/'257RSON'260'258E'262'266RT'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }
// 
// void CompressorTest::testCompress_ABAABAAC() {
// 	string reference="ABA'257'259C'256";
// 	MockedFileReader* in = new MockedFileReader("ABAABAAC");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->compress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }
// 
// void CompressorTest::testDecompress_ABAABAAC() {
// 	string reference="ABAABAAC";
// 	MockedFileReader* in = new MockedFileReader("ABA'257'259C'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }
// 
// void CompressorTest::testCompress_ABAAABACABACA(){
// 	string reference="ABA'259'258C'257A'262'256";
// 	MockedFileReader* in = new MockedFileReader("ABAAABACABACA");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->compress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }
// 
// void CompressorTest::testDecompress_ABAAABACABACA(){
// 	string reference="ABAAABACABACA";
// 	MockedFileReader* in = new MockedFileReader("ABA'259'258C'257A'262'256");
// 	MockedFileWriter* out = new MockedFileWriter();
// 	Compressor *c = new Compressor(6,2,5);
// 	c->decompress(in, out);
// 	CPPUNIT_ASSERT_EQUAL(reference, out->get());
// 
// 	delete in;
// 	delete out;
// 	delete c;
// }