// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using char_vect = std::vector<unsigned char>;

// Used to represent a Huffman node. Stores a
// vector of characters along with their frequency.
class Node {
   friend class Huffman;
 public:
   bool operator<(Node other) const {
      return freq < other.freq; }
   bool operator>(Node other) const {
      return freq > other.freq; }
 private:
   Node* left;
   Node* right;
   char_vect chars;
   int freq;
};

// Provides comparison operators between two nodes.
class CompareNodes {
 public:
   bool operator()(const Node* a, const Node* b) {
      return *a > *b;
   }
};

using node_heap = std::priority_queue<Node*,
   std::vector<Node*>, CompareNodes>;

using stc_map = std::unordered_map<std::string,
   unsigned char>;
using stc_entry = stc_map::value_type;

class Huffman {
 private:
   std::string enc_file_name;
   std::string dec_file_name;
   char_vect enc_buffer;
   char_vect dec_buffer;
   int freq_map[256];
   node_heap tree;
   std::string* char_map;
   stc_map bits_map;
   
   void read_in(std::string, char_vect&);
   void print_out(std::string, char_vect&);
   
   void huffman_encode();
   void calc_freq();
   void build_tree();
   void build_map();
   void build_map_recursive(Node*);
   void build_enc_buffer();
   void build_enc_map();
   void build_enc_rep();
   unsigned char bitstring_to_char(std::string);

   void huffman_decode();
   void build_dec_map(char_vect::iterator&);
   void build_dec_buffer(char_vect::iterator&, unsigned int);
   std::string char_to_bitstring(unsigned char);
 public:
   Huffman(std::string, std::string);
   void encode();
   void decode();
};

#endif
