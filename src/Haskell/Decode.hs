-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
module Decode where

import Data.Map (Map)
import qualified Data.Map as Map

import Data.Maybe (Maybe)
import qualified Data.Maybe as Maybe

import HuffmanTypes

decode :: BitString -> CharMap -> String
decode "" cm = ""
decode s cm = fbs ++ decode rem cm
  where
    fbsRem = fstBitString s cm
    fbs = fst $ fbsRem
    rem = snd $ fbsRem

buildPartition :: Int -> String -> (String, String)
buildPartition x s = (take x s, drop x s)

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

invertMap :: [(a,b)] -> [(b,a)]
invertMap m = [ (y,x) | (x,y) <- m ] 
