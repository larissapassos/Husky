#include <iostream>     // std::cout
#include <vector>
#include <list>
#include <string>
#include "husky.h"

using namespace std;
using namespace husky;

int main() {
	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << "vector: ";
	printCont(v);

	int h = head(v);
	int l = last(v);
	cout << "head: " << h << "\tlast: " << l << endl;

	vector<int> v2 = tail(v);
	cout << "tail: ";
	printCont(v2);

	vector<int> v3 = init(v);
	cout << "init: ";
	printCont(v3);

	int at5 = at(v, 5);
	cout << "sixth element: " << at5 << endl;

	vector<int> v4 = reverse(v);
	cout << "reverse: ";
	printCont(v4);
}
