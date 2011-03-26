#include <sstream>

#include "HuffmanTree.hpp"


using namespace huffman;

Tree::Tree():total(0){
  for (unsigned int i=0; i < dictionary_size; i++) {
    freq[i]=0;
  }
}

void Tree::read(std::istream& infile) {
  // build tree
  while ( infile.good() and ! infile.eof() ) {
    infile.read(buffer,huffman::buffer_size);
    for(int i=0; i<infile.gcount(); i++) {
      freq[ (unsigned char) buffer[i] ]++;  
      total++;
    }
  }
}

std::string Tree::getFreq(bool omit_zero) {
  std::stringstream result;
  for (unsigned int i=0; i< dictionary_size ; i++ ) {
    if (! omit_zero || freq[i] != 0 ) {
      result << i << ":" << freq[i] << ","; 
    }
  }
  return result.str().substr(0,result.str().size()-1);
}

int Tree::getTotal() {
  return total;
}
    
void Tree::build() {
  // use a double size freq
  // use nodes instead of chars
  // sort the nodes
  //   take two and move to nodes
  //   create a new one pointing to them 
  //   bubble it up to its sorted position
  //   repeat until there is only one node
   
}

void Tree::buildMap() {
   build();
   // copy nodes to a new array composed of position=>(bits,length)
}

void Tree::save(std::ostream& outfile) {

}