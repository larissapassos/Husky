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
	ints <- readFile "ints.txt"
	strings <- readFile "strings.txt"
	--recs <- readFile "records.txt"
	let l1 = map rInt (lines ints)
	let l2 = lines strings
	--let l3 = readRecords (map words (lines recs)) []
	putStrLn $ show $ length l1
	putStrLn $ show $ length l2

	-- timing functions

	-- cons
	let hint = 0
	let hstring = "a"
	--let hrec = Record hint hstring
	-- time filename label calculation
	-- the calculation has to follow the pattern
	-- function call `seq` return()
	-- due to lazy evaluation
	let t1 = hint : l1
	let t2 = hstring : l2
	--let t3 = hrec : l3
	time "ints-times.txt" "cons" (t1 `seq` return())
	time "strings-times.txt" "cons" (t2 `seq` return())
	--time "records-times.txt" "cons" (t3 `seq` return())

	-- concat2
	let l4 = map (`mod` 1000000) l1
	let l5 = map ((++) "____") l2
	putStrLn $ show $ length l4
	putStrLn $ show $ length l5
	--let l6 = constructRecordList l1 l2
	let t3 = l1 ++ l4
	let t4 = l2 ++ l5
	time "ints-times.txt" "concat2" (t3 `seq` return())
	time "strings-times.txt" "concat2" (t4 `seq` return())
	--time "records-times.txt" "concat2" (l3 ++ l6 `seq` return())

	-- concat1
	let ll1 = [l1, l4]
	let ll2 = [l2, l5]
	--let ll3 = [l3, l6]
	let t5 = concat ll1
	let t6 = concat ll2
	time "ints-times.txt" "concat1" (t5 `seq` return())
	time "strings-times.txt" "concat1" (t6 `seq` return())
	--time "records-times.txt" "concat1" (concat ll3 `seq` return())

	-- tail
	let t7 = tail l1
	let t8 = tail l2
	time "ints-times.txt" "tail" (t7 `seq` return())
	time "strings-times.txt" "tail" (t8`seq` return())
	--time "records-times.txt" "tail" (tail l3 `seq` return())

	-- init
	let t9 = init l1
	let t10 = init l2
	time "ints-times.txt" "init" (t9 `seq` return())
	time "strings-times.txt" "init" (t10 `seq` return())
	--time "records-times.txt" "init" (init l3 `seq` return())

	-- !!
	let t11 = l1!!((length l1) - 1)
	let t12 = l2!!((length l2) - 1)
	time "ints-times.txt" "at" (t11 `seq` return())
	time "strings-times.txt" "at" (t12 `seq` return())
	--time "records-times.txt" "at" ((l3!!((length l3) - 1)) `seq` return())

	-- reverse
	let t13 = reverse l1
	let t14 = reverse l2
	time "ints-times.txt" "reverse" (t13 `seq` return())
	time "strings-times.txt" "reverse" (t14 `seq` return())
	--time "records-times.txt" "reverse" (reverse l3 `seq` return())

	-- foldl
	let t15 = foldl (+) 0 l1
	let t16 = foldl sumString 0 l2
	time "ints-times.txt" "foldl" (t15 `seq` return())
	time "strings-times.txt" "foldl" (t16 `seq` return())
	--time "records-times.txt" "foldl" (foldl sumRecord 0 l3 `seq` return())

	-- foldr
	let t17 = foldr (+) 0 l1
	let t18 = foldr rightSumS 0 l2
	time "ints-times.txt" "foldr" (t17 `seq` return())
	time "strings-times.txt" "foldr" (t18 `seq` return())
	--time "records-times.txt" "foldr" (foldr rightSumR 0 l3 `seq` return())

	-- scanl
	let t19 = scanl (+) 0 l1
	let t20 = scanl sumString 0 l2
	time "ints-times.txt" "scanl" (t19 `seq` return())
	time "strings-times.txt" "scanl" (t20 `seq` return())
	--time "records-times.txt" "scanl" (scanl sumRecord 0 l3 `seq` return())

	-- scanr
	let t21 = scanr (+) 0 l1
	let t22 = scanr rightSumS 0 l2 
	time "ints-times.txt" "scanr" (t21 `seq` return())
	time "strings-times.txt" "scanr" (t22 `seq` return())
	--time "records-times.txt" "scanr" (scanr rightSumR 0 l3 `seq` return())

	-- map
	let l7 = map (+10) l1
	let l8 = map (++ "abababab") l2
	time "ints-times.txt" "map" (l7 `seq` return())
	time "strings-times.txt" "map" (l8 `seq` return())
	--time "records-times.txt" "map" (map addRecord l3 `seq` return())

	-- concatMap
	let t23 = concatMap createListInt l1
	let t24 = concatMap createListS l2
	time "ints-times.txt" "concatMap" (t23 `seq` return())
	time "strings-times.txt" "concatMap" (t24 `seq` return())
	--time "records-times.txt" "concatMap" (concatMap createListR l3 `seq` return())

	-- zip
	let l10 = zip l1 l4
	let l11 = zip l2 l5
	--let l12 = zip l3 l6
	time "ints-times.txt" "zip" (l10 `seq` return())
	time "strings-times.txt" "zip" (l11 `seq` return())
	--time "records-times.txt" "zip" (zip l3 l6 `seq` return())

	-- zip3
	let l13 = zip3 l1 l4 l7
	let l14 = zip3 l2 l5 l8
	--let l9 = map addRecord l3
	time "ints-times.txt" "zip3" (l13 `seq` return())
	time "strings-times.txt" "zip3" (l14 `seq` return())
	--time "records-times.txt" "zip3" (zip3 l3 l6 l9 `seq` return())

	-- zipWith
	let t25 = zipWith (+) l1 l4
	let t26 = zipWith (++) l2 l5
	time "ints-times.txt" "zipWith" (t25 `seq` return())
	time "strings-times.txt" "zipWith" (t26 `seq` return())
	--time "records-times.txt" "zipWith" (zipWith concatRec l3 l6 `seq` return())

	-- zipWith3
	let t27 = zipWith3 add3int l1 l4 l7
	let t28 = zipWith3 add3str l2 l5 l8
	time "ints-times.txt" "zipWith3" (t27 `seq` return())
	time "strings-times.txt" "zipWith3" (t28 `seq` return())
	--time "records-times.txt" "zipWith3" (zipWith3 add3rec l3 l6 l9 `seq` return())

	-- unzip
	let t29 = unzip l10
	let t30 = unzip l11
	time "ints-times.txt" "unzip" (t29 `seq` return())
	time "strings-times.txt" "unzip" (t30 `seq` return())
	--time "records-times.txt" "unzip" (unzip l12 `seq` return())

	-- unzip3
	--let l15 = zip3 l3 l6 l9
	let t31 = unzip3 l13
	let t32 = unzip3 l14
	time "ints-times.txt" "unzip3" (t31 `seq` return())
	time "strings-times.txt" "unzip3" (t32 `seq` return())
	--time "records-times.txt" "unzip3" (unzip3 l15 `seq` return())

	-- unlines
	let t33 = unlines l2
	time "strings-times.txt" "unlines" (t33 `seq` return())

	-- lines
	let t34 = lines t33
	time "strings-times.txt" "lines" (t34 `seq` return())

	-- words
	let s1 = getSpaces l2 0 ""
	let t35 = words s1
	time "strings-times.txt" "words" (t35 `seq` return())

	-- unwords
	let t36 = unwords l2
	time "strings-times.txt" "unwords" (t36 `seq` return())

	-- filter
	let t37 = filter even l1
	let t38 = filter evenLength l2
	time "ints-times.txt" "filter" (t37 `seq` return())
	time "strings-times.txt" "filter" (t38 `seq` return())
	--time "records-times.txt" "filter" (filter evenAndLength l3 `seq` return())

	-- take
	let t39 = take 10000 l1
	let t40 = take 10000 l2
	time "ints-times.txt" "take" (t39 `seq` return())
	time "strings-times.txt" "take" (t40 `seq` return())
	--time "records-times.txt" "take" (take 10000 l3 `seq` return())

	-- takeWhile
	let t41 = takeWhile retTrue l1
	let t42 = takeWhile retTrue l2
	time "ints-times.txt" "takeWhile" (t41 `seq` return())
	time "strings-times.txt" "takeWhile" (t42 `seq` return())
	--time "records-times.txt" "takeWhile" (takeWhile retTrue l3 `seq` return())

	-- drop
	let t43 = drop 10000 l1
	let t44 = drop 10000 l2
	time "ints-times.txt" "drop" (t43 `seq` return())
	time "strings-times.txt" "drop" (t44 `seq` return())
	--time "records-times.txt" "drop" (drop 10000 l3 `seq` return())

	-- dropWhile
	let t45 = dropWhile retFalse l1
	let t46 = dropWhile retFalse l2
	time "ints-times.txt" "dropWhile" (t45 `seq` return())
	time "strings-times.txt" "dropWhile" (t46 `seq` return())
	--time "records-times.txt" "dropWhile" (dropWhile retFalse l3 `seq` return())

	-- span
	let t47 = span bigNumber l1
	let t48 = span bigString l2
	time "ints-times.txt" "span" (t47 `seq` return())
	time "strings-times.txt" "span" (t48 `seq` return())
	--time "records-times.txt" "span" (span bigRecord l3 `seq` return())

	-- break
	let t49 = break bigNumber l1
	let t50 = break bigString l2
	time "ints-times.txt" "break" (t49 `seq` return())
	time "strings-times.txt" "break" (t50 `seq` return())
	--time "records-times.txt" "break" (break bigRecord l3 `seq` return())

	-- splitAt
	let t51 = splitAt ((length l1) `div` 2) l1
	let t52 = splitAt ((length l2) `div` 2) l2
	time "ints-times.txt" "splitAt" (t51 `seq` return())
	time "strings-times.txt" "splitAt" (t52 `seq` return())
	--time "records-times.txt" "splitAt" (splitAt ((length l3) `div` 2) l3 `seq` return())