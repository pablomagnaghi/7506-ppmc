#ifndef _huffman_tree_hpp_
#define _huffman_tree_hpp_

#include <fstream>
#include <string>
#include "Huffman.hpp"
#include "HuffmanNode.hpp"

namespace huffman {
  class Tree {
    public:
    Tree();
    ~Tree();
    void read(std::istream& infile);
    std::string showFreq(bool omit_zero);
    std::string showTree(bool omit_zero);
    int getTotalRead();
    unsigned int getFirstNotZero();
    void build();
    void buildMap();
    void save(std::ostream& outfile);
    void load(std::istream& infile);
    void sort(unsigned int start=0, unsigned int stop=dictionary_size);
    unsigned int skipZero(unsigned int start=0, unsigned int stop=dictionary_size);
    private:
    char buffer[buffer_size];
    int total_read;
    unsigned int first_not_zero;
    Node freq[dictionary_size];
    Node tree[dictionary_size];
  };
}
#endif // _huffman_tree_hpp_