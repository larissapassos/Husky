#include <chrono>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <tuple>
#include "functionalibrary.h"

using namespace functionalibrary;

static int N = 10;

// Class that encapsulates a pseudo-random generator
class Rand_Int {
public:
	Rand_Int(unsigned seed, int low, int high) :en{ seed }, dist{ low, high } {}
	int operator()() { return dist(en); }
private:
	std::minstd_rand en;
	std::uniform_int_distribution<int> dist;
};

// Method to print a container
template <typename Cont>
void printCont(const Cont& c) {
	for (auto x : c) {
		std::cout << x << " ";
	}
	std::cout << "\n";
}

// Method to print a tuple container
template <typename Cont>
void printTupleCont(const Cont& c) {
	for (auto tpl : c) {
		std::cout << "(" << std::get<0>(tpl) << ", " << std::get<1>(tpl) << ") ";
	}
	std::cout << "\n";
}

// Method to fill a container
template <typename Cont>
void fillCont(Cont& c, Rand_Int& rd) {
	int size = (rd() % N);
	for (int i = 0; i < N; ++i) {
		c.push_back(rd() % 100);
	}
}

// Functor for testing
struct addx{
	addx(int x) :x(x) {}
	int operator()(int y) { return x + y; }

private:
	int x;
};


int main() {

	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vec2{ 1, 2, 3, 4, 5 };
	std::vector<bool> vec_true{ true, true, true, true, true };
	std::vector<bool> vec_false{ false, false, false, false, false };
	std::vector<bool> vec_mixed{ true, false, true, false, true };

	std::ofstream file;
	file.open("tests.txt");

	int sum = functionalibrary::sum(vec.begin(), vec.end(), 0);

	bool test_and_true = functionalibrary::and(vec_true.begin(), vec_true.end());
	bool test_and_false = functionalibrary::and(vec_false.begin(), vec_false.end());
	bool test_and_false2 = functionalibrary::and(vec_mixed.begin(), vec_mixed.end());

	bool test_or_true = functionalibrary::or(vec_true.begin(), vec_true.end());
	bool test_or_false = functionalibrary::or(vec_false.begin(), vec_false.end());
	bool test_or_true2 = functionalibrary::or(vec_mixed.begin(), vec_mixed.end());

	file << sum << std::endl;

	assert(test_and_true);
	assert(!test_and_false);
	assert(!test_and_false2);

	assert(test_or_true);
	assert(test_or_true2);
	assert(!test_or_false);

	file << functionalibrary::product(vec2.begin(), vec2.end(), 1);
	file << '\n';

	file << functionalibrary::product(vec2.begin(), vec2.end(), -1);
	file << '\n';

	file.close();

	// random seed
	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	Rand_Int rd{ seed, 1, std::numeric_limits<int>::max() };

	// Populating vector of ints
	std::vector<int> v1;
	fillCont(v1, rd);

	// Testing map
	std::cout << "v1: ";
	printCont(v1);
	addx add42{ 42 };
	std::cout << "Mapping v1 to add42: ";
	std::vector<int> v2 = map(v1, add42);
	printCont(v2);

	// Testing zip
	auto v3 = zip(v1, v2);
	std::cout << "zipping v1 and v2: ";
	printTupleCont(v3);

	return 0;
}