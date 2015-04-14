#ifndef _HUSKY_H
#define _HUSKY_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace husky {	

	template<typename Cont>
	Cont concat (const Cont& l1, const Cont& l2) {
		Cont result{ l1 };
		for (auto elm : l2) {
			result.push_back(elm);
		}
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

	/*
	template<typename Function, typename Iterator, typename T>
	T foldl(Iterator first, Iterator last, T init, Function f) { return std::accumulate(first, last, init, f); }

	template<typename Iterator, typename T>
	T sum(Iterator first, Iterator last, T init) { return std::accumulate(first, last, init); }

	template<typename Iterator, typename T>
	T product(Iterator first, Iterator last, T init) { return std::accumulate(first, last, init, std::multiplies<T>()); }

	template<typename Iterator>
	bool and_(Iterator first, Iterator last) { return std::accumulate(first, last, true, std::logical_and<bool>()); }

	template<typename Iterator>
	bool or_(Iterator first, Iterator last) { return std::accumulate(first, last, false, std::logical_or<bool>()); }
	*/

	template <typename Cont, typename UnaryOperation>
	Cont map(const Cont& l, UnaryOperation f) {
		Cont l2;
		for (auto elm : l) {
			auto new_elm = f(elm);
			l2.push_back(new_elm);
		}
		return l2;
	}

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
