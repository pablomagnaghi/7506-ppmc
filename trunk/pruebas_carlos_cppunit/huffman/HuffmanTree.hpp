#ifndef _huffman_tree_hpp_
#define _huffman_tree_hpp_

#include <fstream>
#include <string>
#include "Huffman.hpp"


namespace huffman {
  class Tree {
    public:
    Tree();
    void read(std::istream& infile);
    std::string getFreq(bool omit_zero);
    int getTotal();
    void build();
    void buildMap();
    void save(std::ostream& outfile);
    private:
    char buffer[huffman::buffer_size];
    int total;
    unsigned int freq[huffman::dictionary_size]; 
  };
}
#endif // _huffman_tree_hpp_