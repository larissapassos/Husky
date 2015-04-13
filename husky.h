#ifndef _HUSKY_H
#define _HUSKY_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

namespace husky {

	template<typename T, typename Cont>
	class Hlist {
		using value_type = T;
	public:
		Hlist(Cont c) :container(c) {}
		Hlist() { container; }
		Hlist(T a) {
			container;
			container.push_back(a);
		}

		//friend auto begin(Hlist<T, Cont>& l) -> decltype(l.container.begin()) { return l.container.begin(); }
		//friend auto end(Hlist<T, Cont>& l) -> decltype(l.container.end()) { return l.container.end(); }

		int size() { return container.size(); }

		T operator[](int index) {
			int i = 0;
			T elm;
			for (auto x : container) {
				elm = x;
				if (i == index) {
					return x;
				}
				++i;
			}
			return elm;
		}

		//todo: const operator[]

		void add_head(T elm) {
			auto it = container.begin();
			container.insert(it, elm);
		}

		void add_tail(T elm) { container.push_back(elm); }

		void remove_head() {
			auto it = container.begin();
			container.erase(it);
		}

		void remove_tail() { container.pop_back(); }

		friend Hlist<T, Cont>& operator+= (Hlist<T, Cont>& l1, Hlist<T, Cont>& l2) {
			for (int i = 0; i < l2.size(); ++i) {
				l1.add_tail(l2[i]);
			}
			return l1;
		}

	private:
		Cont container;
	};	

	template<typename T, typename Cont>
	std::ostream& operator<<(std::ostream& os, Hlist<T, Cont>& l) {
		os << "[";
		for (int i = 0; i < l.size(); ++i) {
			if (i != (l.size() - 1)) {
				os << l[i] << ",";
			}
			else {
				os << l[i];
			}
		}
		os << "]";
		return os;
	}

	template <typename T, typename Cont>
	Hlist<T, Cont> cons(T head, Hlist<T, Cont>& tail) {
		Hlist<T, Cont> newList{ head };
		newList += tail;
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
	bool and(Iterator first, Iterator last) { return std::accumulate(first, last, true, std::logical_and<bool>()); }

	template<typename Iterator>
	bool or(Iterator first, Iterator last) { return std::accumulate(first, last, false, std::logical_or<bool>()); }
	*/

	template <typename T, typename Cont, typename UnaryOperation>
	Hlist<T, Cont> map(Hlist<T, Cont>& l, UnaryOperation f) {
		Hlist<T, Cont> l2;
		for (int i = 0; i < l.size(); ++i) {
			T new_elm = f(l[i]);
			l2.add_tail(new_elm);
		}
		return l2;
	}

	template <typename T, typename V, typename Cont1, typename Cont2>
	Hlist<std::pair<T,V>, std::vector<std::pair<T,V>>> zip(Hlist<T, Cont1>& l1, Hlist<V, Cont2>& l2) {
		Hlist<std::pair<T, V>, std::vector<std::pair<T, V>>> result;
		int len = std::min(l1.size(), l2.size());
		for (int i = 0; i < len; ++i) {
			std::pair<T, V> new_elm = std::make_pair(l1[i], l2[i]);
			result.add_tail(new_elm);
		}
		return result;
	}
	
	/*
	//filter function returns a list with filtered data
	template<typename T, typename Predicate>
	T filter(const T & data, Predicate good){

		auto filteredData(data);  	//Use copy constructor to copy data set

		filteredData.erase(remove_if(filteredData.begin(), filteredData.end(),
			[&](typename T::value_type &x) { return !good(x); }), filteredData.end());

		return filteredData;
	}*/
}

#endif /* _HUSKY_H */
