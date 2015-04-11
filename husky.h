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

		void push_head(T elm) {
			auto it = container.begin();
			container.insert(it, elm);
		}

		void push_tail(T elm) { container.push_back(); }

		void remove_head() {
			auto it = container.begin();
			container.erase(it);
		}

		void remove_tail() { container.pop_back(); }
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


	template <typename Cont, typename UnaryOperation>
	Cont map(const Cont& c, UnaryOperation f) {
		Cont c2;
		for (auto elm : c) {
			auto new_elm = f(elm);
			c2.push_back(new_elm);
		}
		return c2;
	}

	template <typename Cont1, typename Cont2>
	std::vector<std::pair <typename Cont1::value_type, typename Cont2::value_type> > zip(const Cont1& c1, const Cont2& c2) {
		std::vector<std::pair <typename Cont1::value_type, typename Cont2::value_type> > result;
		int len = std::min(c1.size(), c2.size());
		for (int i = 0; i < len; ++i) {
			auto new_elm = std::make_pair(c1[i], c2[i]);
			result.push_back(new_elm);
		}
		return result;
	}


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
