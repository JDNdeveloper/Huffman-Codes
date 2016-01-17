// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "huffman.h"

bool opt_encode = false;
bool opt_decode = false;

std::string enc_ext = ".h_enc";
std::string dec_ext = ".h_dec";

//stores filename of encoded file
std::string enc_file_name = "";

//stores filename of decoded file
std::string dec_file_name = "";

void parse_args(int, char**);
void generate_file_names();

int main(int argc, char** argv) {
   parse_args(argc, argv);
   generate_file_names();

   //printf("opt_encode: %d\nopt_decode: %d\n"
   //       "enc_file_name: %s\ndec_file_name: %s\n",
   //       opt_encode, opt_decode, enc_file_name.c_str(),
   //       dec_file_name.c_str());

   Huffman hc(enc_file_name, dec_file_name);
   if (opt_encode) {
      hc.encode();
   } else if (opt_decode) {
      hc.decode();
   }
}

void parse_args(int argc, char** argv) {
   bool error = false;
   while (true) {
      int opt = getopt(argc, argv, "e:d:");
      if (opt == EOF)
         break;
      switch (opt) {
      case 'e':
         // if we want to encode a file, it means
         // that that file is the decoded file
         opt_encode = true;
         dec_file_name = optarg;
         break;
      case 'd':
         // if we want to decode a file, it means
         // that that file is the encoded file
         opt_decode = true;
         enc_file_name = optarg;
         break;
      default:
         error = true;
         break;
      }
   }
   if (optind < 3 || argc < 3 || optind > 3 || argc > 3) {
      std::cerr << "Error: Improper Usage" << std::endl;
      error = true;
   }
   if (opt_decode) {
       bool not_hc = false;
       size_t dotloc = enc_file_name.find_last_of(".");
       if (dotloc == std::string::npos) {
          not_hc = true;
       } else if (enc_file_name.substr(dotloc ) != enc_ext) {
          not_hc = true;
       }
       if (not_hc) {
          std::cerr << "Error: Filename is not of type filename"
                    << enc_ext << std::endl;
          error = true;
       }
   }
   if (error) {
      std::cerr << "Proper Usage: \n"
                << "./huffman.exe -e encode_file_name\n"
                << "./huffman.exe -d decode_file_name\n";
      exit(1);
   }
}

void generate_file_names() {
   if (opt_encode) {
      enc_file_name = dec_file_name + enc_ext;
   } else if (opt_decode) {
      size_t dotloc = enc_file_name.find_last_of(".");
      dec_file_name = enc_file_name.substr(0, dotloc);
      dec_file_name += dec_ext;
   }
}
