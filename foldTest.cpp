#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <functional>
#include "functionalibrary.h"

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

	return 0;
}