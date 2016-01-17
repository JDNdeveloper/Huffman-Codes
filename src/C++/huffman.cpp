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
   char_map = new std::string[256];
}

void Huffman::encode() {
   //std::cout << "Encoding " << dec_file_name << std::endl;
   //std::cout << "Resulting encoded file will be located in "
   //          << enc_file_name << std::endl;

   read_in(dec_file_name, dec_buffer);
   huffman_encode();
   print_out(enc_file_name, enc_buffer);
}

void Huffman::decode() {
   //std::cout << "Decoding " << enc_file_name << std::endl;
   //std::cout << "Resulting decoded file will be located in "
   //          << dec_file_name << std::endl;
   
   read_in(enc_file_name, enc_buffer);
   huffman_decode();
   print_out(dec_file_name, dec_buffer);
}

void Huffman::huffman_encode() {
   calc_freq();
   build_tree();
   build_map();
   build_enc_buffer();
}

void Huffman::calc_freq() {
   for (int i = 0; i < 256; i++) {
      freq_map[i] = 0;
   }
   for (unsigned char c : dec_buffer) {
      //std::cout << c << " ";
      freq_map[c]++;
   }
   /*
   for (int i = 0; i < 256; i++) {
      std::cout << i << ": " << freq_map[i]
                << std::endl;
   }
   */  
}

void Huffman::build_tree() {
   for (unsigned int c = 0; c < 256; c++) {
      int freq = freq_map[c];
      if (freq > 0) {
         Node* n = new Node();
         n->chars.push_back((char) c);
         n->freq = freq;
         tree.push(n);
      }
   }
   
   while (tree.size() > 1) {
      Node* a = tree.top(); tree.pop();
      Node* b = tree.top(); tree.pop();
      Node* a_b = new Node();
      a_b->chars.insert(a_b->chars.end(),
                        a->chars.begin(),
                        a->chars.end());
      a_b->chars.insert(a_b->chars.end(),
                        b->chars.begin(),
                        b->chars.end());
      a_b->freq = a->freq + b->freq;
      a_b->right = a;
      a_b->left = b;
      tree.push(a_b);
   }
   
   /*
   while (tree.size() > 0) {
      Node* n = tree.top(); tree.pop();
      std::cout << n->freq << ", "
                << n->chars[0] << std::endl;
   }
   */
}

void Huffman::build_map() {
   if (tree.size() != 1) return;
   for (unsigned int i = 0; i < 256; i++) {
      char_map[i] = "";
   }
   build_map_recursive(tree.top());
   
   for (unsigned int i = 0; i < 256; i++) {
      if (char_map[i] != "")
         std::cout << (unsigned char) i << ": "
                   << char_map[i] << std::endl;
   }
   
}

void Huffman::build_map_recursive(Node *n) {
   if (n->left == NULL || n->right == NULL)
      return;
   for (unsigned char c : n->left->chars) {
      char_map[c] += "0";
   }
   build_map_recursive(n->left);
   for (unsigned char c : n->right->chars) {
      char_map[c] += "1";
   }
   build_map_recursive(n->right);
}

void Huffman::build_enc_buffer() {
   union {
      unsigned long long count;
      unsigned char bytes[8];
   } Count;
   Count.count = 0;
   //save 64 bits for the bit count
   for (unsigned int i = 0; i < 8; i++) {
      enc_buffer.push_back(0);
   }
   for (unsigned char c : dec_buffer) {
      for (unsigned char d : char_map[c]) {
         //enc_buffer.push_back(d);
         Count.count++;
      }
   }
   //put in the bit count
   for (unsigned int i = 0; i < 8; i++) {
      enc_buffer[i] = Count.bytes[7-i];
   }
   std::cout << Count.count << std::endl;
   /*
   for (unsigned char c : enc_buffer) {
      std::cout << (unsigned int) c << std::endl;
   }
   */
}

void Huffman::huffman_decode() {
   dec_buffer = enc_buffer; //REMOVE

   
}

void Huffman::read_in(std::string in_file_name,
                     char_vect &in_buffer) {
   std::ifstream input(in_file_name, std::ios::binary);
   char_vect
      buffer((std::istreambuf_iterator<char>(input)),
             (std::istreambuf_iterator<char>()));
   in_buffer = buffer;
   if (in_buffer.size() < 1) {
      std::cerr << "Error: File does not exist "
         "or is empty" << std::endl;
      exit(1);
   }
}

void Huffman::print_out(std::string out_file_name,
                       char_vect &out_buffer) {
   std::ofstream output(out_file_name, std::ios::binary);
   std::copy(out_buffer.begin(), out_buffer.end(),
             std::ostreambuf_iterator<char>(output));
}
