# FunctionalLibrary

Source: https://hackage.haskell.org/package/base-4.7.0.0/docs/Prelude.html

(Larissa - wrapper class)
List operations - our container should support them
- (::) :: a -> [a] -> [a]
- (++) :: [a] -> [a] -> [a]

(Larissa)
- head :: [a] -> a 
  - last :: [a] -> a 
  - tail :: [a] -> [a] 
  - init :: [a] -> [a] 
  - null :: [a] -> Bool 
  - length :: [a] -> Int 
  - (!!) :: [a] -> Int -> a 9 
  - reverse :: [a] -> [a]
 
(Vinicius)
- foldl :: (b -> a -> b) -> b -> [a] -> b 
  - foldl1 :: (a -> a -> a) -> [a] -> a 
  - and :: [Bool] -> Bool 
  - or :: [Bool] -> Bool 
  - any :: (a -> Bool) -> [a] -> Bool 
  - all :: (a -> Bool) -> [a] -> Bool 
  - sum :: Num a => [a] -> a 
  - product :: Num a => [a] -> a 
  - concat :: [[a]] -> [a] 
  - concatMap :: (a -> [b]) -> [a] -> [b] 
  - maximum :: Ord a => [a] -> a 
  - minimum :: Ord a => [a] -> a 

(Larissa)
- scanl :: (b -> a -> b) -> b -> [a] -> [b] 
  - scanl1 :: (a -> a -> a) -> [a] -> [a] 
  - scanr :: (a -> b -> b) -> b -> [a] -> [b] 
  - scanr1 :: (a -> a -> a) -> [a] -> [a] 

(Ayo)
  - take :: Int -> [a] -> [a] 
  - drop :: Int -> [a] -> [a] 
  - takeWhile :: (a -> Bool) -> [a] -> [a] 
  - dropWhile :: (a -> Bool) -> [a] -> [a]

(Vinicius)
  - splitAt :: Int -> [a] -> ([a], [a])
  - span :: (a -> Bool) -> [a] -> ([a], [a]) 
  - break :: (a -> Bool) -> [a] -> ([a], [a]) 
  - elem :: Eq a => a -> [a] -> Bool infix 4 
  - notElem :: Eq a => a -> [a] -> Bool infix 4 

(Larissa)
- zip :: [a] -> [b] -> [(a, b)] 
  - zip3 :: [a] -> [b] -> [c] -> [(a, b, c)] 
  - zipWith :: (a -> b -> c) -> [a] -> [b] -> [c] 
  - zipWith3 :: (a -> b -> c -> d) -> [a] -> [b] -> [c] -> [d] 
  - unzip :: [(a, b)] -> ([a], [b]) 
  - unzip3 :: [(a, b, c)] -> ([a], [b], [c])
  - map :: (a -> b) -> [a] -> [b] 

(Vinicius)
- lines :: String -> [String] 
  - words :: String -> [String] 
  - unlines :: [String] -> String 
  - unwords :: [String] -> String

(Larissa - wrapper class)
- << operator

(Ayo)
Functions
- filter :: (a -> Bool) -> [a] -> [a]
- curry :: ((a, b) -> c) -> a -> b -> c
- uncurry :: (a -> b -> c) -> (a, b) -> c
- (.) :: (b -> c) -> (a -> b) -> a -> c

(1.2) lazy evaluation
