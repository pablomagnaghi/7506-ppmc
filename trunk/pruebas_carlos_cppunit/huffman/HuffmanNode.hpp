#include <string>
#include "Huffman.hpp"

namespace huffman {

  class Node {
    public:
    Node();      
    Node(unsigned char value);
    unsigned int parent;
    unsigned int zero;
    unsigned int one;
    unsigned int count;
    unsigned char value;
    void clear();
//    std::string showMin(bool omit_zero);
    std::string show(unsigned int i, bool omit_zero, bool show_children, bool show_parent);
    
    friend class HuffmanNodeTest;
  };

}