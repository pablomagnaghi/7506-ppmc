#include "CompressorTest.h"
#include "../PPMC.h"
#include "../Compressor.h"
#include "../MockedFileReader.h"
#include "../MockedFileWriter.h"

using namespace ppmc;
using namespace std;
using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( CompressorTest );


void CompressorTest::setUp(){

}


void CompressorTest::tearDown(){
}                               


void CompressorTest::testConstructor(){

}

void CompressorTest::testCompress(){
	string reference="sfasdsss";
	MockedFileReader* in = new MockedFileReader("sfasdsss");
	MockedFileWriter* out = new MockedFileWriter();
	Compressor *c = new Compressor();
	c->compress(in, out);
	CPPUNIT_ASSERT_EQUAL(reference, out->get());
}
