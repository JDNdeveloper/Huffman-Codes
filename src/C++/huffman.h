// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string>
#include <vector>
#include <queue>

using char_vect = std::vector<unsigned char>;

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

class CompareNodes {
 public:
   bool operator()(const Node* a, const Node* b) {
      return *a > *b;
   }
};

using node_heap = std::priority_queue<Node*,
   std::vector<Node*>, CompareNodes>;

class Huffman {
 private:
   std::string enc_file_name;
   std::string dec_file_name;
   char_vect enc_buffer;
   char_vect dec_buffer;
   int freq_map[256];
   node_heap tree;
   std::string* char_map;
   
   void read_in(std::string, char_vect&);
   void print_out(std::string, char_vect&);
   
   void huffman_encode();
   void calc_freq();
   void build_tree();
   void build_map();
   void build_map_recursive(Node*);
   void build_enc_buffer();

   void huffman_decode();
 public:
   Huffman(std::string, std::string);
   void encode();
   void decode();
};

#endif
