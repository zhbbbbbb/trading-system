#ifndef Node_HPP
#define Node_HPP

#include <memory>


template <typename T>
class Node
{
private:

public:
	T val;
	std::shared_ptr<Node<T>> next;

	Node();
	Node(T val);
};



#ifndef Node_CPP 
#include "Node.cpp"
#endif

#endif