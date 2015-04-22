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
struct add_x {
	add_x(int x) : x(x) {}
	int operator()(int y) { return x + y; }

private:
	int x;
};

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
	int head = 0;
	string h = "a";
	Record r { head, h };

	tstart = high_resolution_clock::now();
	cons(head, v1);
	tend = high_resolution_clock::now();
	auto timespan = duration_cast<milliseconds>(tend - tstart).count();
	outInts << label << ": " << timespan << "ms\n";

	tstart = high_resolution_clock::now();
	cons(h, v2);
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

	outInts.close();
	outStrings.close();
	outRecs.close();
	
	return 0;
}