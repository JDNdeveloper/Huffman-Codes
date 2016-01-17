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

   /*
   for (unsigned int i = 0; i < 256; i++) {
      if (char_map[i] != "")
         std::cout << (unsigned char) i << ": "
                   << char_map[i] << std::endl;
   }
   */
   
   
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
   // Save room for the last valid bits info.
   // This will say what bits are non-junk
   // from the last byte of the file.
   enc_buffer.push_back(0);

   build_enc_map();
   build_enc_rep();
   
   //std::cout << Count.count << std::endl;
   /*
   for (unsigned char c : enc_buffer) {
      std::cout << (unsigned int) c << std::endl;
   }
   */
}

void Huffman::build_enc_map() {
   for (unsigned int i = 0; i < 256; i++) {
      //char is implied by ordering from 0 to 255
      //of the mapping, no need to waste a byte
      //to include this
      
      std::string bitstring_rep = char_map[i];
      //says how many bits are valid of following
      //bytestream that stores the bitstring rep
      enc_buffer.push_back(bitstring_rep.length());

      std::string bitstring = "";
      unsigned int count_eight = 0;
      for (unsigned char bit : bitstring_rep) {
         bitstring += bit;
         count_eight++;
         if (count_eight == 8) {
            enc_buffer.
               push_back(bitstring_to_char(bitstring));
            bitstring = "";
            count_eight = 0;
         }
      }
      
      //pushes last byte of bistring rep onto file
      if (count_eight != 0) {
         enc_buffer.push_back(bitstring_to_char(bitstring));
      }      
   }
}

void Huffman::build_enc_rep() {
   unsigned int count_eight = 0;
   std::string bitstring = "";
   for (unsigned char c : dec_buffer) {
      std::string bitstring_rep = char_map[c];
      for (unsigned char bit : bitstring_rep) {
         //enc_buffer.push_back(d);
         bitstring += bit;
         count_eight++;
         if (count_eight == 8) {
            enc_buffer.
               push_back(bitstring_to_char(bitstring));
            bitstring = "";
            count_eight = 0;
         }
      }
   }

   //pushes last byte onto file, and saves how many
   //bits of that last byte are valid into the first
   //byte of the file.
   if (count_eight != 0) {
      enc_buffer.push_back(bitstring_to_char(bitstring));
      enc_buffer[0] = count_eight;
   } else {
      // if none leftover, all 8 bits of last byte are
      // valid.
      enc_buffer[0] = 8;
   }
   /*
   std::cout << "1: "
             << (unsigned int)
      bitstring_to_char("00100100")
             << std::endl;
   */
}

unsigned char Huffman::bitstring_to_char(std::string s) {
   while (s.length() < 8) {
      s += '0';
   }
   unsigned char c = 0;
   for (unsigned int i = 0; i < 8; i++) {
      if (s[7 - i] - '0' == 1) {
         c |= 1 << i;
      }
   }
   return c;
}

void Huffman::huffman_decode() {
   auto iter = enc_buffer.begin();
   unsigned int last_byte_valid = *iter;
   iter++;

   build_dec_map(iter);
   build_dec_buffer(iter, last_byte_valid);
}

void Huffman::build_dec_map(char_vect::iterator &iter) {
   for (unsigned int i = 0; i < 256; i++) {
      unsigned int valid_bits = *iter;
      iter++;
      std::string bitstring_rep = "";
      unsigned int bit_count = 0;
      while (bit_count < valid_bits) {
         unsigned char data = *iter;
         std::string byte = char_to_bitstring(data);
         for (unsigned char c : byte) {
            if (bit_count < valid_bits) {
               bitstring_rep += c;
               bit_count++;
            }
         }
         iter++;
      }
      stc_entry entry(bitstring_rep, i);
      bits_map.insert(entry);
   }
}

void Huffman::build_dec_buffer(char_vect::iterator &iter,
                               unsigned int
                               last_byte_valid) {
   //std::cout << " : "
   //          << char_to_bitstring(' ') << std::endl;

   std::string bits_partial = "";
   for (; iter != enc_buffer.end(); iter++) {
      std::string bitstring = char_to_bitstring(*iter);
      // default process all 8 bits of the byte
      unsigned int bits_to_process = 8;
      // if this is the last byte, only process the
      // valid bits (num stored in first byte of file)
      if (iter + 1 == enc_buffer.end())
         bits_to_process = last_byte_valid;
      for (unsigned int i = 0; i < bits_to_process;
           i++) {
         bits_partial += bitstring[i];
         auto match = bits_map.find(bits_partial);
         if (match != bits_map.end()) {
            dec_buffer.push_back(bits_map[bits_partial]);
            bits_partial = "";
         }
      }
   }
}

std::string Huffman::char_to_bitstring(unsigned char c) {
   std::string s = "XXXXXXXX";
   for (unsigned int i = 0; i < 8; i++) {
      if ((c & (1 << i)) == 0) {
         s[7 - i] = '0';
      } else {
         s[7 - i] = '1';
      }
   }
   return s;
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
