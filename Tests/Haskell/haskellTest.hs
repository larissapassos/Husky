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

main = do
	ints <- readFile "ints.txt"
	strings <- readFile "strings.txt"
	recs <- readFile "records.txt"
	let l1 = map rInt (lines ints)
	let l2 = lines strings
	let l3 = readRecords (map words (lines recs)) []

	-- timing functions
	let hint = 0
	let hstring = "a"
	let hrec = Record hint hstring
	time "ints-times.txt" "cons" (hint : l1 `seq` return())
	time "strings-times.txt" "cons" (hstring : l2 `seq` return())
	time "records-times.txt" "cons" (hrec : l3 `seq` return())

	let l4 = constructIntList l3
	let l5 = constructStringList l3
	let l6 = constructRecordList l1 l2
	time "ints-times.txt" "concat" (l1 ++ l4 `seq` return())
	time "strings-times.txt" "concat" (l2 ++ l5 `seq` return())
	time "records-times.txt" "concat" (l3 ++ l6 `seq` return())

	time "ints-times.txt" "map" (map (+10) l1 `seq` return())
	time "strings-times.txt" "concat" (map (++ "ah") l2 `seq` return())
	time "records-times.txt" "concat" (map show l3 `seq` return())
