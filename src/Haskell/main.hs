-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
import Encode
import Decode

main = do
  putStrLn "Huffman Codes in Haskell"
  putChar '\n'
  encodeOutput
  putChar '\n'
  decodeOutput

encodeOutput = do
  putStrLn "-- ENCODE EXAMPLE --"
  putStrLn "-> Inputs"
  putStrLn $ "String to encode: " ++ rawInput
  putStrLn "-> Outputs"
  putStrLn $ "Map: " ++ show charMap
  putStrLn $ "Bitstring: " ++ bitString
  putStrLn "-> Reversing operation..."
  putStrLn $ "Decoded string: " ++ decodedString
  where
    -- raw data
    rawInput = "Hello World!"
    -- constructed data (encoding)
    encodeObj = encode rawInput
    charMap = snd encodeObj
    bitString = fst encodeObj
    -- reversing the operation...(decoding)
    decodedString = decode bitString charMap
    
decodeOutput = do
  putStrLn "-- DECODE EXAMPLE --"
  putStrLn "-> Inputs"
  putStrLn $ "Initial Map: " ++ show rawCharMap
  putStrLn $ "Bitstring to decode: " ++ rawBitString
  putStrLn "-> Outputs"
  putStrLn $ "Decoded string: " ++ decodedString
  putStrLn "-> Reversing operation..."
  putStrLn $ "Map: " ++ show charMap
  putStrLn $ "Bitstring: " ++ bitString
  where
    -- raw data
    rawBitString = "01001"
    rawCharMap = [('H',"01"),('i',"00"),('!',"1")]
    -- constructed data (decoding)
    decodedString = decode rawBitString rawCharMap
    -- reversing the operation...(encoding)
    encodeObj = encode decodedString
    charMap = snd encodeObj
    bitString = fst encodeObj
