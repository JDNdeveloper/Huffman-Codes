# Author: Jayden Navarro
# Date: 10/13/2015

class HuffmanCodes:

   class Node:
      def __init__(self):
         self.left = None
         self.right = None
         self.chars = []
         self.freq = -1

   def __init__(self):
      self._clear()

   @property
   def bitString(self):
      return self._bitString

   @property
   def string(self):
      return self._string

   @property
   def charToBitsMap(self):
      return self._cMap

   @property
   def bitsToCharMap(self):
      return {v: k for k, v in self._cMap.items()}

   @property
   def freqMap(self):
      return self._freqMap

   def traverseTree(self):
      if len(self._tree) > 0:
         self._traverseTree(self._tree[0])

   def encode(self, string):
      self._clear()
      self._string = string
      if len(self._string) < 1:
         print("ERROR: No string provided")
         return
      self._calcFreq()
      self._buildTree()
      self._buildMap()
      self._buildBitString()
      return self._bitString

   def decode(self, bitString, cMap):
      self._clear()
      self._bitString = bitString
      self._cMap = cMap

      self._decode()
      return self._string

   # performs preorder traversal of Huffman Tree
   def _traverseTree(self, node):
      if node != None:
         print("Chars: %s, Freq: %s" % (str(node.chars), 
            str(node.freq)))
         self._traverseTree(node.left)
         self._traverseTree(node.right)

   def _clear(self):
      self._cMap = {}
      self._freqMap = {}
      self._tree = []
      self._string = ""
      self._bitString = ""

   def _decode(self):
      bitSubString = ""
      bTcMap = self.bitsToCharMap
      for char in self._bitString:
         bitSubString += char
         if bitSubString in bTcMap.keys():
            self._string += bTcMap[bitSubString]
            bitSubString = ""

   def _calcFreq(self):
      for char in self._string:
         if char in self._freqMap:
            self._freqMap[char] += 1
         else:
            self._freqMap[char] = 1

   def _buildTree(self):
      for char, freq in self._freqMap.items():
         temp = self.Node()
         temp.chars.append(char)
         temp.freq = freq
         self._tree.append(temp)
      while len(self._tree) > 1:
         a = self._getSmallestNode()
         self._tree.remove(a)
         b = self._getSmallestNode()
         self._tree.remove(b)
         combined = self.Node()
         combined.chars.extend(a.chars)
         combined.chars.extend(b.chars)
         combined.freq = a.freq + b.freq
         combined.left = b
         combined.right = a
         self._tree.append(combined)

   def _getSmallestNode(self):
      smallNode = None
      for node in self._tree:
         if smallNode == None:
            smallNode = node
         else:
            if node.freq < smallNode.freq:
               smallNode = node
      return smallNode

   def _buildMap(self):
      if len(self._tree) != 1: 
         return
      self._buildMapRecursive(self._tree[0])

   def _buildMapRecursive(self, node):
      if node.left == None or node.right == None:
         return
      for char in node.left.chars:
         if char in self._cMap.keys():
            self._cMap[char] += '0'
         else:
            self._cMap[char] = '0'
      self._buildMapRecursive(node.left)
      for char in node.right.chars:
         if char in self._cMap.keys():
            self._cMap[char] += '1'
         else:
            self._cMap[char] = '1'
      self._buildMapRecursive(node.right)

   def _buildBitString(self):
      for char in self._string:
         self._bitString += self._cMap[char]


def runTests(testString):
   # runs basic functionality checks
   HC = HuffmanCodes()
   assert HC.decode("01", {"h":"0", "i":"1"}) == "hi"
   assert HC.decode("0110000011", {"l":"00", "h":"01", "e":"10", "o":"11"}) \
      == "hello"
   HC.encode("hello!")
   for node in HC._tree:
      assert set(node.chars) == set(['l', 'e', 'h', 'o', '!'])
      assert node.freq == 6
      assert node.left.freq == 4
      assert node.right.freq == 2

   # outputs example details when encoding run on testString
   HC.encode(testString)
   print("Original String: \"%s\"\n" % HC.string)
   print("Huffman BitString: %s\n" % HC.bitString)

   asciiBitString = bin(int.from_bytes(testString.encode(), 'big'))[2:]
   print("ASCII BitString: %s\n" % asciiBitString)

   huffmanBitLen = len(HC.bitString)
   asciiBitLen = len(asciiBitString)
   ratio = asciiBitLen / huffmanBitLen
   print("Huffman Length: %d, ASCII Length: %d, Compression: %0.1fx\n" 
      % (huffmanBitLen, asciiBitLen, ratio))

   print("Char to Bits Map: %s\n" % str(HC.charToBitsMap))
   print("Char Frequency Map: %s\n" % str(HC.freqMap))
   assert testString == HC.decode(HC.bitString, HC.charToBitsMap)

runTests("Testing 123!")
