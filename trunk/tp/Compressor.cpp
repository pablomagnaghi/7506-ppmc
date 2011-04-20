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
// 		for(int i=order; i>0; i--) {
// 			
// 		}
 	}

}