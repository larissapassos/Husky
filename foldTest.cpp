#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include "functionalibrary.h"

using namespace functionalibrary;

int main() {

	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::ofstream file;
	file.open("tests.txt");

	int sum = foldl(vec.begin(), vec.end(), 0, std::plus<int>());

	file << sum << std::endl;

	file.close();

	return 0;
}