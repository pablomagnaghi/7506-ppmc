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
    
    friend class HuffmanNodeTest;
  };

}