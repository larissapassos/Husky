#include <iostream>     // std::cout
#include <vector>
#include <list>
#include <string>
#include "husky.h"

using namespace std;
using namespace husky;

int main() {
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << "vector: ";
	printCont(v);

	vector<int> v2 = scanl(std::plus<int>(), 0, v);
	cout << "usando scanl: ";
	printCont(v2);

	auto v3 = scanl1(std::plus<int>(), v);
	cout << "usando scanl1: ";
	printCont(v3);
}