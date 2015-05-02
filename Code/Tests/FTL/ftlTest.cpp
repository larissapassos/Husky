#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "ftl/prelude.h"
#include "ftl/map.h"
#include "ftl/vector.h"
#include "ftl/string.h"
#include "ftl/concepts/foldable.h"
#include "ftl/type_traits.h"
#include "ftl/concepts/functor.h"
#include "ftl/concepts/common.h"
#include "ftl/concepts/zippable.h"

using namespace std;
using namespace chrono;
using namespace ftl;
using tp = high_resolution_clock::time_point;

// Files' path
const char* intFile = "../Input/ints.txt";
const char* stringFile = "../Input/strings.txt";
const char* recFile = "../Input/records.txt";

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

Record add_to_record(Record r) {
        return Record{ (r.num +10), r.str + "abab" };
}

int sumString(int x, string s) { return x + s.length(); }

int sumStringr(string s, int x) { return x + s.length(); }

int sumRecord(int x, Record r) { return x + r.num + r.str.length(); }

int sumRecordr(Record r, int x) { return x + r.num + r.str.length(); }

int main() {
    vector<int> v1;
    vector<string> v2;
    vector<Record> v3;

    // Populating the vectors
    readFile(intFile, v1);
    readFile(stringFile, v2);
    readFile(recFile, v3);

    vector<int> v4 = constructIntVector(v3);
    vector<string> v5 = constructStringVector(v3);
    vector<Record> v6 = constructRecordVector(v1, v2);


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

    auto addInt = [](int x) { return x + 10; };

    auto addString = [](string s) { return s + "abababab"; };

    auto addRecord = [](Record r) { return Record{ (r.num + 10), r.str + "abab" }; };

    auto concatRec = [](Record r1, Record r2) { return Record{ r1.num + r2.num, r1.str + r2.str }; };

    auto even = [](int x) { return x % 2 == 0; };

    auto evenLength = [](string s) { return s.length() % 2 == 0; };

    auto evenAndLength = [even, evenLength](Record r) { return even(r.num) && evenLength(r.str); };

    auto trueNumber = [](int x) { return true; };

    auto trueString = [](string s) { return true; };

    auto trueRecord = [](Record r) { return true; };

    auto bigNumber = [](int x) { return x > 1000000; };

    auto bigString = [](string s) { return s.length() > 25; };

    auto bigRecord = [bigNumber, bigString](Record r) { return bigNumber(r.num) && bigString(r.str); };

    auto createVecInt = [](int x) { return vector<int> {x}; };

    auto createVecString = [](string s) { return vector<string> {s}; };

    auto createVecRecord = [](Record r) { return vector<Record> {r}; };

    // Map a vector
    label = "map";

    // Construct fcpp Lists
    int si = v1.size();
    int ss = v2.size();
    int sr = v3.size();

    string prefix = "abababab";

    tstart = high_resolution_clock::now();;
    ftl::fmap(addInt, v1);
    tend = high_resolution_clock::now();
    auto timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::fmap(addString, v2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::fmap(addRecord, v3);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Foldl a vector
    label = "foldl";

    tstart = high_resolution_clock::now();;
    ftl::foldl(std::plus<int>(), 0, v1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::foldl(sumString, 0, v2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::foldl(sumRecord, 0, v3);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Foldr a vector
    label = "foldr";

    tstart = high_resolution_clock::now();;
    ftl::foldr(std::plus<int>(), 0, v1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::foldr(sumStringr, 0, v2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::foldr(sumRecordr, 0, v3);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Zip
    label = "zip";

    tstart = high_resolution_clock::now();
    ftl::zip(v1, v4);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::zip(v2, v5);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::zip(v3, v6);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // ZipWith
    label = "zipWith";

    tstart = high_resolution_clock::now();
    ftl::zipWith(std::plus<int>(), v1, v4);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::zipWith(std::plus<string>(), v2, v5);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::zipWith(concatRec, v3, v6);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    //concatMap
    label = "concatMap";

    tstart = high_resolution_clock::now();
    ftl::concatMap(createVecInt, v1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::concatMap(createVecString, v2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ftl::concatMap(createVecRecord, v3);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    outInts.close();
    outStrings.close();
    outRecs.close();

    return 0;
}
