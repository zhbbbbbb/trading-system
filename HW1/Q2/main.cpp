#include <iostream>
#include "DoublyLinkedList.hpp"

template <typename T>
std::ostream& operator << (std::ostream& os, DoublyLinkedList<T>& list)
{
	for (int i = 0; i < list.Size(); ++i)
	{
		os << list.Get(i) << " ";
	}
	return os;
}


using namespace std;

int main()
{
	DoublyLinkedList<int> list;
	std::cout << "Size: " << list.Size() << std::endl << std::endl;

	int n0=0, n1=1, n2=2, n3=3, n4=4, n5=5;


	std::cout << "Adding 1 to the end." << std::endl;
	list.Add(n1);
	std::cout << "Size: " << list.Size() << std::endl;

	cout << list.head_ptr->val << std::endl;
	cout << "list: " << list << std::endl;


	std::cout << "Adding 2 to the end." << std::endl;
	list.Add(n2);
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	std::cout << list.head_ptr->next->prev->val << std::endl;

	// insert at the end
	std::cout << "Inserting 4 at index 2." << std::endl;
	list.Insert(n4, 2);
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	// insert at the head
	std::cout << "Inserting 0 at index 0." << std::endl;
	list.Insert(n0, 0);
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	// insert in the middle	
	std::cout << "Inserting 3 at index 3." << std::endl;
	list.Insert(n3, 3);
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;


	std::cout << "Index of 0: " << list.IndexOf(n0) << std::endl << std::endl;

	std::cout << "Get value at index 1: " << list.Get(1) << std::endl << std::endl;

	// remove the first
	std::cout << "Removing " << list.Remove(0) << std::endl;
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	// remove the last
	std::cout << "Removing " << list.Remove(list.Size() - 1) << std::endl;
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	// remove the middle
	std::cout << "Removing " << list.Remove(1) << std::endl;
	std::cout << "Size: " << list.Size() << std::endl;
	std::cout << list << std::endl << std::endl;

	std::cout << "Keep Calling Next() on the iterator while it HasNext()." << std::endl;
	ListIterator2<int> a = list.Iterator();
	std::cout << a.Curr() << std::endl;
	while (a.HasNext())
		std::cout << a.Next() << std::endl;





	return 0;
}
