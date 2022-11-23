#ifndef QuickSort_HPP
#define QuickSort_HPP

#include <vector>

template <typename T>
class QuickSort
{
public:
	// swap 2 positions in arr
	void Swap(std::vector<T>& arr, int i, int j)
	{
		T temp = std::move(arr[i]);
		arr[i] = std::move(arr[j]);
		arr[j] = std::move(temp);
	}

	// partition arr[i, j) using the pivot at index i
	int Partition(std::vector<T>& arr, int i, int j)
	{
		int pivot_idx = i;
		T pivot = arr[i];

		for (int k = i + 1; k < j; ++k)
		{
			// identify smaller element
			if (arr[k] <= pivot)
			{
				// keep switching until the smaller element is moved to the left of pivot
				for (int m = 0; m < k - pivot_idx; ++m)
				{
					Swap(arr, k - m, k - m - 1);
				}
				++pivot_idx; // update the index of pivot
			}
		}
		return pivot_idx;
	}


	std::vector<T>& Quicksort(std::vector<T>& arr, int i, int j)
	{
		if (i < j)
		{
			int pivot_idx = Partition(arr, i, j); // partition the array into left and right arrays
			Quicksort(arr, i, pivot_idx); // quick sort the left array
			Quicksort(arr, pivot_idx + 1, j); // quick sort the right array
		}
		return arr;
	}

	std::vector<T>& Sort(std::vector<T>& arr)
	{
		Quicksort(arr, 0, arr.size());
		return arr;
	}




};



#endif