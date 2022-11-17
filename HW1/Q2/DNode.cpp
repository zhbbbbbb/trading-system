#ifndef DNode_CPP
#define DNode_CPP



#include <iostream>
#include "DNode.hpp"

template<typename T>
DNode<T>::DNode(){}


//constructor with new value
template<typename T>
DNode<T>::DNode(T x) : val(x), next(nullptr), prev(nullptr)
{

}



#endif