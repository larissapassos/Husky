//filter function

#include <iostream>     // std::cout
#include <algorithm>    // std::remove_if
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <iterator>


bool isOdd (int i) { return ((i%2)==1); }

using namespace functionalibrary;

int main () {
	int myints[] = {1,2,3,4,5,6,7,8,9};            // 1 2 3 4 5 6 7 8 9

	// bounds of range:
	int* pbegin = myints;                          // ^
	int* pend = myints+sizeof(myints)/sizeof(int); // ^                 ^
	   
	pend = std::remove_if (pbegin, pend, isOdd);   // 2 4 6 8 ? ? ? ? ?
	   					       // ^       ^
	std::cout << "the range contains:";
	for (int* p=pbegin; p!=pend; ++p){
	    	std::cout << ' ' << *p;}

	std::cout << '\n';
	    
	std::vector<int> taste = {1,2,3,4,5,6,7,8,9};

	filter(taste, isOdd);
	filter(taste,[](int value){ return value > 4;});

return 0;
}
