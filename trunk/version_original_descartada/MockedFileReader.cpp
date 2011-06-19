#include "MockedFileReader.h"


using namespace util;
using namespace std;

MockedFileReader::MockedFileReader():IFileReader() {

}

MockedFileReader::~MockedFileReader(){

}

MockedFileReader::MockedFileReader(const std::string& dd){
	data = dd;
	iter = data.begin();
}

bool MockedFileReader::eof() {
	return iter == data.end();
}
char MockedFileReader::read(){
	if (eof()) throw 1;
	char r = *iter;
	iter++;
	return r;
}