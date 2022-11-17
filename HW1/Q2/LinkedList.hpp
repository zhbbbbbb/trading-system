#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <memory>
#include "Node.hpp"
#include "ListIterator.hpp"


template <typename T>
class LinkedList
{
protected:
	std::shared_ptr<Node<T>> head_ptr;
	int size;

public:
	LinkedList();

	// Add the specified element at the end of the list
	void Add(T& value);

	// Add the specified element at the specified index
	void Insert(T& value, int index);

	// Get the element at the specified index
	T& Get(int index);

	// Retrieve the index of the specified element (-1 if it does not exist in the list
	int IndexOf(T& value);

	// Remove the element at the specified index and return it
	T& Remove(int index);

	// Return an iterator on this list
	ListIterator<T> Iterator();

	// Return the size of the list
	int Size();
};



#ifndef LinkedList_CPP 
#include "LinkedList.cpp"
#endif




#endif