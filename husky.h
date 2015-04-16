#ifndef _HUSKY_H
#define _HUSKY_H

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <tuple>
#include <vector>

namespace husky {

	// concat - concatenates two containers and returns the result.
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

	// printCont - print a container
	template<typename Cont>
	void printCont(const Cont& l) {
		std::cout << "[ ";
		for (auto elm : l) {
			std::cout << elm << " ";
		}
		std::cout << "]\n";
	}

	// cons - haskell list constructor, receives a head and a tail list, and returns a new list consisting of (head:tail)
	template<typename Cont>
	Cont cons(typename Cont::value_type head, const Cont& tail) {
		Cont newList{ tail };
		auto it = newList.begin();
		newList.insert(it, head);
		return newList;
	}

	// head - receives a container and returns the first element
	template<typename Cont>
	typename Cont::value_type head(const Cont& l) { return l.front(); }

	// last - receives a container and returns the last element
	template<typename Cont>
	typename Cont::value_type last(const Cont& l) { return l.back(); }

	// tail - receives a container and returns the list except for the first element
	template<typename Cont>
	Cont tail(const Cont& l) {
		Cont t{ l };
		t.erase(t.begin());
		return t;
	}

	// init - receives a container and returns the list except for the last element
	template<typename Cont>
	Cont init(const Cont& l) {
		Cont t{ l };
		t.pop_back();
		return t;
	}

	// is_null - receives a container and returns wether it is empty or not
	template<typename Cont>
	bool is_null(const Cont& l) { return l.empty(); }

	// length - receives a container and returns its size
	template<typename Cont>
	unsigned int length(const Cont& l) { return l.size(); }

	// at - receives a container and a index and return the element at this index
	template<typename Cont>
	typename Cont::value_type at(const Cont& l, int index) {
		int i = 0;
		if (static_cast<unsigned>(index) >= l.size()) {
			return l.back();
		}
		for (auto elm : l) {
			if (i == index) {
				return elm;
			}
			++i;
		}
		return l.front();
	}

	// reverse - receives a container and returns a new container with the same elements in reverse order
	template<typename Cont>
	Cont reverse(const Cont& l) {
		Cont result;
		for (auto rit = l.crbegin(); rit != l.crend(); ++rit) {
			result.push_back(*rit);
		}
		return result;
	}

	// Returns a fold of the given container, with a given initial value and a given function
	template<typename Function, typename Cont, typename T>
	T foldl(const Cont& container, T init, Function f) { return std::accumulate(container.begin(), container.end(), init, f); }

	// Returns a fold of a given container with the given function with no initial values
	template<typename Function, typename Cont>
	typename Cont::iterator::value_type foldl1(Cont& container, Function f) {
		using it = typename Cont::iterator;

		it first = container.begin();
		it last = container.end();
		typename it::value_type init = *first;
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
	typename Cont::iterator::value_type maximum_(const Cont& container, Comp comp) { return *(std::max_element(container.begin(), container.end(), comp)); }

	// Returns the minimum value in a given container, using the default comparison operators
	template<typename Cont>
	typename Cont::iterator::value_type minimum_(const Cont& container) { return *(std::min_element(container.begin(), container.end())); }

	// Returns the minimum value in a given container, using a user-defined comparison functinon
	template<typename Cont, typename Comp>
	typename Cont::iterator::value_type minimum_(const Cont& container, Comp comp) { return *(std::min_element(container.begin(), container.end(), comp)); }

	// Note: All function names above end in _ dure to name conflict. I figured out that that happened on ayo's computer because he was using namespaces, whereas
	// I wasn't when running my tests. Talk about function naming. (Vinicius)

	// scanl - similar to foldl, but returns a vector of successive reduced values from the left
	template<typename Cont, typename T, typename Function>
	std::vector<T> scanl(Function f, T init, const Cont& l) {
		std::vector<T> result;
		result.push_back(init);
		for (auto elm : l) {
			init = f(init, elm);
			result.push_back(init);
		}
		return result;
	}

	// scanl1 - a variant of scanl that has no starting value argument
	template<typename Cont, typename Function>
	std::vector<typename Cont::value_type> scanl1(Function f, const Cont& l) {
		std::vector<typename Cont::value_type> result;
		auto first = l.begin();
		auto last = l.end();
		auto init = *first;
		result.push_back(init);
		std::advance(first, 1);
		while (first != last) {
			init = f(init, *first);
			result.push_back(init);
			std::advance(first, 1);
		}
		return result;
	}

	// scanr - right-to-left dual of scanl
	template<typename Cont, typename T, typename Function>
	std::vector<T> scanr(Function f, T init, const Cont& l) {
		std::vector<T> result;
		result.push_back(init);
		for (auto rit = l.crbegin(); rit != l.crend(); ++rit) {
			init = f(init, *rit);
			result.push_back(init);
		}
		return reverse(result);
	}

	//scanr1 - a variant of scanr that has no starting value argument
	template<typename Cont, typename Function>
	std::vector<typename Cont::value_type> scanr1(Function f, const Cont& l) {
		std::vector<typename Cont::value_type> result;
		auto first = l.crbegin();
		auto last = l.crend();
		auto init = *first;
		result.push_back(init);
		std::advance(first, 1);
		while (first != last) {
			init = f(init, *first);
			result.push_back(init);
			std::advance(first, 1);
		}
		return reverse(result);
	}

	// map - receives a container and a unary function and returns a new container with the result of the function applied to every original element
	template <typename Cont, typename Function>
	std::vector<typename std::result_of<Function(typename Cont::value_type)>::type> map(const Cont& l, Function f) {
		using V = typename std::result_of<Function(typename Cont::value_type)>::type;
		std::vector<V> l2;
		for (auto elm : l) {
			auto new_elm = f(elm);
			l2.push_back(new_elm);
		}
		return l2;
	}

	// Maps a given container with a given function and then concatenate the results
	template<typename Cont, typename Function>
	auto concatMap(const Cont& container, Function f) -> decltype(map(container, f)) { return concat(map(container, f)); }

	// zip - receives two containers and returns a vector of pairs formed by the containers' elements
	template <typename Cont1, typename Cont2>
	std::vector<std::pair<typename Cont1::value_type, typename Cont2::value_type>> zip(const Cont1& l1, const Cont2& l2) {
		std::vector<std::pair<typename Cont1::value_type, typename Cont2::value_type>> result;
		int len = std::min(l1.size(), l2.size());
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		for (int i = 0; i < len; ++i) {
			auto new_elm = std::make_pair(*it1, *it2);
			result.push_back(new_elm);
			++it1;
			++it2;
		}
		return result;
	}

	// zip3 - takes three containers and returns a list of triples, analogous to zip
	template <typename Cont1, typename Cont2, typename Cont3>
	std::vector<std::tuple<typename Cont1::value_type, typename Cont2::value_type, typename Cont3::value_type>> zip3(const Cont1& l1, const Cont2& l2, const Cont3& l3) {
		std::vector<std::tuple<typename Cont1::value_type, typename Cont2::value_type, typename Cont3::value_type>> result;
		int len = std::min(l1.size(), std::min(l2.size(), l3.size()));
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		auto it3 = l3.begin();
		for (int i = 0; i < len; ++i) {
			auto new_tpl = std::make_tuple(*it1, *it2, *it3);
			result.push_back(new_tpl);
			++it1;
			++it2;
			++it3;
		}
		return result;
	}

	// zipWith - generalises zip by zipping with the function given as the first argument, instead of a tupling function
	template<typename Function, typename Cont1, typename Cont2>
	std::vector<typename std::result_of<Function(typename Cont1::value_type, typename Cont2::value_type)>::type> zipWith(Function f, const Cont1& l1, const Cont2& l2) {
		using V = typename std::result_of<Function(typename Cont1::value_type, typename Cont2::value_type)>::type;
		std::vector<V> result;
		int len = std::min(l1.size(), l2.size());
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		for (int i = 0; i < len; ++i) {
			auto new_elm = f(*it1, *it2);
			result.push_back(new_elm);
			++it1;
			++it2;
		}
		return result;
	}

	//zipWith3 - takes a function which combines three elements, as well as three lists and returns a list of their point-wise combination
	template<typename Function, typename Cont1, typename Cont2, typename Cont3>
	std::vector<typename std::result_of<Function(typename Cont1::value_type, typename Cont2::value_type, typename Cont3::value_type)>::type> zipWith3(Function f, const Cont1& l1, const Cont2& l2, const Cont3& l3) {
		using V = typename std::result_of<Function(typename Cont1::value_type, typename Cont2::value_type, typename Cont3::value_type)>::type;
		std::vector<V> result;
		int len = std::min(l1.size(), std::min(l2.size(), l3.size()));
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		auto it3 = l3.begin();
		for (int i = 0; i < len; ++i) {
			auto new_elm = f(*it1, *it2, *it3);
			result.push_back(new_elm);
			++it1;
			++it2;
			++it3;
		}
		return result;
	}

	// unzip - transforms a list of pairs into a list of first components and a list of second components.
	template<typename T, typename V>
	std::pair<std::vector<T>, std::vector<V>> unzip(const std::vector<std::pair<T, V>>& l) {
		std::vector<T> first;
		std::vector<V> second;
		for (auto tpl : l) {
			first.push_back(std::get<0>(tpl));
			second.push_back(std::get<1>(tpl));
		}
		auto p = make_pair(first, second);
		return p;
	}

	// unzip3 - takes a list of triples and returns three lists
	template<typename T, typename V, typename W>
	std::tuple<std::vector<T>, std::vector<V>, std::vector<W>> unzip3(const std::vector<std::tuple<T, V, W>>& l) {
		std::vector<T> first;
		std::vector<V> second;
		std::vector<W> third;
		for (auto tpl : l) {
			first.push_back(std::get<0>(tpl));
			second.push_back(std::get<1>(tpl));
			third.push_back(std::get<2>(tpl));
		}
		auto p = make_tuple(first, second, third);
		return p;
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


	//Function take: take n, applied to a list xs, returns the prefix of xs of length n, 
	//or xs itself if n > length xs:
	template <typename Value, typename Container>
	void take(Value v, const Container& c)
	{
		int x = 0;
		std::cout << std::endl;
		for (auto it = std::begin(c); it != std::end(c); ++it){

			if (x < v) std::cout << *it;
			x++;
		}
	}


	//Function takeWhile: applied to a predicate p and a list xs, 
	//returns the longest prefix (possibly empty) of xs of elements that satisfy p:
	template <typename Predicate, typename Container>
	void takeWhile(Predicate good, const Container& c)
	{
		std::cout << "\n";
		for (auto it = std::begin(c); it != std::end(c); ++it){

			if (good(*it)){
				std::cout << *it;
			}
			else{
				break;
			}
		}
	}


	//Function drop: drop n xs returns the suffix of xs after the first n elements,
	//or [] if n > length xs:
	template <typename Value, typename Container>
	void drop(Value v, const Container& c)
	{
		int x = 0;
		std::cout << std::endl;
		for (auto it = std::begin(c); it != std::end(c); ++it){

			if (x >= v) std::cout << *it;
			x++;
		}
	}



	//Function dropWhile: dropWhile p xs returns the suffix remaining after takeWhile p xs:
	template <typename Predicate, typename Container>
	void dropWhile(Predicate good, const Container& c)
	{
		std::cout << "\n";
		int x = 0;

		for (auto it = std::begin(c); it != std::end(c); ++it){

			if (!good(*it) || x == 1){
				std::cout << *it;
				x = 1;
			}
			else{
				if (x == 1) std::cout << *it;
			}
		}
	}



	//Function Composition  Haskel definition:  (.) :: (b -> c) -> (a -> b) -> a -> c 
	/*template<typename F, typename G>
	decltype(auto)compose(F&& f, G&& g)
	{
		return[=](auto x){return f(g(x)); };

	}*/


}

#endif /* _HUSKY_H */
