#include "AI.h"

using namespace util;
using namespace std;
using namespace util;

size_t AI::binaryMinSize=1048576;

AI::AI(FileReader& in, const std::string n):file(in),name(n){
	
	/*
	gif
	tif
	jpeg
	jpg
	*/
	
	ext.insert(make_pair("txt",5));
	ext.insert(make_pair("c",5));
	ext.insert(make_pair("h",5));
	ext.insert(make_pair("cpp",5));
	ext.insert(make_pair("bat",5));
	ext.insert(make_pair("sh",5));
	ext.insert(make_pair("xml",5));
	ext.insert(make_pair("svg",5));
	//ext.insert(make_pair("",5));
	
	
	ext.insert(make_pair("exe",+1));
	ext.insert(make_pair("pdf",+1));
	ext.insert(make_pair("z",+1));
	ext.insert(make_pair("XX",+1));
	ext.insert(make_pair("gz",+1));
	ext.insert(make_pair("mp3",+1));
	ext.insert(make_pair("wav",+1));
	ext.insert(make_pair("rpm",+1));
	ext.insert(make_pair("deb",+1));
	ext.insert(make_pair("tar",+1));
	ext.insert(make_pair("odt",+1));
	ext.insert(make_pair("ods",+1));
	ext.insert(make_pair("png",+1));
	ext.insert(make_pair("doc",+1));
	ext.insert(make_pair("docx",+1));
	ext.insert(make_pair("xls",+1));
	ext.insert(make_pair("xlsx",+1));
	//ext.insert(make_pair("",+1));
	
	



}

size_t AI::evaluate(){
	
	if(name.find_last_of(".") != string::npos) {
		map<string, int>::iterator it;
// 		string extension = "";
// 		extension = name.substr(name.find_last_of(".")+1);
		
		it = ext.find(name.substr(name.find_last_of(".")+1));
		if (it != ext.end()) {
			return it->second;
		}
	}
	
	
	size_t fileSize = file.getSize();
	if (fileSize < binaryMinSize) {
		return 5;
	}
	size_t chars = file.getChars();
	if (chars > 60 ) {
		return 3;
	}
	return 5;
}