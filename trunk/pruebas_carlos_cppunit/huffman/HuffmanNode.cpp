#include <sstream>
#include <iomanip>

#include "HuffmanNode.hpp"

using namespace huffman;

Node::Node() {
  clear();
}


Node::Node(unsigned char value):value(value) {
  parent = empty;
  zero   = empty;
  one    = empty;
  count  = 0;
}

void Node::clear() {
  value  = 0x00;
  parent = empty;
  zero   = empty;
  one    = empty;
  count  = 0;
}

std::string Node::showMin(bool omit_zero){
  std::stringstream result;
  if (! omit_zero || count != 0 ) {
      result << (int) value << ":" << count << ","; 
  }
  return result.str();
}
  
std::string Node::showMax(unsigned int i, bool omit_zero){
  std::stringstream result;

  if (! omit_zero || count != 0 ) {
    result << "@:" << std::setfill('0') << std::setw(3) << i << " $:" ;
    if (value >31) {
      result << value ;
    } else {
      result << "_";
    }
    result <<"(" << std::hex << std::setfill('0') << std::setw(2) << (int) value << std::dec  << ")" << " #:" << count;
    if (zero != empty) {
      result << "[" << zero << "]";
    }
    if (one != empty) {
      result << "[" << one << "]";
    }
    if (parent != empty) {
      result << "<" << parent << ">";
    }
    result << std::endl;  
  }
  return result.str();
}