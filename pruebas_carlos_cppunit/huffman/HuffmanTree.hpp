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
    int getTotalRead();
    void build();
    void buildMap();
    void save(std::ostream& outfile);
    void load(std::istream& infile);
    unsigned int skipZero(unsigned int start=0, unsigned int stop=dictionary_size);

    // candidates to helper friend class
    std::string showFreq(bool omit_zero);
    std::string showTree(bool omit_zero);
    
    private:
    void sort(unsigned int start=0, unsigned int stop=dictionary_size);
    void semiSort(unsigned int start=0, unsigned int stop=dictionary_size);
    unsigned int getFirstNotZero();
    
    char buffer[buffer_size];
    int total_read;
    unsigned int first_not_zero;
    Node freq[dictionary_size];
    Node tree[dictionary_size];
    
    friend class HuffmanTreeTest;
  };
}
#endif // _huffman_tree_hpp_