#include <iostream>
#include <fstream>

#include "HuffmanTree.hpp"

using namespace std;

int main(int argc, char* argv[]) {

  ifstream infile ("message.txt");
  if ( ! infile.is_open() ) {
    throw 1; 
  }

  ofstream outfile ("compressed.txt", ios_base::out|ios_base::trunc|ios_base::binary);
  if ( ! outfile.is_open() ) {
    throw 1;
  }

  huffman::Tree tree;
  std::string freq = tree.showFreq(true);
  // cout << freq;
  
  tree.read(infile);

  // some monitoring
  // cout << "buffer size: " << huffman::buffer_size << endl;
  // cout << "total: " << tree.getTotal() << endl;
  // freq = tree.showFreq(true);
  // cout << freq;
  
  tree.build();
  freq = tree.showFreq(false);
  //cout << freq;
  //tree.save(outfile);
  
  
  outfile.close();
  infile.close();

}