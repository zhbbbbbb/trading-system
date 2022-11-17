#ifndef Hasher_HPP
#define Hasher_HPP

#include <memory>
#include <cmath>

template <typename K>
class Hasher
{
private:

public:
	virtual ~Hasher() {}    // virtual dstor
	virtual int hash(K key) = 0;
	
};



template <typename K>
class Hasher1 : public Hasher<K>
{
private:
	std::hash<K> hasher;
public:
	Hasher1(): hasher(std::hash<K>()) {}
	virtual ~Hasher1() {}


	virtual int hash(K key)
	{
		int val = hasher(key);
		if (val > 0) return val;
		else return -val;
	}
};

#endif