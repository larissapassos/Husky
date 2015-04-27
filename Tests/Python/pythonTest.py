import time
from functools import reduce
from itertools import takewhile, dropwhile

intFile = "ints.txt"
stringFile = "strings.txt"
recFile = "records.txt"

class Record:
	def __init__(self, num, s):
		self.num = num
		self.s = s

	def __str__(self):
		return str(self.num) + " " + self.s

def readFile(filename, l):
	with open(filename, "r") as f:
		if filename == recFile:
			for line in f:
				elm = line.split()
				rec = Record(int(elm[0]), elm[1])
				l.append(rec)
		elif filename == stringFile:
			for line in f:
				elm = line.split()
				l.append(elm[0])
		else:
			for line in f:
				elm = line.split()
				l.append(int(elm[0]))

def constructIntList(recordList):
	return [r.num for r in recordList]

def constructStringList(recordList):
	return [r.s for r in recordList]

def constructRecList(intList, stringList):
	recList = []
	for n, s in zip(intList, stringList):
		r = Record(n,s)
		recList.append(r)
	return recList		

def measureTime(outfile, label, f, *args):
	start = time.clock()
	f(*args)
	end = time.clock()
	timespan = (end - start)*1000
	line = label + ": " + str(timespan) + "ms\n"
	outfile.write(line)

# Auxiliary functions
def cons(head, tail):
	newList = tail.copy()
	newList.insert(0, head)
	return newList

def concat2(l1, l2):
	return l1 + l2

def tail(l):
	return l[1:]

def init(l):
	return l[:(len(l) - 1)]

def at(l, index):
	return l[index]

def reverse(l):
	return l[::-1]

def zipWith(f, *lists):
	return [f(*result) for result in zip(*lists)]

def unlines(l):
	return '\n'.join(l)

def lines(s):
	return s.split('\n')

def unwords(l):
	return ' '.join(l)

def words(s):
	return s.split(' ')

def take(n, l):
	return l[:n]

def drop(n, l):
	return l[:-n]

def span_container(pred, l):
	return (takewhile(pred, l), dropwhile(pred, l))

def break_container(pred, l):
	return span_container(lambda x : not pred(x), l)

def splitAt(n, l):
	return (take(n, l), drop(n, l))

def main():
	l1 = []
	l2 = []
	l3 = []

	readFile(intFile, l1)
	readFile(stringFile, l2)
	readFile(recFile, l3)

	with open("ints-times.txt", "w") as fints, open("strings-times.txt", "w") as fstrings, open("records-times.txt", "w") as frecs:
		# timing functions
		l4 = constructIntList(l3)
		l5 = constructStringList(l3)
		l6 = constructRecList(l1,l2)

		# cons
		hi = 0
		hs = "a"
		hr = Record(hi, hs)
		measureTime(fints, "cons", cons, hi, l1)
		measureTime(fstrings, "cons", cons, hs, l2)
		measureTime(frecs, "cons", cons, hr, l3)

		# concat2
		measureTime(fints, "concat2", concat2, l1, l4)
		measureTime(fstrings, "concat2", concat2, l2, l5)
		measureTime(frecs, "concat2", concat2, l3, l6)

		# concat1
		# no implementation

		# tail
		measureTime(fints, "tail", tail, l1)
		measureTime(fstrings, "tail", tail, l2)
		measureTime(frecs, "tail", tail, l3)

		# init
		measureTime(fints, "init", init, l1)
		measureTime(fstrings, "init", init, l2)
		measureTime(frecs, "init", init, l3)

		# at
		measureTime(fints, "at", at, l1, len(l1) - 1)
		measureTime(fstrings, "at", at, l2, len(l2) - 1)
		measureTime(frecs, "at", at, l3, len(l3) - 1)

		# reverse
		measureTime(fints, "reverse", reverse, l1)
		measureTime(fstrings, "reverse", reverse, l2)
		measureTime(frecs, "reverse", reverse, l3)

		# foldl
		sumInt = lambda x, y: x + y
		sumString = lambda x, s: x + len(s)
		sumRecord = lambda x, r: x + r.num + len(r.s)
		measureTime(fints, "foldl", reduce, sumInt, l1, 0)
		measureTime(fstrings, "foldl", reduce, sumString, l2, 0)
		measureTime(frecs, "foldl", reduce, sumRecord, l3, 0)

		# foldr
		# no implementation

		# scanl
		# no implementation

		# scanr
		# no implementation

		# map
		addint = lambda x: x + 10
		addstring = lambda s: s + "abababab"
		addRecord = lambda r: Record(r.num + 10, r.s + "abab")
		measureTime(fints, "map", map, addint, l1)
		measureTime(fstrings, "map", map, addstring, l2)
		measureTime(frecs, "map", map, addRecord, l3)

		# concatMap
		# no implementation

		# zip
		measureTime(fints, "zip", zip, l1, l4)
		measureTime(fstrings, "zip", zip, l2, l5)
		measureTime(frecs, "zip", zip, l3, l6)

		# zip3
		l7 = map(addint, l1)
		l8 = map(addstring, l2)
		l9 = map(addRecord, l3)
		measureTime(fints, "zip", zip, l1, l4, l7)
		measureTime(fstrings, "zip", zip, l2, l5, l8)
		measureTime(frecs, "zip", zip, l3, l6, l9)

		# zipWith
		catString = lambda s1, s2: s1 + s2
		catRecord = lambda r1, r2: Record(r1.num + r2.num, r1.s + r2.s)
		measureTime(fints, "zipWith", zipWith, sumInt, l1, l4)
		measureTime(fstrings, "zipWith", zipWith, catString, l2, l5)
		measureTime(frecs, "zipWith", zipWith, catRecord, l3, l6)

		# zipWith3
		add3int = lambda x, y, z: x + y + z
		add3string = lambda s1, s2, s3: s1 + s2 + s3
		add3Record = lambda r1, r2, r3: Record(r1.num + r2.num + r3.num, r1.s + r2.s + r3.s)
		measureTime(fints, "zipWith", zipWith, add3int, l1, l4, l7)
		measureTime(fstrings, "zipWith", zipWith, add3string, l2, l5, l8)
		measureTime(frecs, "zipWith", zipWith, add3Record, l3, l6, l9)

		# unzip
		l10 = zip(l1, l4)
		l11 = zip(l2, l5)
		l12 = zip(l3, l6)
		measureTime(fints, "unzip", zip, *l10)
		measureTime(fstrings, "unzip", zip, *l11)
		measureTime(frecs, "unzip", zip, *l12)

		# unzip3
		l13 = zip(l1, l4, l7)
		l14 = zip(l2, l5, l8)
		l15 = zip(l3, l6, l9)
		measureTime(fints, "unzip3", zip, *l13)
		measureTime(fstrings, "unzip3", zip, *l14)
		measureTime(frecs, "unzip3", zip, *l15)

		# unlines
		measureTime(fstrings, "unlines", unlines, l2)

		# lines
		s = unlines(l2)
		measureTime(fstrings, "lines", lines, s)

		# words
		s = ' '.join(l2[:10000])
		measureTime(fstrings, "words", words, s)

		# unwords
		measureTime(fstrings, "unwords", unwords, l2)

		# filter
		evens = lambda x: x % 2 == 0
		evenLength = lambda s: len(s) % 2 == 0
		evenAndLength = lambda r: evens(r.num) and evenLength(r.s)
		measureTime(fints, "filter", filter, evens, l1)
		measureTime(fstrings, "filter", filter, evenLength, l2)
		measureTime(frecs, "filter", filter, evenAndLength, l3)

		# take
		measureTime(fints, "take", take, 10000,l1)
		measureTime(fstrings, "take", take, 10000, l2)
		measureTime(frecs, "take", take, 10000, l3)

		# takewhile
		retTrue = lambda x: True
		measureTime(fints, "takewhile", takewhile, retTrue, l1)
		measureTime(fstrings, "takewhile", takewhile, retTrue, l2)
		measureTime(frecs, "takewhile", takewhile, retTrue, l3)

		# drop
		measureTime(fints, "drop", drop, 10000,l1)
		measureTime(fstrings, "drop", drop, 10000, l2)
		measureTime(frecs, "drop", drop, 10000, l3)

		# dropwhile
		retFalse = lambda x: False
		measureTime(fints, "dropwhile", dropwhile, retFalse, l1)
		measureTime(fstrings, "dropwhile", dropwhile, retFalse, l2)
		measureTime(frecs, "dropwhile", dropwhile, retFalse, l3)

		# span_container
		bigNumber = lambda x: x > 1000000
		bigString = lambda s: len(s) > 25
		bigRecord = lambda r: bigNumber(r.num) and bigString(r.s)
		measureTime(fints, "span_container", span_container, bigNumber, l1)
		measureTime(fstrings, "span_container", span_container, bigString, l2)
		measureTime(frecs, "span_container", span_container, bigRecord, l3)

		# break_container
		measureTime(fints, "break_container", break_container, bigNumber, l1)
		measureTime(fstrings, "break_container", break_container, bigString, l2)
		measureTime(frecs, "break_container", break_container, bigRecord, l3)

		# splitAt
		measureTime(fints, "splitAt", splitAt, len(l1) // 2, l1)
		measureTime(fstrings, "splitAt", splitAt, len(l2) // 2, l2)
		measureTime(frecs, "splitAt", splitAt, len(l3) // 2, l3)





if __name__ == "__main__":
	main()
