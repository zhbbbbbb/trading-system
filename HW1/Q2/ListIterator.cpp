#ifndef ListIterator_CPP
#define ListIterator_CPP


#include "ListIterator.hpp"
#include "DoublyLinkedList.hpp"


template <typename T>
ListIterator<T>::ListIterator(): curr_ptr(nullptr)
{

}

template <typename T>
ListIterator<T>::ListIterator(std::shared_ptr<Node<T>>& ptr): curr_ptr(ptr)
{

}

// Return whether there is another element to return in this iterator
template <typename T>
bool ListIterator<T>::HasNext()
{
	if (curr_ptr != nullptr)
	{
		return curr_ptr->next != nullptr;
	}
	else
	{
		return false;
	}
}

// Return the next element in this iterator
template <typename T>
T& ListIterator<T>::Next()
{
	curr_ptr = curr_ptr->next;
	return curr_ptr->val;
}

// Return the current element in this iterator
template <typename T>
T& ListIterator<T>::Curr()
{
	return curr_ptr->val;
}



template <typename T>
ListIterator2<T>::ListIterator2() : curr_ptr(nullptr)
{

}

template <typename T>
ListIterator2<T>::ListIterator2(std::shared_ptr<DNode<T>>& ptr) : curr_ptr(ptr)
{

}

// Return whether there is another element to return in this iterator
template <typename T>
bool ListIterator2<T>::HasNext()
{
	if (curr_ptr != nullptr)
	{
		return curr_ptr->next != nullptr;
	}
	else
	{
		return false;
	}
}

// Return the next element in this iterator
template <typename T>
T& ListIterator2<T>::Next()
{
	curr_ptr = curr_ptr->next;
	return curr_ptr->val;
}

// Return the current element in this iterator
template <typename T>
T& ListIterator2<T>::Curr()
{
	return curr_ptr->val;
}

#endif