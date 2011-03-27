#include <sstream>


#include "HuffmanTree.hpp"

#include <iostream>
using namespace std;

using namespace huffman;

Tree::Tree():total_read(0),first_not_zero(0){
  
  for (unsigned int i=0; i < dictionary_size; i++) {
    freq[i].value=i;
  }
}

Tree::~Tree() {
//   for (unsigned int i=0; i < dictionary_size; i++) {
//     delete freq[i];
//   } 
}

void Tree::read(std::istream& infile) {
  while ( infile.good() and ! infile.eof() ) {
    infile.read(buffer,buffer_size);
    for(int i=0; i<infile.gcount(); i++) {
      freq[ (unsigned char) buffer[i] ].count++;  
      total_read++;
    }
  }
}

std::string Tree::showFreq(bool omit_zero) {
  std::stringstream result;
  for (unsigned int i=0; i< dictionary_size ; i++ ) {
    if (! omit_zero || freq[i].count != 0 ) {
      result << (int) freq[i].value << ":" << freq[i].count << ","; 
    }
  }
  return result.str().substr(0,result.str().size()-1);
}

std::string Tree::showTree(bool omit_zero) {
  std::stringstream result;
  for (unsigned int i=0; i< dictionary_size ; i++ ) {
    if (! omit_zero || tree[i].count != 0 ) {
      result << i << ":" << tree[i].count << ","; 
    }
  }
  return result.str().substr(0,result.str().size()-1);
}
unsigned int Tree::getFirstNotZero() {
  return first_not_zero;
}

int Tree::getTotalRead() {
  return total_read;
}
    
void Tree::sort(unsigned int start, unsigned int stop) {
  Node tmp;
  for (unsigned int i=start; i < stop -1 ; i++) {
    for (unsigned int j=i; j < stop; j++) {
      if(freq[i].count > freq[j].count) {
         tmp = freq[i];
         freq[i] = freq[j];
         freq[j] = tmp;
      }
    }
  }  
}

unsigned int Tree::skipZero(unsigned int start, unsigned int stop) {
  for (unsigned int i=start; i<=stop; i++) {
    if (freq[i].count != 0) {
      first_not_zero = i;
      return first_not_zero;
    }
  }
  //while ( freq[start].count == 0 && start <= stop) start++;
  first_not_zero = empty;
  return first_not_zero;
}

void Tree::build() {
//  unsigned int start=0;
//  unsigned int stop=dictionary_size;
  unsigned int node_count=0;
  
  while( first_not_zero < dictionary_size ) {
//    cout << " nc: " << node_count << " fnz: " << first_not_zero << endl;
//    cout << showFreq(true);
    sort(first_not_zero,dictionary_size); 
    
    skipZero(first_not_zero);  
    
    tree[node_count]=freq[first_not_zero];
    node_count++;
    
    tree[node_count]=freq[first_not_zero + 1];
    node_count++;
    
    freq[first_not_zero + 1].count += freq[first_not_zero].count;
    freq[first_not_zero + 1].zero = node_count - 2;
    freq[first_not_zero + 1].one  = node_count - 1;
    
    freq[first_not_zero].count = 0;

    //sortFirst();
  }  
  
  // buildParentage();
}

void Tree::buildMap() {
   build();
   // copy nodes to a new array composed of position=>(bits,length)
}

void Tree::save(std::ostream& outfile) {

}

void Tree::load(std::istream& infile) {
  
}