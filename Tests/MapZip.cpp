#include <iostream>     // std::cout
#include <vector>
#include <list>
#include "husky.h"

using namespace std;
using namespace husky;

struct addx{
	addx(int x) :x(x) {}
	int operator()(int y) { return x + y; }

private:
	int x;
};

template<typename Cont>
void printTuple(const Cont& l) {
	cout << "[ ";
	for (auto tpl : l) {
		cout << "(" << get<0>(tpl) << ", " << get<1>(tpl) << ") ";
	}
	cout << "]\n";
}

int main() {
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	addx add42{ 42 };

	cout << "hector: ";
	printCont(v);

	vector<int> v2 = map(v, add42);
	cout << "usando map: ";
	printCont(v2);

	auto v3 = zip(v, v2);
	cout << "zip: ";
	printTuple(v3);
}
