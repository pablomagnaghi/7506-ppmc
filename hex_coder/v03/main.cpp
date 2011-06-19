#include "hexdecoder.hpp"
#include "hexencoder.hpp"

#include <cstring>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  string cmd(argv[1]);
  if (! cmd.compare("decode")) {
    // We can use argv because the input is in 0-9a-fA-F range
    string input(argv[2]);
    HexDecoder hd;
    hd.decode(input);
    cout.write(hd.getCharBufferPtr(), hd.getSize());
    return 0;
  } else if (! cmd.compare("decode_as_string")) {
    // Now it uses an string as result
    string input(argv[2]);
    HexDecoder hd;
    hd.decode(input);
    cout << hd.getAsString();
    return 0;
  } else if (! cmd.compare("encode_stream")) {
    // We can open a file and feed it to the HexEncoder
    // From this case, the output is in 0-9a-fA-F range
    HexEncoder he;
    ifstream input(argv[2], ifstream::in | ifstream::binary);
    cout << he.encode(input);
    input.close();
    return 0;
  } else if (! cmd.compare("encode_cin")) {
    // We can use cin as an input string
    HexEncoder he;
    cout << he.encode(cin);
    return 0;
  } else if (! cmd.compare("encode_buffer")) {
    // Using argv, we can only feed printable ascii codes
    HexEncoder he;
    cout << he.encode(argv[2],strlen(argv[2]));
    return 0;
  } else if (! cmd.compare("encode_fixed_buffer")) {    
    HexEncoder he;
    char buffer[8];
    buffer[0]=0;
    buffer[1]=1;
    buffer[2]=2;
    buffer[3]=3;
    buffer[4]=4;
    buffer[5]=5;
    buffer[6]=6;
    buffer[7]=7;
    
    cout << he.encode(buffer, 8);
    
    return 1;
  } else {
    cerr << "Unrecognized command" << endl;
    return 1;
  }
  
}

