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

template<typename T, typename V, typename Cont>
void printTuple(Hlist<pair<T, V>, Cont>& l) {
	cout << "[";
	for (int i = 0; i < l.size(); ++i) {
		auto tpl = l[i];
		cout << "(" << get<0>(tpl) << ", " << get<1>(tpl) << "),";
	}
	cout << "]\n";
}

int main() {
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Hlist<int, vector<int>> h{ v };
	addx add42{ 42 };

	cout << "hlist com vector: " << h << endl;

	Hlist<int, vector<int>> h2 = map(h, add42);
	cout << "hlist usando map: " << h2 << endl;

	auto h3 = zip(h, h2);
	cout << "zip: ";
	printTuple(h3);
}