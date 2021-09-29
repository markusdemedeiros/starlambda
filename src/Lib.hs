{-# LANGUAGE ForeignFunctionInterface #-}

module Lib
  ( someFunc,
  )
where

import Foreign
import Foreign.C

someFunc :: IO ()
someFunc = putStrLn "someFunc"

foreign import ccall "exp" c_exp :: Double -> Double

foreign import ccall "math.h sin" c_sin :: Double -> Double
