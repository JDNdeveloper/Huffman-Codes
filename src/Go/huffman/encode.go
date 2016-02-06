// Author: Jayden Navarro
// Date: 2-1-2016
// Class: CMPS 112
package huffman

type node struct {
  left *node
  right *node
  chars []byte
  freq int
}

func Encode(s string) (string, map[byte]string) {
  freqMap := calcFreq(s)
  cNode := buildTree(freqMap)
  charMap := make(map[byte]string)
  pCharMap := &charMap
  buildMap(cNode, pCharMap)
  bitString := buildBitString(s, charMap)
  return bitString, charMap
}

func calcFreq(s string) map[byte]int {
  freqMap := make(map[byte]int)
  for _, c := range s {
    _, ok := freqMap[byte(c)]
    if ok {
      freqMap[byte(c)] += 1
    } else {
      freqMap[byte(c)] = 1
    }
  }
  return freqMap
}

func buildTree(freqMap map[byte]int) *node {
  var nodeList []*node
  for char, freq := range freqMap {
    temp := &node{nil, nil, nil, 0}
    temp.chars = append(temp.chars, char)
    temp.freq = freq
    nodeList = append(nodeList, temp)
  }
  for len(nodeList) > 1 {
    var a, b *node
    a, nodeList = getSmallestNode(nodeList)
    b, nodeList = getSmallestNode(nodeList)
    combined := &node{nil, nil, nil, 0}
    combined.chars = append(a.chars, b.chars...)
    combined.freq = a.freq + b.freq
    combined.left = b
    combined.right = a
    nodeList = append(nodeList, combined)
  }
  return nodeList[0]
}

func getSmallestNode(nodeList []*node) (*node, []*node) {
  var newNodeList []*node
  smallNode := &node{nil, nil, nil, 0}
  smallNode.freq = -1
  for _, cNode := range nodeList {
    if smallNode.freq == -1 {
      smallNode = cNode
    } else if cNode.freq < smallNode.freq {
      newNodeList = append(newNodeList, smallNode)
      smallNode = cNode
    } else {
      newNodeList = append(newNodeList, cNode)
    }
  }
  return smallNode, newNodeList
}


func buildMap(cNode *node, charMap *map[byte]string) {  
  if cNode.left == nil || cNode.right == nil {
    return
  }
  for _, char := range cNode.left.chars {
    _, ok := (*charMap)[char]
    if ok {
      (*charMap)[char] += "0"
    } else {
      (*charMap)[char] = "0"
    }
  }
  buildMap(cNode.left, charMap)
  for _, char := range cNode.right.chars {
    _, ok := (*charMap)[char]
    if ok {
      (*charMap)[char] += "1"
    } else {
      (*charMap)[char] = "1"
    }
  }
  buildMap(cNode.right, charMap)
}

func buildBitString(s string,
  charMap map[byte]string) string {
  bitString := ""
  for _, char := range s {
    bitString += charMap[byte(char)]
  }
  return bitString
}
