#include "Huffman.hpp"

namespace huffman {

  class Node {
    public:
    Node();      
    Node(char value);
    unsigned int parent;
    unsigned int zero;
    unsigned int one;
    unsigned int count;
    char value;
  };

}