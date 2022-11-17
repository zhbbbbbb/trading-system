#ifndef ListIterator_HPP
#define ListIterator_HPP

#include <memory>
#include "Node.hpp"
#include "DNode.hpp"

template <typename T>
class ListIterator
{
private:
	std::shared_ptr<Node<T>> curr_ptr;

public:
	ListIterator();
	ListIterator(std::shared_ptr<Node<T>>& ptr);

	// Return whether there is another element to return in this iterator
	bool HasNext();

	// Return the next element in this iterator
	T& Next();
	// Return the current element in this iterator
	T& Curr();
};

template <typename T>
class ListIterator2
{
private:
	std::shared_ptr<DNode<T>> curr_ptr;

public:
	ListIterator2();
	ListIterator2(std::shared_ptr<DNode<T>>& ptr);

	// Return whether there is another element to return in this iterator
	bool HasNext();

	// Return the next element in this iterator
	T& Next();
	// Return the current element in this iterator
	T& Curr();
};






#ifndef ListIterator_CPP 
#include "ListIterator.cpp"
#endif


#endif