// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string>
#include <vector>

using char_vect = std::vector<char>;

class Huffman {
 private:
   std::string enc_file_name;
   std::string dec_file_name;
   std::vector<char> enc_buffer;
   std::vector<char> dec_buffer;
   
   void readIn(std::string, char_vect&);
   void printOut(std::string, char_vect&);
   void huffman_encode();
   void huffman_decode();
 public:
   Huffman(std::string, std::string);
   void encode();
   void decode();
};

#endif
