#ifndef MaxHeap_HPP
#define MaxHeap_HPP


#include <vector>
#include <iostream>

template <typename T>
class MaxHeap
{
public:
	std::vector<T> tree; // a heap tree where the node i has subnodes at indices 2i+1 and 2i+2

	MaxHeap(std::vector<T> tree) : tree(tree)
	{

	}


	void Swap(int i, int j)
	{
		T temp = std::move(tree[i]);
		tree[i] = std::move(tree[j]);
		tree[j] = std::move(temp);
	}


	// heapify node i
	void Heapify(int i)
	{
		int n = tree.size();
		int larger_idx = i;
		int l = 2 * i + 1, r = 2 * i + 2; // left and right child
		if (l < n && tree[l] > tree[larger_idx])
		{
			larger_idx = l;
		}
		if (r < n && tree[r] > tree[larger_idx])
		{
			larger_idx = r;
		}
		if (i != larger_idx)
		{
			Swap(i, larger_idx);
		}

	}

	// make the tree max heap
	std::vector<T>& Build_MaxHeap()
	{
		// from the index of the last non-leaf node, use heapify(i) and keep decrementing i
		int n = tree.size();
		int i = (n - 2 - n % 2) / 2;
		for (int j = i; j >= 0; --j)
		{
			Heapify(j);
		}
		return tree;
	}

	// add an element to the maxheap
	void Add(T val)
	{
		tree.push_back(val);
		Build_MaxHeap();
	}

	// remove the ith element from the max heap
	void Remove(int i)
	{
		tree.erase(tree.begin() + i);
		Build_MaxHeap();
	}



	void Print()
	{
		Build_MaxHeap();
		int N = tree.size();
		int thres = 1;
		int curr = 0;
		for (int i = 0; i < N; ++i)
		{
			std::cout << tree[i] << " ";
			++curr;
			if (curr == thres)
			{
				std::cout << std::endl;
				thres *= 2;
				curr = 0;
			}
		}
		if (curr != 0) std::cout << std::endl;
		std::cout << std::endl;
	}

};



#endif