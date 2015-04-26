#ifndef _HUSKY_H
#define _HUSKY_H

#include <algorithm>
#include <cstring>
#include <functional>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace husky {

	/* --------------------------------- */
	/* List manipulation functions below */
	/* --------------------------------- */

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

	/* -------------------------------- */
	/* Standard and Special Folds Below */
	/* -------------------------------- */

	// Returns a fold of the given container, with a given initial value and a given function
	template<typename Function, typename Cont, typename T>
	T foldl(const Cont& container, T init, Function f) {
		return std::accumulate(container.begin(), container.end(), init, f);
	}

	// Returns a fold of a given container with the given function with no initial values
	template<typename Function, typename Cont>
	typename Cont::value_type foldl1(const Cont& container, Function f) {
		auto first = container.cbegin();
		auto last = container.cend();
		auto init = *first;
		std::advance(first, 1);

		return std::accumulate(first, last, init, f);
	}

	// foldr, applied to a binary operator, a starting value (typically the right-identity of the operator), and a list, 
	// reduces the list using the binary operator, from right to left:
	template<typename Function, typename Cont, typename T>
	T foldr(const Cont& container, T init, Function f) {

		for (auto rit = container.crbegin(); rit != container.crend(); ++rit) {
			init = f(init, *rit);
		}

		return init;
	}

	// foldr1 - a variant of foldr that has no starting value argument, and thus must be applied to non-empty lists.
	template<typename Function, typename Cont>
	typename Cont::value_type foldr1(const Cont& container, Function f) {
		auto first = container.crbegin();
		auto last = container.crend();
		auto init = *first;
		std::advance(first, 1);

		return std::accumulate(first, last, init, f);
	}

	// sum - returns the summation of the values in the given container with the given initial value
	template<typename Cont, typename T>
	T sum(const Cont& container, T init) {
		return std::accumulate(container.begin(), container.end(), init);
	}

	// product - eturns the product of the values in the given container with the given initial value
	template<typename Cont, typename T>
	T product(const Cont& container, T init) {
		return std::accumulate(container.begin(), container.end(), init, std::multiplies<T>());
	}

	// and_fold - returns a logical and operation for every value in the given container
	template<typename Cont>
	bool and_fold(const Cont& container) {
		return std::accumulate(container.begin(), container.end(), true, std::logical_and<bool>());
	}

	// or_fold - returns a logical or operation for every value in the given container
	template<typename Cont>
	bool or_fold(const Cont& container) {
		return std::accumulate(container.begin(), container.end(), false, std::logical_or<bool>());
	}

	// any_fold - returns true if any value in the given container fits a given predicate
	template<typename Cont, typename Pred>
	bool any_fold(const Cont& container, Pred predicate) {
		return std::any_of(container.begin(), container.end(), predicate);
	}

	// all_fold - returns true if all values in the given container fit a given predicate
	template<typename Cont, typename Pred>
	bool all_fold(const Cont& container, Pred predicate) {
		return std::all_of(container.begin(), container.end(), predicate);
	}

	/* ------------------------------------ */
	/* Maximum and minimum functions below */
	/* ------------------------------------ */

	// maximum_of - returns the maximum value in a given container, using the default comparison operators
	template<typename Cont>
	typename Cont::iterator::value_type maximum_of(const Cont& container) {
		return *(std::max_element(container.begin(), container.end()));
	}

	// maximum_of - returns the maximum value in a given container, using a user-defined comparison functinon
	template<typename Cont, typename Comp>
	typename Cont::iterator::value_type maximum_of(const Cont& container, Comp comp) {
		return *(std::max_element(container.begin(), container.end(), comp));
	}

	// minimum_of - returns the minimum value in a given container, using the default comparison operators
	template<typename Cont>
	typename Cont::iterator::value_type minimum_of(const Cont& container) {
		return *(std::min_element(container.begin(), container.end()));
	}

	// minimum_of - eturns the minimum value in a given container, using a user-defined comparison functinon
	template<typename Cont, typename Comp>
	typename Cont::iterator::value_type minimum_of(const Cont& container, Comp comp) {
		return *(std::min_element(container.begin(), container.end(), comp));
	}

	/* -------------------- */
	/* Scan functions below */
	/* -------------------- */

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

	/* ---------- */
	/* Maps below */
	/* ---------- */

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

	// concatMap - maps a given container with a given function and then concatenate the results
	template<typename Cont, typename Function>
	auto concatMap(const Cont& container, Function f) -> decltype(map(container, f)) {
		return concat(map(container, f));
	}

	/* ------------------- */
	/* Zip functions below */
	/* ------------------- */

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
		auto p = std::make_pair(first, second);
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
		auto p = std::make_tuple(first, second, third);
		return p;
	}

	/* ----------------------------------- */
	/* String manipulation functions below */
	/* ----------------------------------- */

	// lines - breaks a string up into a list of strings at newline characters. The resulting strings do not contain newlines.
	// Returns a vector of strings.
	std::vector<std::string> lines(const std::string& str) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string curr;

		while (std::getline(ss, curr)) result.push_back(curr);

		return result;

	}

	// unlines - an inverse operation to lines. It joins lines, after appending a terminating newline to each.
	// Returns a single string.
	std::string unlines(const std::vector<std::string>& vec) {
		std::string result;
		for (auto elm : vec) result.append(elm + '\n');
		return result;
	}

	// words - breaks a string up into a list of words, which were delimited by white space.
	// Returns a vector of strings.
	std::vector<std::string> words(const std::string& str) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string curr;

		while (std::getline(ss, curr, ' ')) result.push_back(curr);

		return result;

	}

	// unwords - an inverse operation to words. It joins words with separating spaces.
	// Returns a single string.
	std::string unwords(const std::vector<std::string>& vec) {
		std::string result;
		for (auto elm : vec) result.append(elm + ' ');
		return result;
	}


	/* --------------------------------------------- */
	/* List searching and sublisting functions below */
	/* --------------------------------------------- */

	//filter - returns a list with data filtered by a given predicate
	template<typename Cont, typename Predicate>
	Cont filter(const Cont& data, Predicate good){

		auto filteredData(data);  	//Use copy constructor to copy data set

		filteredData.erase(remove_if(filteredData.begin(), filteredData.end(),
			[&](typename Cont::value_type &x) { return !good(x); }), filteredData.end());

		return filteredData;
	}


	//Function take: take v, applied to a list c, returns the prefix of c of length v, 
	//or c itself if v > length c:
	template <typename Value, typename Cont>
	std::vector<typename Cont::value_type> take(Value v, const Cont& c) {
		std::vector<typename Cont::value_type> prefix;

		if ((unsigned)v > c.size()) v = c.size();

		for (auto it = std::begin(c); it != std::begin(c) + v; ++it) {
			prefix.push_back(*it);
		}

		return prefix;
	}


	//Function takeWhile: applied to a predicate p and a list c, 
	//returns the longest prefix (possibly empty) of c of elements that satisfy good:
	template <typename Predicate, typename Cont>
	std::vector<typename Cont::value_type> takeWhile(Predicate good, const Cont& c) {
		std::vector<typename Cont::value_type> prefix;

		for (auto it = std::begin(c); it != std::end(c); ++it) {
			if (good(*it)) prefix.push_back(*it);
			else break;
		}

		return prefix;
	}


	//Function drop: drop v c returns the suffix of c after the first v elements,
	//or [] if v > length c:
	template <typename Value, typename Cont>
	std::vector<typename Cont::value_type> drop(Value v, const Cont& c) {
		std::vector<typename Cont::value_type> suffix;

		if ((unsigned)v > c.size()) return suffix;

		for (auto it = std::begin(c) + v; it != std::end(c); ++it) {
			suffix.push_back(*it);
		}

		return suffix;
	}

	//Function dropWhile: dropWhile bad c returns the suffix remaining after takeWhile bad c:
	template <typename Predicate, typename Cont>
	std::vector<typename Cont::value_type> dropWhile(Predicate bad, const Cont& c) {
		std::vector<typename Cont::value_type> suffix;

		bool keep_dropping = true;

		for (auto it = std::begin(c); it != std::end(c); ++it) {
			if (!bad(*it) || !keep_dropping) {
				suffix.push_back(*it);
				keep_dropping = false;
			}
		}

		return suffix;
	}


	// elem - the list membership predicate. Returns true if an element equal to x was found at the given container.
	template<typename Cont, typename T>
	bool elem(const T& val, const Cont& container) {
		return (std::find(container.begin(), container.end(), val) != container.end());
	}

	// notElem - the negation of elem.
	template<typename Cont, typename T>
	bool notElem(const T& val, const Cont& container) {
		return !(std::find(container.begin(), container.end(), val) != container.end());
	}


	// span_container, applied to a predicate p and a container, returns a pair where first element is longest prefix
	// (possibly empty) of container of elements that satisfy p and second element is the remainder of the list.
	// span_container p container is equivalent to (takeWhile p container, dropWhile p container).
	template<typename Predicate, typename Cont>
	std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> span_container(Predicate p, const Cont& container) {
		std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> result;

		result = std::make_pair(takeWhile(p, container), dropWhile(p, container));

		return result;
	}

	// break_container, applied to a predicate p and a container, returns a tuple where first element is longest prefix
	// (possibly empty) of container of elements that do not satisfy p and second element is the remainder of the list.
	// break_container p is equivalent to span (not(p)).
	template<typename Predicate, typename Cont>
	std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> break_container(Predicate p, const Cont& container) {
		std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> result;

		auto notP = [&](typename const Cont::value_type &x) { return !p(x); };

		result = std::make_pair(takeWhile(notP, container), dropWhile(notP, container));
		return result;
	}

	// splitAt - returns a pair where first element is container prefix of length n and second element is the remainder of the list.
	// It is equivalent to (take n container, drop n container).
	template<typename Cont>
	std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> splitAt(int n, const Cont& container) {
		std::pair<std::vector<typename Cont::value_type>, std::vector<typename Cont::value_type>> result;

		result = std::make_pair(take(n, container), drop(n, container));

		return result;
	}

	/* ------ */
	/* C++ 14 */
	/* ------ */

	//Function Composition  Haskel definition:  (.) :: (b -> c) -> (a -> b) -> a -> c 
	/*template<typename F, typename G>
	decltype(auto)compose(F&& f, G&& g)
	{
	return[=](auto x){return f(g(x)); };

	}*/

}

#endif /* _HUSKY_H */
