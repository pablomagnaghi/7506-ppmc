#include "CompressorTest.h"
#include "../PPMC.h"
#include "../Compressor.h"
#include "../MockedFileReader.h"
#include "../MockedFileWriter.h"
#include "../Probability.h"
#include "../ContextSelector.h"
#include "../../pruebas_carlos_cppunit/hex_coder/v04/hexdecoder.hpp"
#include "../../pruebas_carlos_cppunit/hex_coder/v04/OddDigitException.hpp"


using namespace ppmc;
using namespace std;
using namespace util;

CPPUNIT_TEST_SUITE_REGISTRATION( CompressorTest );

baseType CompressorTest::delta =0.0000000000001;

void CompressorTest::setUp(){
	
}


void CompressorTest::tearDown(){
}                               


void CompressorTest::testConstructor(){

}

/**
 * empty frequency table
 */
void CompressorTest::testCalculateCeiling_0_1_1(){
	Probability p;
	p.skip = 0;
	p.width = 1;
	p.total = 1;
	Compressor *c = new Compressor(0);
	baseType ceiling = c->ceiling;
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
	delete(c);
}

/**
 * empty frequency table
 */
void CompressorTest::testCalculateFloor_0_1_1(){
	Probability p;
	p.skip = 0;
	p.width = 1;
	p.total = 1;
	Compressor *c = new Compressor(0);
	baseType floor = c->floor;
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor, c->floor);
	delete(c);
}

/**
 * a hit with only a char with frequency 1
 */
void CompressorTest::testCalculateCeiling_0_1_2(){
	Probability p;
	p.skip = 0;
	p.width = 1;
	p.total = 2;
	Compressor *c = new Compressor(0);
	baseType ceiling = c->ceiling;
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
	delete(c);
}

/**
 * a hit with only a char with frequency 1
 */
void CompressorTest::testCalculateFloor_0_1_2(){
	Probability p;
	p.skip = 0;
	p.width = 1;
	p.total = 2;
	Compressor *c = new Compressor(0);
	baseType floor = c->floor + (c->ceiling / 2) ;
	if (sizeof (baseType) == 8) {
		floor += 1;
	}
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor, c->floor);
	delete(c);
}

/**
 * a miss with only a char with frequency 1
 */
void CompressorTest::testCalculateCeiling_1_1_2(){
	Probability p;
	p.skip = 1;
	p.width = 1;
	p.total = 2;
	Compressor *c = new Compressor(0);
	baseType ceiling = (c->ceiling / (baseType) 2);
	if (sizeof(baseType)==4) {
		ceiling += 1;
	}
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
	delete(c);
}

/**
 * a miss with only a char with frequency 1
 */
void CompressorTest::testCalculateFloor_1_1_2(){
	Probability p;
	p.skip = 1;
	p.width = 1;
	p.total = 2;
	Compressor *c = new Compressor(0);
	baseType floor = c->floor;
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor, c->floor);
	delete(c);
}

void CompressorTest::testCalculateFloor(){
	Probability p;
	p.skip = 250;
	p.width = 1;
	p.total = 256;
	Compressor *c = new Compressor(0);
	
	c->calculate(p);
	baseType floor = 0;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor, c->floor);

	delete(c);
}

/**
 * a miss with only a char with frequency 1
 */
void CompressorTest::testCalculateCeiling(){
	Probability p;
	p.skip = 2;
	p.width = 1;
	p.total = 3;
	Compressor *c = new Compressor(0);
	
	baseType ceiling = (c->ceiling / (baseType) 4) ;
	c->calculate(p);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
	delete(c);
}


void CompressorTest::testCalculate_c() {
	Probability p;
	p.skip = 99;
	p.width = 1;
	p.total = 257;
	Compressor *c = new Compressor(0);

	c->calculate(p);

	baseType ceiling = 2640485730;
	baseType floor = 2623773795;

	if (sizeof(baseType) == 8 ) {
		ceiling = 11340799858545171455U;
		floor   = 11269022644250582272U;
	}
	
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor, c->floor);

	delete(c);
}
void CompressorTest::testCompressFirstChars(){
	
	
	
}

// void CompressorTest::testCompressWithM_1(){
// 	Probability p1,p2;
// 	p1.skip = 99;
// 	p1.width = 1;
// 	p1.total = 257;
// 	Compressor *c = new Compressor(0);
// 	ContextSelector cs(0);
// 
// 	baseType ceiling = 2640485730;
// 	baseType floor = 2623773795;
// 
// 	if (sizeof(baseType) == 8 ) {
// 		ceiling = 11340799858545171455U;
// 		floor   = 11269022644250582272U;
// 	}
// 	
// 	c->compressWithM_1(cs, 'c');
// 	p2 =c->q.getProbability();
// 	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad skip", p1.skip,p2.skip);
// 	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad width", p1.width,p2.width);
// 	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad total", p1.total,p2.total);
// 	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
//  	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor,c->floor);
// 
// 	delete(c);
// }

void CompressorTest::testCompressWithModels_0(){
	Probability p1,p2;
	p1.skip = 99;
	p1.width = 1;
	p1.total = 257;
	Compressor *c = new Compressor(0);
	ContextSelector cs(0);
	baseType ceiling = 0;
	baseType floor = 0;

	if (sizeof(baseType) == 8 ) {
		ceiling = 11340799858545171455U;
		floor   = 11269022644250582272U;
	}

	MockedFileReader* in = new MockedFileReader("c");

	c->compressWithModels(cs);
	p2 =c->q.getProbability();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad skip", p1.skip,p2.skip);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad width", p1.width,p2.width);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad total", p1.total,p2.total);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad ceiling", ceiling, c->ceiling);
 	CPPUNIT_ASSERT_EQUAL_MESSAGE("bad floor", floor,c->floor);
	
	delete(in);
	delete(c);
}

void CompressorTest::testCompressWithModels_1(){
	
}

void CompressorTest::testCompressWithModels_2(){
	
}

void CompressorTest::testCompressEof_M_1(){
	
}

void CompressorTest::testCompressEof_M0(){
	
}

void CompressorTest::testCompressEof_M1(){
	
}

void CompressorTest::testCompressEof(){
	
}
// c2b416b8d3000000

void CompressorTest::testCompress(){
	string reference="c2b416b8d3000000";
	MockedFileReader* in = new MockedFileReader("ABDABABABD");
	MockedFileWriter* out = new MockedFileWriter();
	MockedFileWriter* out2 = new MockedFileWriter();
	out2->write("hola");
	Compressor *c = new Compressor(0);
	c->compress(in, out);
	
	HexDecoder hd;
	string buffer = out->get();
	hd.decode(buffer);
	cout << "contents: " << out2->get()  << endl;
	cout << "hd size: " << hd.getSize() << endl;
	CPPUNIT_ASSERT_EQUAL(reference, hd.getAsString());

	delete in;
	delete out;
	delete c;
}
