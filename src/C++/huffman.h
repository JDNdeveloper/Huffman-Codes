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

   // Reads in from a file
   void read_in(std::string, char_vect&);
   // Prints out to a file
   void print_out(std::string, char_vect&);

   // Encodes the dec_buffer
   void huffman_encode();
   // Calculates the character frequency of the buffer
   void calc_freq();
   // Builds the Huffman Tree
   void build_tree();
   // Builds the character to bit string map
   void build_map();
   // Buils the map recursively given a node
   void build_map_recursive(Node*);
   // Builds the enc_buffer
   void build_enc_buffer();
   // Builds the encoding map
   void build_enc_map();
   // Builds the encoding representation
   void build_enc_rep();
   // Converts a bitstring to the proper character for
   // output to the file
   unsigned char bitstring_to_char(std::string);

   // Decodes the enc_buffer
   void huffman_decode();
   // Builds the decode map
   void build_dec_map(char_vect::iterator&);
   // Builds the decode buffer
   void build_dec_buffer(char_vect::iterator&, unsigned int);
   // Converts a character to the bit string representation
   std::string char_to_bitstring(unsigned char);
 public:
   // Constructor, which takes in the input filename and the
   // output filename
   Huffman(std::string, std::string);
   // Runs the encode process
   void encode();
   // Runs the decode process
   void decode();
};

#endif
