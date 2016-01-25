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
encode s = (s,[('s',"01010")])
