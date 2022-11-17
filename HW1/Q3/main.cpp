#include <vector>
#include <list>
#include <iostream>
#include "Hashtable.hpp"


int main()
{
	// size of dictionary
	int size = 100;

	std::shared_ptr<Hasher<std::string>> hasher_ptr;
	hasher_ptr.reset(new Hasher1<std::string>());

	std::shared_ptr<EqualityPredicate<std::string>> predicate_ptr;
	predicate_ptr.reset(new EqualityPredicate1<std::string>());


	Hashtable<std::string, int> ht(size, hasher_ptr, predicate_ptr);
	
	ht.Add("One", 1);
	std::cout << ht.Get("One", -1) << std::endl;

	std::cout << ht.Get("Two", -1) << std::endl; // return -1 because no key named "Two"
	ht.Add("Two", 2);
	std::cout << ht.Get("Two", -1) << std::endl; // return -1 because no key named "Two"

	ht.Remove("One");
	std::cout << ht.Get("One", -1) << std::endl; // return -1 because no key named "Two"


	return 0;
}