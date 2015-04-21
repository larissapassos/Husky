#include <iostream>     // std::cout
#include <vector>
#include <list>
#include "husky.h"

using namespace std;
using namespace husky;

int main() {
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int head = 0;
	vector<int> v2 = cons(head, v);
	cout << "constructor using cons: ";
	printCont(v2);
	auto v3 = concat(v, v2);
	cout << "concat: ";
	printCont(v3);
}
