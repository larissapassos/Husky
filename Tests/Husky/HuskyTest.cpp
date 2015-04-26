#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "husky.h"

using namespace std;
using namespace chrono;
using namespace husky;
using tp = high_resolution_clock::time_point;

// Files' path
const char* intFile = "ints.txt";
const char* stringFile = "strings.txt";
const char* recFile = "records.txt";

// Custom class for testing
struct Record {
	int num;
	string str;
};

// read records
istream& operator>>(istream& is, Record& r) {
	int n;
	string s;
	is >> n >> s;
	r.num = n;
	r.str = s;
	return is;
}

// Print records
ostream& operator<<(ostream& os, const Record& r) {
	return os << r.num << ' ' << r.str;
}

// Print vectors
template<typename T>
ostream& operator<<(ostream& os, vector<T>& v)
{
	for (auto& x : v) os << x << "\n";
	return os;
}

//  read file into vector
template<typename T>
void readFile(const char* filename, vector<T>& v) {
	ifstream input;
	input.open(filename);
	T elm;
	while (!input.eof()) {
		input >> elm;
		v.push_back(elm);
	}
	input.close();
}

// construct vector of ints from vector of records
vector<int> constructIntVector(const vector<Record>& v) {
	vector<int> v2;
	for (auto rec : v) {
		v2.push_back(rec.num);
	}
	return v2;
}

// construct vector of strings from vector of records
vector<string> constructStringVector(const vector<Record>& v) {
	vector<string> v2;
	for (auto rec : v) {
		v2.push_back(rec.str);
	}
	return v2;
}

// construct vector of records from vectors of ints and strings
vector<Record> constructRecordVector(const vector<int>& v1, const vector<string>& v2) {
	vector<Record> v3;
	auto it1 = v1.begin();
	for (auto s : v2) {
		int n = *it1;
		Record r{ n, s };
		v3.push_back(r);
		++it1;
	}
	return v3;
}

/* ------------------------- */
/* Auxiliary functions below */
/* ------------------------ */


int main() {
	vector<int> v1;
	vector<string> v2;
	vector<Record> v3;
	

	// Populating the vectors
	readFile(intFile, v1);
	readFile(stringFile, v2);
	readFile(recFile, v3);

	// opening files for writing
	ofstream outInts;
	outInts.open("ints-times.txt");
	ofstream outStrings;
	outStrings.open("strings-times.txt");
	ofstream outRecs;
	outRecs.open("records-times.txt");

	// Testing husky functions - the label indicates which function is being tested
	const char* label;
	tp tstart;
	tp tend;

	// Cons
	label = "cons";
	int hi = 0;
	string hs = "a";
	Record r { hi, hs };

	tstart = high_resolution_clock::now();
	cons(hi, v1);
	tend = high_resolution_clock::now();
	auto timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	cons(hs, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	cons(r, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// Concat between two vectors
	label = "concat2";
	vector<int> v4 = constructIntVector(v3);
	vector<string> v5 = constructStringVector(v3);
	vector<Record> v6 = constructRecordVector(v1, v2);

	tstart = high_resolution_clock::now();
	concat(v1,v4);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concat(v2, v5);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concat(v3, v6);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";
	
	// concat for 1 vector
	label = "concat1";
	
	tstart = high_resolution_clock::now();
	concat(v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concat(v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concat(v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// tail
	label = "tail";

	tstart = high_resolution_clock::now();
	tail(v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	tail(v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	tail(v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// init
	label = "init";

	tstart = high_resolution_clock::now();
	init(v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	init(v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	init(v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";
	
	// at
	label = "at";

	tstart = high_resolution_clock::now();
	at(v1, v1.size() - 1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	at(v2, v2.size() - 1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	at(v3, v3.size() - 1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// reverse
	label = "reverse";

	tstart = high_resolution_clock::now();
	reverse(v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	reverse(v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	reverse(v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";
	
	// foldl
	label = "foldl";
	auto sumString = [](int x, string s) { return x + s.length(); };
	auto sumRecord = [](int x, Record r) { return x + r.num + r.str.length(); };

	tstart = high_resolution_clock::now();
	foldl(v1, 0, plus<int>());
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	foldl(v2, 0, sumString);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	foldl(v3, 0, sumRecord);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";
	
	// foldr
	label = "foldr";

	tstart = high_resolution_clock::now();
	foldr(v1, 0, plus<int>());
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	foldr(v2, 0, sumString);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	foldr(v3, 0, sumRecord);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";
	
	// scanl
	label = "scanl";

	tstart = high_resolution_clock::now();
	scanl(plus<int>(), 0, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	scanl(sumString, 0, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	scanl(sumRecord, 0, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// scanr
	label = "scanr";

	tstart = high_resolution_clock::now();
	scanr(plus<int>(), 0, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	scanr(sumString, 0, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	scanr(sumRecord, 0, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// map
	label = "map";
	auto addint = [](int x) { return x + 10; };
	auto addstring = [](string s) { return s + "abababab"; };
	auto addRecord = [](Record r) { return Record{ (r.num + 10), r.str + "abab" }; };

	tstart = high_resolution_clock::now();
	auto v7 = map(v1, addint);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v8 = map(v2, addstring);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v9 = map(v3, addRecord);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// concatMap
	label = "concatMap";

	tstart = high_resolution_clock::now();
	concatMap(v1, addint);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concatMap(v2, addstring);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	concatMap(v3, addRecord);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// zip
	label = "zip";

	tstart = high_resolution_clock::now();
	auto v10 = zip(v1, v4);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v11 = zip(v2, v5);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v12 = zip(v3, v6);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// zip3
	label = "zip3";

	tstart = high_resolution_clock::now();
	auto v13 = zip3(v1, v4, v7);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v14 = zip3(v2, v5, v8);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	auto v15 = zip3(v3, v6, v9);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// zipWith
	label = "zipWith";
	auto concatRec = [](Record r1, Record r2) { return Record{ r1.num + r2.num, r1.str + r2.str }; };

	tstart = high_resolution_clock::now();
	zipWith(plus<int>(), v1, v4);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	zipWith(plus<string>(), v2, v5);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	zipWith(concatRec, v3, v6);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// zipWith3
	label = "zipWith3";
	auto add3int = [](int x, int y, int z) { return x + y + z; };
	auto add3string = [](string s1, string s2, string s3) { return s1 + s2 + s3; };
	auto add3Record = [](Record r1, Record r2, Record r3) { return Record{ (r1.num + r2.num + r3.num), (r1.str + r2.str + r3.str) }; };

	tstart = high_resolution_clock::now();
	zipWith3(add3int, v1, v4, v7);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	zipWith3(add3string, v2, v5, v8);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	zipWith3(add3Record, v3, v6, v9);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// unzip
	label = "unzip";

	tstart = high_resolution_clock::now();
	unzip(v10);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	unzip(v11);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	unzip(v12);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// unzip3
	label = "unzip3";

	tstart = high_resolution_clock::now();
	unzip3(v13);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	unzip3(v14);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	unzip3(v15);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// lines
	label = "lines";
	string s{ "a\nb\nc\nd\n" };

	tstart = high_resolution_clock::now();
	lines(s);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	// unlines
	label = "unlines";

	tstart = high_resolution_clock::now();
	unlines(v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	// words
	label = "words";
	string s1{ "a b c d" };

	tstart = high_resolution_clock::now();
	auto v16 = words(s1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	// unwords
	label = "unwords";

	tstart = high_resolution_clock::now();
	unwords(v16);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	// filter
	label = "filter";
	auto evens = [](int x) { return x % 2 == 0; };
	auto evenLength = [](string s) { return s.length() % 2 == 0; };
	auto evenAndLength = [evens, evenLength](Record r) { return evens(r.num) && evenLength(r.str); };

	tstart = high_resolution_clock::now();
	filter(v1, evens);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	filter(v2, evenLength);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	filter(v3, evenAndLength);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// take
	label = "take";

	tstart = high_resolution_clock::now();
	take(10000, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	take(10000, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	take(10000, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// takeWhile
	label = "takeWhile";
	auto trueNumber = [](int x) { return true; };
	auto trueString = [](string s) { return true; };
	auto trueRecord = [](Record r) { return true; };

	tstart = high_resolution_clock::now();
	takeWhile(trueNumber, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	takeWhile(trueString, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	takeWhile(trueRecord, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// drop
	label = "drop";

	tstart = high_resolution_clock::now();
	drop(10000, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	drop(10000, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	drop(10000, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// dropWhile
	label = "dropWhile";
	auto falseNumber = [](int x) { return false; };
	auto falseString = [](string s) { return false; };
	auto falseRecord = [](Record r) { return false; };

	tstart = high_resolution_clock::now();
	dropWhile(falseNumber, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	dropWhile(falseString, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	dropWhile(falseRecord, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// span_container
	label = "span_container";
	auto bigNumber = [](int x) { return x > 1000000; };
	auto bigString = [](string s) { return s.length() > 25; };
	auto bigRecord = [bigNumber, bigString](Record r) { return bigNumber(r.num) && bigString(r.str); };

	tstart = high_resolution_clock::now();
	span_container(bigNumber, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	span_container(bigString, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	span_container(bigRecord, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// break_container
	label = "break_container";

	tstart = high_resolution_clock::now();
	break_container(bigNumber, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	break_container(bigString, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	break_container(bigRecord, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	// splitAt
	label = "splitAt";

	tstart = high_resolution_clock::now();
	splitAt(v1.size() / 2, v1);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	splitAt(v2.size() / 2, v2);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outStrings << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	splitAt(v3.size() / 2, v3);
	tend = high_resolution_clock::now();
	timespan = duration_cast<milliseconds>(tend - tstart).count();
	outRecs << label << ": " << timespan << "ms\n";

	outInts.close();
	outStrings.close();
	outRecs.close();
	
	return 0;
}