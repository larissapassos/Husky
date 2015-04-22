import time

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
def concat(l1, l2):
	return l1 + l2

def main():
	l1 = []
	l2 = []
	l3 = []

	readFile(intFile, l1)
	readFile(stringFile, l2)
	readFile(recFile, l3)

	with open("ints-times.txt", "w") as fints, open("strings-times.txt", "w") as fstrings, open("records-times.txt", "w") as frecs:
		#testing functions
		l4 = constructIntList(l3)
		l5 = constructStringList(l3)
		l6 = constructRecList(l1,l2)
		measureTime(fints, "concat", concat, l1, l4)
		measureTime(fstrings, "concat", concat, l2, l5)
		measureTime(frecs, "concat", concat, l3, l6)



if __name__ == "__main__":
	main()
