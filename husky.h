#ifndef _HUSKY_H
#define _HUSKY_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

namespace husky {

	template<typename Cont>
	Cont concat(const Cont& l1, const Cont& l2) {
		Cont result{ l1 };
		for (auto elm : l2) {
			result.push_back(elm);
		}
		return result;
	}

	// Special implementation of concat for a single container.
	// Concatenates every element of the list into a single list
	template<typename Cont>
	Cont concat(const Cont& l) {
		Cont result{ l };
		for (auto elm : l) result.push_back(elm);
		//return concat(new Cont(), l);
		return result;
	}

	template<typename Cont>
	void printCont(const Cont& l) {
		std::cout << "[ ";
		for (auto elm : l) {
			std::cout << elm << " ";
		}
		std::cout << "]\n";
	}

	template <typename T, typename Cont>
	Cont cons(T head, const Cont& tail) {
		Cont newList{ tail };
		auto it = newList.begin();
		newList.insert(it, head);
		return newList;
	}

	// Iterator versions of fold functions
	/*template<typename Function, typename Iterator, typename T>
	T foldl(Iterator first, Iterator last, T init, Function f) { return std::accumulate(first, last, init, f); }

	template<typename Function, typename Iterator>
	typename Iterator::value_type foldl1(Iterator first, Iterator last, Function f) {
		typename Iterator::value_type init = *first;
		std::advance(first, 1);

		while (first != last) {
			init = f(init, *first);
			std::advance(first, 1);
		}

		return init;
	}

	template<typename Iterator, typename T>
	T sum(Iterator first, Iterator last, T init) { return std::accumulate(first, last, init); }

	template<typename Iterator, typename T>
	T product(Iterator first, Iterator last, T init) { return std::accumulate(first, last, init, std::multiplies<T>()); }

	template<typename Iterator>
	bool and_(Iterator first, Iterator last) { return std::accumulate(first, last, true, std::logical_and<bool>()); }

	template<typename Iterator>
	bool or_(Iterator first, Iterator last) { return std::accumulate(first, last, false, std::logical_or<bool>()); }*/

	// Container version of fold functions

	// Returns a fold of the given container, with a given initial value and a given function
	template<typename Function, typename Cont, typename T>
	T foldl(const Cont& container, T init, Function f) { return std::accumulate(container.begin(), container.end(), init, f); }

	// Returns a fold of a given container with the given function with no initial values
	template<typename Function, typename Cont>
	typename Cont::iterator::value_type foldl1(Cont& container, Function f) {
		using it = typename Cont::iterator;

		it first = container.begin();
		it last = container.end();
		it::value_type init = *first;
		std::advance(first, 1);

		while (first != last) {
			init = f(init, *first);
			std::advance(first, 1);
		}

		return init;
	}

	// Returns the summation of the values in the given container with the given initial value
	template<typename Cont, typename T>
	T sum(const Cont& container, T init) { return std::accumulate(container.begin(), container.end(), init); }

	// Returns the product of the values in the given container with the given initial value
	template<typename Cont, typename T>
	T product(const Cont& container, T init) { return std::accumulate(container.begin(), container.end(), init, std::multiplies<T>()); }

	// Returns a logical and operation for every value in the given container
	template<typename Cont>
	bool and_(const Cont& container) { return std::accumulate(container.begin(), container.end(), true, std::logical_and<bool>()); }

	// Returns a logical or operation for every value in the given container
	template<typename Cont>
	bool or_(const Cont& container) { return std::accumulate(container.begin(), container.end(), false, std::logical_or<bool>()); }

	// Returns true if any value in the given container fits a given predicate
	template<typename Cont, typename Pred>
	bool any_(const Cont& container, Pred predicate) { return std::any_of(container.begin(), container.end(), predicate); }

	// Returns true if all values in the given container fit a given predicate
	template<typename Cont, typename Pred>
	bool all_(const Cont& container, Pred predicate) { return std::all_of(container.begin(), container.end(), predicate); }

	// Returns the maximum value in a given container, using the default comparison operators
	template<typename Cont>
	typename Cont::iterator::value_type maximum_(const Cont& container) { return *(std::max_element(container.begin(), container.end())); }

	// Returns the maximum value in a given container, using a user-defined comparison functinon
	template<typename Cont, typename Comp>
	typename Cont::iterator::value_type maximum_(const Cont& container) { return *(std::max_element(container.begin(), container.end(), comp)); }

	// Returns the minimum value in a given container, using the default comparison operators
	template<typename Cont>
	typename Cont::iterator::value_type minimum_(const Cont& container) { return *(std::min_element(container.begin(), container.end())); }

	// Returns the minimum value in a given container, using the default comparison operators
	template<typename Cont, typename Comp>
	typename Cont::iterator::value_type minimum_(const Cont& container) { return *(std::min_element(container.begin(), container.end(), comp)); }

	// Note: All function names above end in _ dure to name conflict. I figured out that that happened on ayo's computer because he was using namespaces, whereas
	// I wasn't when running my tests. Talk about function naming. (Vinicius)

	template <typename Cont, typename UnaryOperation>
	Cont map(const Cont& l, UnaryOperation f) {
		Cont l2;
		for (auto elm : l) {
			auto new_elm = f(elm);
			l2.push_back(new_elm);
		}
		return l2;
	}

	// Maps a given container with a given function and then concatenate the results
	template<typename Cont, typename Function>
	Cont concatMap(const Cont& container, Function f) { return concat(map(container, f)); }

	template <typename Cont1, typename Cont2>
	std::vector<std::pair<typename Cont1::value_type, typename Cont2::value_type>> zip(const Cont1& l1, const Cont2& l2) {
		std::vector<std::pair<typename Cont1::value_type, typename Cont2::value_type>> result;
		int len = std::min(l1.size(), l2.size());
		for (int i = 0; i < len; ++i) {
			auto new_elm = std::make_pair(l1[i], l2[i]);
			result.push_back(new_elm);
		}
		return result;
	}

	// Breaks a string up into a list of strings at newline characters.
	std::vector<std::string> lines(const std::string& str) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string curr;

		while (std::getline(ss, curr)) result.push_back(curr);

		return result;
		
	}

	// Inverse to lines function. Using vector only since lines returns a vector.
	std::string unlines(const std::vector<std::string>& vec) {
		std::string result;
		for (auto elm : vec) result.append(elm + '\n');
		return result;
	}

	// Breaks a string up into a list of strings at whitespaces.
	std::vector<std::string> words(const std::string& str) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string curr;

		while (std::getline(ss, curr, ' ')) result.push_back(curr);

		return result;

	}

	// Inverse to words function. Using vector only since words returns a vector.
	std::string unwords(const std::vector<std::string>& vec) {
		std::string result;
		for (auto elm : vec) result.append(elm + ' ');
		return result;
	}

	//filter function returns a list with filtered data
	template<typename T, typename Cont, typename Predicate>
	Cont filter(const Cont& data, Predicate good){

		auto filteredData(data);  	//Use copy constructor to copy data set

		filteredData.erase(remove_if(filteredData.begin(), filteredData.end(),
			[&](typename T::value_type &x) { return !good(x); }), filteredData.end());

		return filteredData;
	}
}

#endif /* _HUSKY_H */
