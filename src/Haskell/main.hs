-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
import Encode
import Decode

main = do
  putStrLn encodePrompt
  putChar '\n'
  putStrLn decodePrompt

encodePrompt = "-- ENCODE EXAMPLE --" ++
               "\n-> Inputs" ++
               "\nString to encode: " ++ rawInput ++
               "\n-> Outputs" ++
               "\nMap: " ++ show charMap ++
               "\nBitstring: " ++ bitString ++
               "\n-> Reversing operation..." ++
               "\nDecoded string: " ++ decodedString
  where
    -- raw data
    rawInput = "Hello World!"
    -- constructed data (encoding)
    encodeObj = encode rawInput
    charMap = snd encodeObj
    bitString = fst encodeObj
    -- reversing the operation...(decoding)
    decodedString = decode bitString charMap
    
decodePrompt = "-- DECODE EXAMPLE --" ++
               "\n-> Inputs" ++
               "\nInitial Map: " ++ show rawCharMap ++
               "\nBitstring to decode: " ++ rawBitString ++
               "\n-> Outputs" ++
               "\nDecoded string: " ++ decodedString ++
               "\n-> Reversing operation..." ++
               "\nMap: " ++ show charMap ++
               "\nBitString: " ++ bitString
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
