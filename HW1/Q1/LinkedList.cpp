#ifndef LinkedList_CPP
#define LinkedList_CPP

#include "LinkedList.hpp"
#include <iostream>


// Add the specified element at the end of the list
template <typename T>
LinkedList<T>::LinkedList(): head_ptr(nullptr), size(0)
{
	
}

// Add the specified element at the end of the list
template <typename T>
void LinkedList<T>::Add(T& value)
{
	if (size > 0)
	{
		// first, traverse thru the end of the list
		std::shared_ptr<Node<T>> curr_ptr = head_ptr;
		for (int i = 0; i < size-1; ++i)
		{
			curr_ptr = curr_ptr->next;
		}
		// add value to the end
		curr_ptr->next = std::make_shared<Node<T>>(value);
		
	}
	else
		head_ptr = std::make_shared<Node<T>>(value);

	// update size
	++size;	
}

// Add the specified element at the specified index
template <typename T>
void LinkedList<T>::Insert(T& value, int index)
{
	if (index < 0 || index > size) throw std::out_of_range("Invalid index.");
	std::shared_ptr<Node<T>> curr_ptr = head_ptr;
	if (index > 0)
	{
		for (int i = 0; i < index - 1; ++i)
		{
			curr_ptr = curr_ptr->next;
		}
		std::shared_ptr<Node<T>> temp = std::move(curr_ptr->next);
		curr_ptr->next = std::make_shared<Node<T>>(Node<T>(value));	// insert new node at inedx
		curr_ptr->next->next = temp;// attach the previous member at that index to the one after.
	}
	else
	{
		std::shared_ptr<Node<T>> temp = std::move(curr_ptr);
		head_ptr = std::make_shared<Node<T>>(Node<T>(value));	// insert new node at inedx
		head_ptr->next = temp;
	}
	++size; // update size
}

// Get the element at the specified index
template <typename T>
T& LinkedList<T>::Get(int index)
{
	if (index < 0 || index >= size) throw std::out_of_range("Invalid index.");
	std::shared_ptr<Node<T>> curr_ptr = head_ptr;
	for (int i = 0; i < index; ++i)
	{
		curr_ptr = curr_ptr->next;
	}
	return curr_ptr->val;
}

// Retrieve the index of the specified element (-1 if it does not exist in the list
template <typename T>
int LinkedList<T>::IndexOf(T& value)
{
	std::shared_ptr<Node<T>> curr_ptr = head_ptr;
	int curr_index = 0;
	for (int i = 0; i < size; ++i)
	{
		if (curr_ptr->val == value) return curr_index;
		++curr_index;
		curr_ptr = curr_ptr->next;
	}
	return -1;
}

// Remove the element at the specified index and return it
template <typename T>
T& LinkedList<T>::Remove(int index)
{
	if (index < 0 || index >= size) throw std::out_of_range("Invalid index.");
	std::shared_ptr<Node<T>> ptr;
	// first, traverse to the index
	std::shared_ptr<Node<T>> curr_ptr = head_ptr;
	if (index > 0)
	{
		for (int i = 0; i < index - 1; ++i)
		{
			curr_ptr = curr_ptr->next;
		}
		ptr = curr_ptr->next;
		curr_ptr->next = curr_ptr->next->next;
	}
	else
	{
		ptr = head_ptr;
		head_ptr = curr_ptr->next;
	}
	--size; // update size
	return ptr->val;
}

// Return an iterator on this list
template <typename T>
ListIterator<T> LinkedList<T>::Iterator()
{
	//std::cout << "Within Iterator() " << head_ptr==nullptr
	return ListIterator<T>(head_ptr);

}


// Return the size of the list
template <typename T>
int LinkedList<T>::Size()
{
	return size;
}




#endif