#include "Compressor.h"


using namespace ppmc;
using namespace std;

Compressor::Compressor():Arithmetic(){

}

Compressor::~Compressor(){


}

void Compressor::compress(util::IFileReader* reader, util::IFileWriter* writer){
 	while (!reader->eof()) {
		char c = reader->read();
		writer->write(c);
// 		for(int i=order; i>0; i--) {
// 			
// 		}
 	}

}