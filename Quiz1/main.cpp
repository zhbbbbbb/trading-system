#include <iostream>
#include <vector>
#include "quiz_QuickSort.hpp"
#include "quiz_MaxHeap.hpp"


template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<T>& arr)
{
	for (unsigned int i = 0; i < arr.size(); ++i)
	{
		os << arr[i] << " ";
	}
	return os;
}


int main()
{
	// Q1 quicksort
	std::cout << "---Q1---" << std::endl;
	std::vector<int> arr1{ 11, 3,2,5,9, 1, 3 };

	QuickSort<int> qs;
	qs.Sort(arr1);
	std::cout << arr1 << std::endl << std::endl; // 1 2 3 3 5 9 11


	// Q2&3 maxheap
	std::cout << "---Q2---" << std::endl;
	std::vector<int> arr2{ 11, 3,2,5,9, 1, 3 };
	MaxHeap<int> mp(arr2);
	mp.Print(); // built max heap in Print()

	mp.Add(100);
	mp.Add(200);
	mp.Print();


	std::cout << "---Q3---" << std::endl;
	mp.Remove(4); // remove the 4th node
	mp.Print();

	return 0;
}