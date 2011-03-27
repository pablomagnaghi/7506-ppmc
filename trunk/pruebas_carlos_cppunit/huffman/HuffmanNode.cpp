#include "HuffmanNode.hpp"

using namespace huffman;

Node::Node() {
  value = 0x00;
  parent = empty;
  zero = empty;
  one = empty;
  count = 0;
}

Node::Node(unsigned char value):value(value) {
  parent = empty;
  zero = empty;
  one = empty;
  count = 0;
}