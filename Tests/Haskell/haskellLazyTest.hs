import System.IO
import System.CPUTime

data Record = Record Int String deriving (Show, Eq, Ord, Read)

time :: FilePath -> String -> IO t -> IO t
time filename label comp = do
	start <- getCPUTime
	v <- comp
	end <- getCPUTime
	let diff = (fromIntegral (end - start)) / (10^9)
	let s = label ++ ": " ++ show(diff) ++ "ms\n"
	appendFile filename s
	return v

rInt :: String -> Int
rInt = read

readRecords :: [[String]] -> [Record] -> [Record]
readRecords [] l = l
readRecords ((n:s):xs) l = readRecords xs (l ++ [Record (rInt n) (head s)])

constructIntList :: [Record] -> [Int]
constructIntList l = [n | (Record n s) <- l]

constructStringList :: [Record] -> [String]
constructStringList l = [s | (Record n s) <- l]

constructRecordList :: [Int] -> [String] -> [Record]
constructRecordList lint lstring = [(Record n s) | n <- lint, s <- lstring]

sumString :: Int -> String -> Int
sumString x s = x + (length s)

sumRecord :: Int -> Record -> Int
sumRecord x (Record n s) = x + n + (length s)

rightSumS :: String -> Int -> Int
rightSumS s x = sumString x s

rightSumR :: Record -> Int -> Int
rightSumR r x = sumRecord x r

addRecord :: Record -> Record
addRecord (Record n s) = (Record (n + 10) (s ++ "abab"))

createListInt :: Int -> [Int]
createListInt x = [x]

createListS :: String -> [String]
createListS s = [s]

createListR :: Record -> [Record]
createListR r = [r]

concatRec :: Record -> Record -> Record
concatRec (Record n1 s1) (Record n2 s2) = (Record (n1 + n2) (s1 ++ s2))

add3int :: Int -> Int -> Int -> Int
add3int x y z = x + y + z

add3str :: String -> String -> String -> String
add3str s1 s2 s3 = s1 ++ s2 ++ s3

add3rec :: Record -> Record -> Record -> Record
add3rec (Record n1 s1) (Record n2 s2) (Record n3 s3) = (Record (n1 + n2 + n3) (s1 ++ s2 ++ s3))

getSpaces :: [String] -> Int -> String -> String
getSpaces l 10000 s = s
getSpaces (a:as) n s = getSpaces as (n+1) (s ++ " " ++ a)

evenLength :: String -> Bool
evenLength s = even (length s)

evenAndLength :: Record -> Bool
evenAndLength (Record n s) = (even n) && (evenLength s)

retTrue :: a -> Bool
retTrue x = True

retFalse :: a -> Bool
retFalse x = False

bigNumber :: Int -> Bool
bigNumber x = (x > 1000000)

bigString :: String -> Bool
bigString s = ((length s) > 25)

bigRecord :: Record -> Bool
bigRecord (Record n s) = (bigNumber n) && (bigString s)

main = do
	ints <- readFile "../Input/ints.txt"
	strings <- readFile "../Input/strings.txt"
	recs <- readFile "../Input/records.txt"
	let l1 = map rInt (lines ints)
	let l2 = lines strings
	let l3 = readRecords (map words (lines recs)) []

	-- timing functions

	-- cons
	let hint = 0
	let hstring = "a"
	let hrec = Record hint hstring
	-- time filename label calculation
	-- the calculation has to follow the pattern
	-- function call `seq` return()
	-- due to lazy evaluation
	time "ints-times.txt" "cons" (hint : l1 `seq` return())
	time "strings-times.txt" "cons" (hstring : l2 `seq` return())
	time "records-times.txt" "cons" (hrec : l3 `seq` return())

	-- concat2
	let l4 = constructIntList l3
	let l5 = constructStringList l3
	let l6 = constructRecordList l1 l2
	time "ints-times.txt" "concat2" (l1 ++ l4 `seq` return())
	time "strings-times.txt" "concat2" (l2 ++ l5 `seq` return())
	time "records-times.txt" "concat2" (l3 ++ l6 `seq` return())

	-- concat1
	let ll1 = [l1, l4]
	let ll2 = [l2, l5]
	let ll3 = [l3, l6]
	time "ints-times.txt" "concat1" (concat ll1 `seq` return())
	time "strings-times.txt" "concat1" (concat ll2 `seq` return())
	time "records-times.txt" "concat1" (concat ll3 `seq` return())

	-- tail
	time "ints-times.txt" "tail" (tail l1 `seq` return())
	time "strings-times.txt" "tail" (tail l2 `seq` return())
	time "records-times.txt" "tail" (tail l3 `seq` return())

	-- init
	time "ints-times.txt" "init" (init l1 `seq` return())
	time "strings-times.txt" "init" (init l2 `seq` return())
	time "records-times.txt" "init" (init l3 `seq` return())

	-- !!
	time "ints-times.txt" "at" ((l1!!((length l1) - 1)) `seq` return())
	time "strings-times.txt" "at" ((l2!!((length l2) - 1)) `seq` return())
	time "records-times.txt" "at" ((l3!!((length l3) - 1)) `seq` return())

	-- reverse
	time "ints-times.txt" "reverse" (reverse l1 `seq` return())
	time "strings-times.txt" "reverse" (reverse l2 `seq` return())
	time "records-times.txt" "reverse" (reverse l3 `seq` return())

	-- foldl
	time "ints-times.txt" "foldl" (foldl (+) 0 l1 `seq` return())
	time "strings-times.txt" "foldl" (foldl sumString 0 l2 `seq` return())
	time "records-times.txt" "foldl" (foldl sumRecord 0 l3 `seq` return())

	-- foldr
	time "ints-times.txt" "foldr" (foldr (+) 0 l1 `seq` return())
	time "strings-times.txt" "foldr" (foldr rightSumS 0 l2 `seq` return())
	time "records-times.txt" "foldr" (foldr rightSumR 0 l3 `seq` return())

	-- scanl
	time "ints-times.txt" "scanl" (scanl (+) 0 l1 `seq` return())
	time "strings-times.txt" "scanl" (scanl sumString 0 l2 `seq` return())
	time "records-times.txt" "scanl" (scanl sumRecord 0 l3 `seq` return())

	-- scanr
	time "ints-times.txt" "scanr" (scanr (+) 0 l1 `seq` return())
	time "strings-times.txt" "scanr" (scanr rightSumS 0 l2 `seq` return())
	time "records-times.txt" "scanr" (scanr rightSumR 0 l3 `seq` return())

	-- map
	time "ints-times.txt" "map" (map (+10) l1 `seq` return())
	time "strings-times.txt" "map" (map (++ "abababab") l2 `seq` return())
	time "records-times.txt" "map" (map addRecord l3 `seq` return())

	-- concatMap
	time "ints-times.txt" "concatMap" (concatMap createListInt l1 `seq` return())
	time "strings-times.txt" "concatMap" (concatMap createListS l2 `seq` return())
	time "records-times.txt" "concatMap" (concatMap createListR l3 `seq` return())

	-- zip
	time "ints-times.txt" "zip" (zip l1 l4 `seq` return())
	time "strings-times.txt" "zip" (zip l2 l5 `seq` return())
	time "records-times.txt" "zip" (zip l3 l6 `seq` return())

	-- zip3
	let l7 = map (+10) l1
	let l8 = map (++ "abababab") l2
	let l9 = map addRecord l3
	time "ints-times.txt" "zip3" (zip3 l1 l4 l7 `seq` return())
	time "strings-times.txt" "zip3" (zip3 l2 l5 l8 `seq` return())
	time "records-times.txt" "zip3" (zip3 l3 l6 l9 `seq` return())

	-- zipWith
	time "ints-times.txt" "zipWith" (zipWith (+) l1 l4 `seq` return())
	time "strings-times.txt" "zipWith" (zipWith (++) l2 l5 `seq` return())
	time "records-times.txt" "zipWith" (zipWith concatRec l3 l6 `seq` return())

	-- zipWith3
	time "ints-times.txt" "zipWith3" (zipWith3 add3int l1 l4 l7 `seq` return())
	time "strings-times.txt" "zipWith3" (zipWith3 add3str l2 l5 l8 `seq` return())
	time "records-times.txt" "zipWith3" (zipWith3 add3rec l3 l6 l9 `seq` return())

	-- unzip
	let l10 = zip l1 l4
	let l11 = zip l2 l5
	let l12 = zip l3 l6
	time "ints-times.txt" "unzip" (unzip l10 `seq` return())
	time "strings-times.txt" "unzip" (unzip l11 `seq` return())
	time "records-times.txt" "unzip" (unzip l12 `seq` return())

	-- unzip3
	let l13 = zip3 l1 l4 l7
	let l14 = zip3 l2 l5 l8
	let l15 = zip3 l3 l6 l9
	time "ints-times.txt" "unzip3" (unzip3 l13 `seq` return())
	time "strings-times.txt" "unzip3" (unzip3 l14 `seq` return())
	time "records-times.txt" "unzip3" (unzip3 l15 `seq` return())

	-- unlines
	time "strings-times.txt" "unlines" (unlines l2 `seq` return())

	-- lines
	let s = unlines l2
	time "strings-times.txt" "lines" (lines s `seq` return())

	-- words
	let s1 = getSpaces l2 0 ""
	time "strings-times.txt" "words" (words s1 `seq` return())

	-- unwords
	time "strings-times.txt" "unwords" (unwords l2 `seq` return())

	-- filter
	time "ints-times.txt" "filter" (filter even l1 `seq` return())
	time "strings-times.txt" "filter" (filter evenLength l2 `seq` return())
	time "records-times.txt" "filter" (filter evenAndLength l3 `seq` return())

	-- take
	time "ints-times.txt" "take" (take 10000 l1 `seq` return())
	time "strings-times.txt" "take" (take 10000 l2 `seq` return())
	time "records-times.txt" "take" (take 10000 l3 `seq` return())

	-- takeWhile
	time "ints-times.txt" "takeWhile" (takeWhile retTrue l1 `seq` return())
	time "strings-times.txt" "takeWhile" (takeWhile retTrue l2 `seq` return())
	time "records-times.txt" "takeWhile" (takeWhile retTrue l3 `seq` return())

	-- drop
	time "ints-times.txt" "drop" (drop 10000 l1 `seq` return())
	time "strings-times.txt" "drop" (drop 10000 l2 `seq` return())
	time "records-times.txt" "drop" (drop 10000 l3 `seq` return())

	-- dropWhile
	time "ints-times.txt" "dropWhile" (dropWhile retFalse l1 `seq` return())
	time "strings-times.txt" "dropWhile" (dropWhile retFalse l2 `seq` return())
	time "records-times.txt" "dropWhile" (dropWhile retFalse l3 `seq` return())

	-- span
	time "ints-times.txt" "span" (span bigNumber l1 `seq` return())
	time "strings-times.txt" "span" (span bigString l2 `seq` return())
	time "records-times.txt" "span" (span bigRecord l3 `seq` return())

	-- break
	time "ints-times.txt" "break" (break bigNumber l1 `seq` return())
	time "strings-times.txt" "break" (break bigString l2 `seq` return())
	time "records-times.txt" "break" (break bigRecord l3 `seq` return())

	-- splitAt
	time "ints-times.txt" "splitAt" (splitAt ((length l1) `div` 2) l1 `seq` return())
	time "strings-times.txt" "splitAt" (splitAt ((length l2) `div` 2) l2 `seq` return())
	time "records-times.txt" "splitAt" (splitAt ((length l3) `div` 2) l3 `seq` return())