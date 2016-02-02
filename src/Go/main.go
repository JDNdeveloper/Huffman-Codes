// Author: Jayden Navarro
// Date: 1-15-2016
// Class: CMPS 112
package main

import (
  "fmt"
  "./huffman"
)

func main() {
  fmt.Println("Huffman Codes in Go\n")
  encodeOutput()
  fmt.Println()
  decodeOutput()
}

func encodeOutput() {
  // raw data
  rawInput := "Hello World!"
  // constructed data (encoding)
  bitString, charMap := huffman.Encode(rawInput)
  // reversing the operation...(decoding)
  decodedString := huffman.Decode(bitString, charMap)
  
	fmt.Println("-- ENCODE EXAMPLE --")
  fmt.Println("-> Inputs")
  fmt.Printf("String to encode: %s\n", rawInput)
  fmt.Println("-> Outputs")
  fmt.Print("Map: ")
  printMap(charMap)
  fmt.Printf("Bitstring: %s\n", bitString)
  fmt.Println("-> Reversing operation...")
  fmt.Printf("Decoded string: %s\n", decodedString)
}

func decodeOutput() {
  // raw data
  rawBitString := "01001"
  rawCharMap := map[byte]string {
    'H': "01",
    'i': "00",
    '!': "1",
  }
  // constructed data (decoding)
  decodedString := huffman.Decode(rawBitString, rawCharMap)
  // reversing the operation...(encoding)
  bitString, charMap := huffman.Encode(decodedString)
  
  fmt.Println("-- DECODE EXAMPLE --")
  fmt.Println("-> Inputs")
  fmt.Print("Initial Map: ")
  printMap(rawCharMap)
  fmt.Printf("Bitstring to decode: %s\n", rawBitString)
  fmt.Println("-> Outputs")
  fmt.Printf("Decoded string: %s\n", decodedString)
  fmt.Println("-> Reversing operation...")
  fmt.Print("Map: ")
  printMap(charMap)
  fmt.Printf("Bitstring: %s\n", bitString)
}

func printMap(m map[byte]string) {
  fmt.Print("[ ")
  for c, b := range m {
    fmt.Printf("('%c':%s) ", c, b)
  }
  fmt.Println("]")
}
