#include <chrono>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>
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

	std::ofstream file;
	file.open("tests.txt");

	int sum = foldl(vec.begin(), vec.end(), 0, std::plus<int>());

	file << sum << std::endl;

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