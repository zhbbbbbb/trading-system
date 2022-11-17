#ifndef Hashtable_HPP
#define Hashtable_HPP

#include <memory>
#include <vector>
#include <list>
#include "Hasher.hpp"
#include "EqualityPredicate.hpp"

template <typename K, typename V>
class Hashtable
{
private:
	int size;
	std::vector<std::list<std::pair<K, V>>> table;
	std::shared_ptr<Hasher<K>> hasher;
	std::shared_ptr<EqualityPredicate<K>> equal_predicate;

public:
	Hashtable(int size, std::shared_ptr<Hasher<K>> hasher, std::shared_ptr<EqualityPredicate<K>> equal_predicate);
	void Add(const K& key, const V& value);
	V Get(const K& key, const V& substitute_value) const;
	void Remove(const K& key);
};




#ifndef Hashtable_CPP 
#include "Hashtable.cpp"
#endif

#endif