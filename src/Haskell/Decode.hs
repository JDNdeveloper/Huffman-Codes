-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
module Decode where

import Data.Map (Map)
import qualified Data.Map as Map

import Data.Maybe (Maybe)
import qualified Data.Maybe as Maybe

import HuffmanTypes

-- Takes in a bit string and a character to bit string
-- map and returns the decoded string
decode :: BitString -> CharMap -> String
decode "" cm = ""
decode s cm = fbs ++ decode rem cm
  where
    fbsRem = fstBitString s cm
    fbs = fst $ fbsRem
    rem = snd $ fbsRem

-- Builds a partition of a string by returning the
-- first x characters and the last x characters in
-- a tuple
buildPartition :: Int -> String -> (String, String)
buildPartition x s = (take x s, drop x s)

-- Given a string and a character to bit string map,
-- the first decoded sequence of the bit string is returned,
-- along with the remaining part of the bit string
fstBitString :: String -> CharMap -> (BitString, String)
fstBitString = fstBitString' 1

fstBitString' :: Int -> String -> CharMap
              -> (BitString, String)
fstBitString' x s cm
  | Maybe.isJust result = ([Maybe.fromJust result], sndPart)
  | x > length s = ("","")
  | otherwise = fstBitString' (x + 1) s cm
  where
    part = buildPartition x s
    fstPart = fst part
    sndPart = snd part
    result = Map.lookup fstPart m
    m = Map.fromList $ invertMap cm

-- Reverses the key value pairing in a map
invertMap :: [(a,b)] -> [(b,a)]
invertMap m = [ (y,x) | (x,y) <- m ]
