#ifndef EqualityPredicate_HPP
#define EqualityPredicate_HPP

#include <memory>


template <typename K>
class EqualityPredicate
{
private:

public:
	virtual bool equal(K key1, K key2) = 0;
};


template <typename K>
class EqualityPredicate1 : public EqualityPredicate<K>
{
private:
public:
	bool equal(K key1, K key2)
	{
		return key1 == key2;
	}
};


#endif