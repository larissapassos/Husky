#ifndef _FUNCTIONALIBRARY_H
#define _FUNCTIONALIBRARY_H

#include <functional>
#include <algorithm>
#include <numeric>

namespace functionalibrary {

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

	// Look into concat and concatMap

	template <typename Cont,typename UnaryOperation>
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



	template<typename TYPE, typename Predicate>
	TYPE filter( const TYPE & data, Predicate good){
		auto filteredData(data);  	//Use copy constructor to copy data set
					
		filteredData.erase(remove_if(filteredData.begin(), filteredData.end(),
		[&](typename TYPE::value_type &x) { return !good(x); }), filteredData.end());

		return filteredData;
	}
}

#endif /* _FUNCTIONALIBRARY_H */
