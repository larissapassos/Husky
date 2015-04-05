#ifndef _FUNCTIONALIBRARY_H
#define _FUNCTIONALIBRARY_H

#include <functional>
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

}

#endif /* _FUNCTIONALIBRARY_H */