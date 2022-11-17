#ifndef DNode_CPP
#define DNode_CPP



#include <iostream>
#include "DNode.hpp"

template<typename T>
DNode<T>::DNode(){}

template<typename T>
DNode<T>::~DNode(){}

//constructor with new value
template<typename T>
DNode<T>::DNode(T x) : prev(nullptr)
{
	val = x;
	next = nullptr;
}



#endif