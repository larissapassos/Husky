#ifndef _FUNCTIONALIBRARY_H
#define _FUNCTIONALIBRARY_H

#include <numeric>

namespace functionalibrary {

	template<typename Function, typename Iterator, typename T>
	static T foldl(Iterator first, Iterator last, T init, Function f) { return std::accumulate(first, last, init, f); }

}

#endif /* _FUNCTIONALIBRARY_H */