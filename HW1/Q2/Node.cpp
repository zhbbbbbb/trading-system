#ifndef Node_CPP
#define Node_CPP


#include "Node.hpp"


template<typename T>
Node<T>::Node() : val(T()), next(nullptr)
{

}



template<typename T>
Node<T>::Node(T x) :val(x), next(nullptr)
{

}



#endif