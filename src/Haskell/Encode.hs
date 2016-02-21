-- Author: Jayden Navarro
-- Date: 1-15-2016
-- Class: CMPS 112
module Encode where

import Data.Map (Map)
import qualified Data.Map as Map

import Data.Maybe (Maybe)
import qualified Data.Maybe as Maybe

import HuffmanTypes

encode :: String -> (BitString, CharMap)
encode s = (bitString, charMap)
  where
    freqMap = buildFreqMap s
    tree = buildHuffmanTree freqMap
    charMap = buildCharMap tree
    bitString = buildBitString charMap s

type FreqMap = [(Int,Char)]

data HuffmanTree = HuffmanNode (Int,[Char])
                   HuffmanTree HuffmanTree
                 | HuffmanLeaf (Int,Char)
                 deriving (Show,Eq)

-- Combines two trees together
treeAdd :: HuffmanTree -> HuffmanTree -> HuffmanTree
t1@(HuffmanLeaf (x,u)) `treeAdd` t2@(HuffmanLeaf (y,v)) =
  HuffmanNode (x+y,[u,v]) t1 t2
t1@(HuffmanLeaf (x,u)) `treeAdd` t2@(HuffmanNode (y,v) _ _) =
  HuffmanNode (x+y,u:v) t1 t2
t1@(HuffmanNode (x,u) _ _) `treeAdd`
  t2@(HuffmanNode (y,v) _ _) = HuffmanNode (x+y,u++v) t1 t2
t1@(HuffmanNode (x,u) _ _) `treeAdd` t2@(HuffmanLeaf (y,v)) =
  HuffmanNode (x+y,v:u) t1 t2

instance Ord HuffmanTree where
  HuffmanLeaf (x,_) <= HuffmanNode (y,_) _ _ = x <= y
  HuffmanNode (x,_) _ _ <= HuffmanLeaf (y,_) = x <= y
  HuffmanLeaf (x,_) <= HuffmanLeaf (y,_) = x <= y
  HuffmanNode (x,_) _ _ <= HuffmanNode (y,_) _ _ = x <= y

-- Build the Frequency Map
buildFreqMap :: String -> FreqMap
buildFreqMap s = combineDups [ (1,c) | c <- s ]

combineDups :: [(Int,Char)] -> FreqMap
combineDups [] = []
combineDups (x:xs)
  | c `inFreqMap` xs = combineDups $ combineDup x xs
  | otherwise = x: combineDups xs
  where
    i = fst x
    c = snd x

combineDup :: (Int,Char) -> [(Int,Char)] -> [(Int,Char)]
combineDup x [] = [x]
combineDup x (y:ys)
  | snd x == snd y = (fst x + fst y, snd x): ys
  | otherwise = y: combineDup x ys

inFreqMap :: Char -> FreqMap -> Bool
inFreqMap ch = foldr (\(i,c) a -> c == ch || a) False

-- Build the Huffman Tree
buildHuffmanTree :: FreqMap -> HuffmanTree
buildHuffmanTree m = buildHuffmanTree' $ buildLeafList m

buildHuffmanTree' :: [HuffmanTree] -> HuffmanTree
buildHuffmanTree' [x] = x
buildHuffmanTree' l1 = buildHuffmanTree' l4
  where
    small1 = getSmallestTreeAndList l1
    x1 = fst small1
    l2 = snd small1
    small2 = getSmallestTreeAndList l2
    x2 = fst small2
    l3 = snd small2
    l4 = (x2 `treeAdd` x1): l3

buildLeafList :: FreqMap -> [HuffmanTree]
buildLeafList = foldr (\x a -> HuffmanLeaf x: a) []

getSmallestTreeAndList :: [HuffmanTree] ->
                      (HuffmanTree,[HuffmanTree])
getSmallestTreeAndList l = (smallest,
                            freqMapWithoutSmallest)
  where
    smallest = foldr1 (\x a -> if x <= a then x else a) l
    freqMapWithoutSmallest = filter (/= smallest) l

-- Build the Char to Bitstring Map
buildCharMap :: HuffmanTree -> CharMap
buildCharMap (HuffmanLeaf (_,x)) = [(x,"")]
buildCharMap (HuffmanNode _ a b) = cMap
  where
    aMap1 = buildCharMap a
    bMap1 = buildCharMap b
    aMap2 = addZeroBit aMap1
    bMap2 = addOneBit bMap1
    cMap = aMap2 ++ bMap2

addZeroBit :: CharMap -> CharMap
addZeroBit = map (\(x,y) -> (x,'0':y))

addOneBit :: CharMap -> CharMap
addOneBit = map (\(x,y) -> (x,'1':y))

-- Build the Bitstring
buildBitString :: CharMap -> String -> BitString
buildBitString cm s = foldr
                      (\x a ->
                        (Maybe.fromJust
                         $ Map.lookup x m) ++ a) [] s
  where
    m = Map.fromList cm
