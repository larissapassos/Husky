#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <random>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

// Store the strings in the static area to avoid allocating heap space
const static size_t N = 500000;

// Class that encapsulates a pseudo-random generator
class Rand_Int {
public:
	Rand_Int(unsigned seed, int low, int high) :en{ seed }, dist{ low, high } {}
	int operator()() { return dist(en); }
private:
	minstd_rand en;
	uniform_int_distribution<int> dist;
};

// Custom class for testing
struct Record {
	int num;
	string str;
};

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

// method that generates a random string
string random_string(Rand_Int& rd, Rand_Int& rs) {
	auto randchar = [&rd]() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		int max_index = (sizeof(charset) - 1);
		return charset[rd() % max_index];
	};
	int length = rs();
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}

/* Method that populates a vector<strings> with random strings
* with length between 8 and 50.
*/
vector<string> generateStrings(Rand_Int& rd, Rand_Int& rs) {
	vector<string> c{ N };
	auto r = bind(random_string, rd, rs);
	generate(c.begin(), c.end(), r);
	return c;
}

// Method that populates an vector of random integers
vector<int> generateInts(Rand_Int& rd) {
	vector<int> c;
	c.resize(N);
	generate(c.begin(), c.end(), rd);
	return c;
}

Record random_record(Rand_Int& rd, Rand_Int& rs) {
	string s = random_string(rd, rs);
	int n = rd();
	Record r{ n, s };
	return r;
}

vector<Record> generateRecords(Rand_Int& rd, Rand_Int& rs) {
	vector<Record> c{ N };
	auto r = bind(random_record, rd, rs);
	generate(c.begin(), c.end(), r);
	return c;
}

int main() {
	// random seed
	unsigned seed = static_cast<unsigned>(system_clock::now().time_since_epoch().count());
	Rand_Int rd{ seed, 1, numeric_limits<int>::max() };
	Rand_Int rs{ seed, 8, 50 };

	// Populating the vectors
	vector<int> v1 = generateInts(rd);
	vector<string> v2 = generateStrings(rd, rs);
	vector<Record> v3 = generateRecords(rd, rs);

	// Print vectors to files
	ofstream ofint;
	ofint.open("ints.txt");
	ofint << v1;
	ofstream ofstrings;
	ofstrings.open("strings.txt");
	ofstrings << v2;
	ofstream ofrec;
	ofrec.open("records.txt");
	ofrec << v3;

	ofint.close();
	ofstrings.close();
	ofrec.close();
	return 0;
}