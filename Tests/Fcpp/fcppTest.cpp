#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "prelude.h"
#include "list.h"
#include "lambda.h"

using namespace std;
using namespace chrono;
using namespace fcpp;
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

Record add_to_record(Record r) {
        return Record{ (r.num +10), r.str + "abab" };
}

int sumString(int x, string s) { return x + s.length(); }

int sumStringr(string s, int x) { return x + s.length(); }

int sumRecord(int x, Record r) { return x + r.num + r.str.length(); }

int sumRecordr(Record r, int x) { return x + r.num + r.str.length(); }

Record concatRec(Record r1, Record r2) { return Record{ r1.num + r2.num, r1.str + r2.str }; }

bool evenLength(string s) { return s.length() % 2 == 0; }

bool evenAndLength(Record r) { return even(r.num) && evenLength(r.str); }

bool trueNumber(int x) { return true; }

bool trueString(string s) { return true; }

bool trueRecord(Record r) { return true; }

bool bigNumber(int x) { return x > 1000000; }

bool bigString(string s) { return s.length() > 25; }

bool bigRecord(Record r) { return bigNumber(r.num) && bigString(r.str); }


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


    // Map a vector
    label = "map";

    // Construct fcpp Lists
    int si = v1.size();
    int ss = v2.size();
    int sr = v3.size();

    List<int> li;
    List<string> ls;
    List<Record> lr;

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    string prefix = "abababab";

    tstart = high_resolution_clock::now();;
    li = map(fcpp::plus(10), li);
    tend = high_resolution_clock::now();
    auto timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    ls = map(fcpp::plus(prefix), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    lr = map(ptr_to_fun(&add_to_record), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Foldl a vector
    label = "foldl";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    foldl(fcpp::plus, 0, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    foldl(ptr_to_fun(&sumString), 0, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    foldl(ptr_to_fun(&sumRecord), 0, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Foldr a vector
    label = "foldr";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    foldr(fcpp::plus, 0, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    foldr(ptr_to_fun(&sumStringr), 0, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    foldr(ptr_to_fun(&sumRecordr), 0, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Cons
    label = "cons";

    int hi = 0;
    string hs = "a";
    Record r { hi, hs };

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    cons(hi, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    cons(hs, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    cons(r, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Concat two vectors
    label = "concat2";

    vector<int> v4 = constructIntVector(v3);
    vector<string> v5 = constructStringVector(v3);
    vector<Record> v6 = constructRecordVector(v1, v2);

    List<int> li2;
    List<string> ls2;
    List<Record> lr2;

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);
    for (int i = 0; i < si; ++i) li2 = cons(v4[i], li2);
    for (int i = 0; i < ss; ++i) ls2 = cons(v5[i], ls2);
    for (int i = 0; i < sr; ++i) lr2 = cons(v6[i], lr2);

    tstart = high_resolution_clock::now();;
    cat(li, li2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    cat(ls, ls2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    cat(lr, lr2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // Concat a vector
    label = "concat1";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    List<List<int>> lti;

    for (int i = 0; i < 2; ++i) {
        List<int> aux;
        for (int j = 0; j < si; ++j) {
            aux = cons(v1[i], aux);
        }
        lti = cons(aux, lti);
    }

    List<List<string>> lts;

    for (int i = 0; i < 2; ++i) {
        List<string> aux;
        for (int j = 0; j < ss; ++j) {
            aux = cons(v2[i], aux);
        }
        lts = cons(aux, lts);
    }

    List<List<Record>> ltr;

    for (int i = 0; i < 2; ++i) {
        List<Record> aux;
        for (int j = 0; j < sr; ++j) {
            aux = cons(v3[i], aux);
        }
        ltr = cons(aux, ltr);
    }

    tstart = high_resolution_clock::now();;
    concat(lti);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    concat(lts);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    concat(ltr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // tail
    label = "tail";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    tail(li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    tail(ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    tail(lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // init
    label = "init";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    init(li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    init(ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    init(lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // at
    label = "at";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    at(li, length(li) - 1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    at(ls, length(ls) - 1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    at(lr, length(lr) - 1);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // reverse
    label = "reverse";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    //fcpp::reverse(li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    //fcpp::reverse(ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    //fcpp::reverse(lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // scanl a vector
    label = "scanl";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    scanl(fcpp::plus, 0, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    scanl(ptr_to_fun(&sumString), 0, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    scanl(ptr_to_fun(&sumRecord), 0, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // scanr a vector
    label = "scanr";

    // Construct fcpp Lists
    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    scanr(fcpp::plus, 0, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    scanr(ptr_to_fun(&sumStringr), 0, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    scanr(ptr_to_fun(&sumRecordr), 0, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // zip
    label = "zip";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    auto liz = zip(li, li2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    auto lsz = zip(ls, ls2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    auto lrz = zip(lr, lr2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // zipWith
    label = "zipWith";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    zipWith(fcpp::plus, li, li2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    zipWith(fcpp::plus, ls, ls2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    zipWith(ptr_to_fun(&concatRec), lr, lr2);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // unzip
    label = "unzip";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    unzip(liz);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    unzip(lsz);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    unzip(lrz);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // filter
    label = "filter";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::filter(even, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::filter(ptr_to_fun(&evenLength), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::filter(ptr_to_fun(&evenAndLength), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // take
    label = "take";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::take(10000, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::take(10000, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::take(10000, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // takeWhile
    label = "takeWhile";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::takeWhile(ptr_to_fun(&trueNumber), li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::takeWhile(ptr_to_fun(&trueString), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::takeWhile(ptr_to_fun(&trueRecord), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // drop
    label = "drop";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::drop(10000, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::drop(10000, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::drop(10000, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // dropWhile
    label = "dropWhile";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::dropWhile(ptr_to_fun(&trueNumber), li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::dropWhile(ptr_to_fun(&trueString), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::dropWhile(ptr_to_fun(&trueRecord), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // span
    label = "span";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::span(ptr_to_fun(&bigNumber), li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::span(ptr_to_fun(&bigString), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::span(ptr_to_fun(&bigRecord), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // break
    label = "break";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp::break_(ptr_to_fun(&bigNumber), li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::break_(ptr_to_fun(&bigString), ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::break_(ptr_to_fun(&bigRecord), lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    // splitAt
    label = "splitAt";

    for (int i = 0; i < si; ++i) li = cons(v1[i], li);
    for (int i = 0; i < ss; ++i) ls = cons(v2[i], ls);
    for (int i = 0; i < sr; ++i) lr = cons(v3[i], lr);

    tstart = high_resolution_clock::now();;
    fcpp:splitAt(si / 2, li);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outInts << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::splitAt(ss / 2, ls);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outStrings << label << ": " << timespan << "ms\n";

    tstart = high_resolution_clock::now();
    fcpp::splitAt(sr / 2, lr);
    tend = high_resolution_clock::now();
    timespan = duration_cast<milliseconds>(tend - tstart).count();
    outRecs << label << ": " << timespan << "ms\n";

    outInts.close();
    outStrings.close();
    outRecs.close();

    return 0;
}
