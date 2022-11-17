#ifndef Node_HPP
#define Node_HPP

#include <memory>


template <typename T>
class Node
{
private:

public:
	Node();
	Node(T val);
	T val;
	std::shared_ptr<Node<T>> next;
};



#ifndef Node_CPP 
#include "Node.cpp"
#endif

#endif