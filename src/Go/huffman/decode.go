// Author: Jayden Navarro
// Date: 2-1-2016
// Class: CMPS 112
package huffman

func Decode(bitString string, mbs map[byte]string) string {
  decodedString := ""
  builder := ""
  msb := reverseMap(mbs)
  for _, c := range bitString {
    builder += string(c)
    bs, ok := msb[builder]
    if ok {
      decodedString += string(bs)
      builder = ""
    }
  }
  return decodedString
}

func reverseMap(mbs map[byte]string) map[string]byte {
  msb := make(map[string]byte)
  for b, s := range mbs {
    msb[s] = b
  }
  return msb
}
