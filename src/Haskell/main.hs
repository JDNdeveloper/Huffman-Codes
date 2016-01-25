-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
import Encode
import Decode

main = putStrLn mainOutputString

encodeInput = "Hello World!"

decodeInput = "011000"
decodeMap = [('H',"01"),('i',"10"),('!',"00")]

mainOutputString = encodePrompt ++ "\n\n" ++ decodePrompt

encodePrompt = "String to encode: " ++ encodeInput ++
               "\nMap: " ++ theMap ++
               "\nEncoded string: " ++ theString
  where
    theMap = show $ snd theEncoding
    theString = fst theEncoding
    theEncoding = encode encodeInput
    
decodePrompt = "Bitstring to decode: " ++ decodeInput ++
               "\nMap: " ++ show decodeMap ++
               "\nDecoded bitstring: " ++
               decode decodeInput decodeMap
