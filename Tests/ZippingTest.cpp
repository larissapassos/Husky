#include <iostream>     // std::cout
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <utility>
#include "husky.h"

using namespace std;
using namespace husky;

template <typename T, typename V>
void printTuple(pair<T, V> tpl) {
	cout << "(";
    printCont(get<0>(tpl));
    cout << ", ";
	printCont(get<1>(tpl));
	cout << ")" << endl;
}

template <typename T, typename V, typename W>
void printTuple(tuple<T, V, W> tpl) {
	cout << "(";
	printCont(get<0>(tpl));
	cout << ", ";
	printCont(get<1>(tpl));
	cout << ", ";
	printCont(get<2>(tpl));
	cout << ")" << endl;
}

template<typename Cont>
void printTupleCont(const Cont& l) {
	cout << "[ ";
	for (auto tpl : l) {
		cout << "(" << get<0>(tpl) << ", " << get<1>(tpl) << ", " << get<2>(tpl) << ") ";
	}
	cout << "]\n";
}

int main() {
	vector<int> v1 = { 1, 2, 3, 4, 5 };
	vector<string> v2 = { "a", "b", "c" };
	vector<int> v3 = { 6, 7, 8 };

	cout << "vector 1: ";
	printCont(v1);
	cout << "vector 2: ";
	printCont(v2);
	cout << "vector 3: ";
	printCont(v3);

	auto v4 = zip3(v1, v2, v3);
	cout << "usando zip3: ";
	printTupleCont(v4);

	auto v5 = zipWith(std::plus<int>(), v1, v3);
	cout << "usando zipWith: ";
	printCont(v5);

	auto v6 = zipWith3([](int x, string s, int y) -> int { return x + s.length() + y; }, v1, v2, v3);
	cout << "usando zipWith3: ";
	printCont(v6);

	auto p1 = unzip(zip(v1, v2));
	cout << "usando unzip em (v1,v2): ";
	printTuple(p1);

	auto p2 = unzip3(v4);
	cout << "usando unzip3 em (v1, v2, v3): ";
	printTuple(p2);
}