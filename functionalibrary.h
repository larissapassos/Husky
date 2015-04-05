#ifndef _FUNCTIONALIBRARY_H
#define _FUNCTIONALIBRARY_H

#include <algorithm>
#include <numeric>

namespace functionalibrary {

	template<typename Function, typename Iterator, typename T>
	static T foldl(Iterator first, Iterator last, T init, Function f) { return std::accumulate(first, last, init, f); }

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
}

#endif /* _FUNCTIONALIBRARY_H */