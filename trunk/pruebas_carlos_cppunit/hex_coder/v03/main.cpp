#include "hexdecoder.hpp"
#include "hexencoder.hpp"

#include <cstring>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  string cmd(argv[1]);
  if (! cmd.compare("decode")) {
    string input(argv[2]);
    HexDecoder hd;
    hd.decode(input);
    cout.write(hd.getCharBufferPtr(), hd.getSize());
    return 0;
  } else if (! cmd.compare("encode_stream")) {
    HexEncoder he;
    ifstream input(argv[2], ifstream::in | ifstream::binary);
    cout << he.encode(input);
    input.close();
    return 0;
  } else if (! cmd.compare("encode_cin")) {
    HexEncoder he;
    cout << he.encode(cin);
    return 0;
  } else if (! cmd.compare("encode_buffer")) {
    HexEncoder he;
    cout << he.encode(argv[2],strlen(argv[2]));
    return 0;
  } else {
    cerr << "Unrecognized command" << endl;
    return 1;
  }
  
  
}

