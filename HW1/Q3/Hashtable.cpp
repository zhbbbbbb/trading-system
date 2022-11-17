#ifndef Hashtable_CPP
#define Hashtable_CPP


#include "Hashtable.hpp"
#include <memory>
#include <vector>


template <typename K, typename V>
Hashtable<K, V>::Hashtable(int size, std::shared_ptr<Hasher<K>> hasher, std::shared_ptr<EqualityPredicate<K>> equal_predicate): 
	size(size), table(std::vector<std::list<std::pair<K, V>>>(size)), hasher(hasher), equal_predicate(equal_predicate)
{

}


template <typename K, typename V>
void Hashtable<K, V>::Add(const K& key, const V& value)
{
	int idx = hasher->hash(key) % size;
	for (auto& pair : table[idx])
	{
		if (equal_predicate->equal(pair.first, key))
		{
			// update old value with new value
			pair.second = value;
			return;
		}
	}
	table[idx].push_back(std::pair<K, V>(key, value));
}

template <typename K, typename V>
V Hashtable<K, V>::Get(const K& key, const V& substitute_value) const 
{
	int idx = hasher->hash(key) % size;
	for (auto& pair : table[idx])
	{
		if (equal_predicate->equal(pair.first, key))
		{
			return pair.second;
		}
	}
	return substitute_value;
}


template <typename K, typename V>
void Hashtable<K, V>::Remove(const K& key)
{
	int idx = hasher->hash(key) % size;
	for (auto it = table[idx].begin(); it != table[idx].end();)
	{
		if (equal_predicate->equal(it->first, key))
		{
			//auto del = it;
			//it = it.next();
			table[idx].erase(it++);
			return;
		}
		else ++it;
	}
	//auto it = table[idx].begin();
	//while (it != table[idx].end())
	//{

	//}

}



#endif