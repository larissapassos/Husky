#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <functional>
#include "husky.h"
#include <cstring>
#include <string>

bool isOdd(int i) { return ((i % 2) == 1); }

int main() {
	using namespace std::placeholders;

	std::vector<int> vec{ 2, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vec2{ 1, 2, 3, 4, 5 };
	std::vector<int> vecd{ 8, 4, 2 };
	std::vector<bool> vec_true{ true, true, true, true, true };
	std::vector<bool> vec_false{ false, false, false, false, false };
	std::vector<bool> vec_mixed{ true, false, true, false, true };

	std::ofstream file;
	file.open("tests.txt");

	int sum = husky::sum(vec, 0);

	bool test_and_true = husky::and_(vec_true);
	bool test_and_false = husky::and_(vec_false);
	bool test_and_false2 = husky::and_(vec_mixed);

	bool test_or_true = husky::or_(vec_true);
	bool test_or_false = husky::or_(vec_false);
	bool test_or_true2 = husky::or_(vec_mixed);

	file << sum << std::endl;

	int x = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
	int testSumFoldl1 = husky::foldl1(vec, std::multiplies<int>());
	int testSumFold2 = husky::foldr1(vec, std::multiplies<int>());
	int testDivFold = husky::foldl1(vecd, std::divides<int>());
	int testDivFold2 = husky::foldr1(vecd, std::divides<int>());

	file << testSumFoldl1 << std::endl;
	file << testSumFold2 << std::endl;
	file << "div" << std::endl;
	file << testDivFold << std::endl;
	file << testDivFold2 << std::endl;

	//auto t2 = std::bind(std::equal_to<int>(), 2, _2);
	bool any_of_ = husky::any_(vec, [&](int x) { return x == 2; });
	bool all_of_ = husky::all_(vec, [&](int x) { return x < 42; });
	int max_vec1 = husky::maximum_(vec);
	int min_vec1 = husky::minimum_(vec);

	bool isElem = husky::elem(2, vec);
	bool notElem = husky::notElem(80, vec);

	assert(isElem);
	assert(notElem);
	assert(min_vec1 == 2);
	assert(max_vec1 == 10);
	assert(all_of_);
	assert(any_of_);
	assert(testSumFoldl1 == x);
	assert(test_and_true);
	assert(!test_and_false);
	assert(!test_and_false2);

	assert(test_or_true);
	assert(test_or_true2);
	assert(!test_or_false);

	file << husky::product(vec2, 1);
	file << '\n';

	file << husky::product(vec2, -1);
	file << '\n';

	std::string phrase = "Testing\nlines\nimplementation.";
	std::vector<std::string> res = husky::lines(phrase);

	for (auto i : res) file << i << " ";
	file << std::endl;

	std::string phrase_back = husky::unlines(res);

	file << phrase_back;


	std::string phrase2 = "Testing words implementation.";
	std::vector<std::string> res2 = husky::words(phrase2);

	for (auto i : res2) file << i;
	file << std::endl;

	std::string phrase2_back = husky::unwords(res2);

	file << phrase2_back;

	std::vector<int> taste = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	//bool testFilter = husky::filter(vec, ([](int x) { return x < 5; }));
	//bool testFilter = husky::filter(taste, isOdd);
	file.close();

	return 0;
}