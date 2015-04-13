#include <iostream>     // std::cout
#include <vector>
#include <list>
#include "husky.h"

using namespace std;
using namespace husky;

int main() {
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int head = 0;
	Hlist<int, vector<int>> h;
	Hlist<int, vector<int>> h2 { v };
	Hlist<int, vector<int>> h3{ head };

	cout << "hlist1 (vazia): " << h << endl;
	cout << "hlist com vector: " << h2 << endl;
	cout << "hlist com head: " << h3 << endl;

	Hlist<int, vector<int>> h4 = cons(head, h2);
	cout << "hlist usando cons: " << h4 << endl;
	h4.add_head(-1);
	cout << "add_head: " << h4 << endl;
	h4.add_tail(10);
	cout << "add_tail: " << h4 << endl;
	h4.remove_head();
	cout << "remove_head: " << h4 << endl;
	h4.remove_tail();
	cout << "remove_tail: " << h4 << endl;

	h3 += h2;
	cout << "concat: " << h3 << endl;
}
