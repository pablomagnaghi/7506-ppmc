#include "AI.h"

using namespace util;
using namespace std;
using namespace util;

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
	
	
	ext.insert(make_pair("exe",-1));
	ext.insert(make_pair("pdf",-1));
	ext.insert(make_pair("z",-1));
	ext.insert(make_pair("zip",-1));
	ext.insert(make_pair("rar",-1));
	ext.insert(make_pair("XX",-1));
	ext.insert(make_pair("gz",-1));
	ext.insert(make_pair("mp3",-1));
	ext.insert(make_pair("wav",-1));
	ext.insert(make_pair("rpm",-1));
	ext.insert(make_pair("deb",-1));
	ext.insert(make_pair("tar",-1));
	ext.insert(make_pair("odt",-1));
	ext.insert(make_pair("ods",-1));
	ext.insert(make_pair("png",-1));
	ext.insert(make_pair("doc",-1));
	ext.insert(make_pair("docx",-1));
	ext.insert(make_pair("xls",-1));
	ext.insert(make_pair("xlsx",-1));
	//ext.insert(make_pair("",-1));
	
	



}

size_t AI::evaluate(){
	// is known
	if(name.find_last_of(".") != string::npos) {
		map<string, int>::iterator it;
		it = ext.find(name.substr(name.find_last_of(".")+1));
		if (it != ext.end()) {
			return it->second;
		}
	}

	// is binary
	if (file.getChars() > 128 ) {
		return -1;
	}

	// is text
	size_t fileSize = file.getSize();
	if (fileSize < 50 * 1048576) {
		return 7;
	}
	if (fileSize < 100 * 1048576) {
		return 6;
	}
	if (fileSize < 250 * 1048576) {
		return 5;
	}
	if (fileSize < 500 * 1048576) {
		return 4;
	}
	if (fileSize < 1000 * 1048576) {
		return 3;
	}
	return 2;
}
