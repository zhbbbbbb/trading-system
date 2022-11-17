#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <memory>
#include "Node.hpp"
#include "ListIterator.hpp"


template <typename T>
class LinkedList
{
private:
	std::shared_ptr<Node<T>> head_ptr;
	int size;

public:
	LinkedList();

	// Add the specified element at the end of the list
	virtual void Add(T& value);

	// Add the specified element at the specified index
	virtual void Insert(T& value, int index);

	// Get the element at the specified index
	virtual T& Get(int index);

	// Retrieve the index of the specified element (-1 if it does not exist in the list
	virtual int IndexOf(T& value);

	// Remove the element at the specified index and return it
	virtual T& Remove(int index);

	// Return an iterator on this list
	virtual ListIterator<T> Iterator();

	// Return the size of the list
	int Size();
};



#ifndef LinkedList_CPP 
#include "LinkedList.cpp"
#endif




#endif