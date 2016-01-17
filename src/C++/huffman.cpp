// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
#include <iostream>
#include <fstream>
#include <iterator>

#include "huffman.h"

Huffman::Huffman(std::string enc_name,
                 std::string dec_name) {
   enc_file_name = enc_name;
   dec_file_name = dec_name;
}

void Huffman::encode() {
   std::cout << "Encoding " << dec_file_name << std::endl;
   std::cout << "Resulting encoded file will be located in "
             << enc_file_name << std::endl;

   readIn(dec_file_name, dec_buffer);
   huffman_encode();
   printOut(enc_file_name, enc_buffer);
}

void Huffman::decode() {
   std::cout << "Decoding " << enc_file_name << std::endl;
   std::cout << "Resulting decoded file will be located in "
             << dec_file_name << std::endl;
   
   readIn(enc_file_name, enc_buffer);
   huffman_decode();
   printOut(dec_file_name, dec_buffer);
}

void Huffman::huffman_encode() {
   enc_buffer = dec_buffer; //REMOVE   
}

void Huffman::huffman_decode() {
   dec_buffer = enc_buffer; //REMOVE
}

void Huffman::readIn(std::string in_file_name,
                     char_vect &in_buffer) {
   std::ifstream input(in_file_name, std::ios::binary);
   char_vect
      buffer((std::istreambuf_iterator<char>(input)),
             (std::istreambuf_iterator<char>()));
   in_buffer = buffer;
}

void Huffman::printOut(std::string out_file_name,
                       char_vect &out_buffer) {
   std::ofstream output(out_file_name, std::ios::binary);
   std::copy(out_buffer.begin(), out_buffer.end(),
             std::ostreambuf_iterator<char>(output));
}
