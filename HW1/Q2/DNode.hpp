#ifndef DNode_hpp
#define DNode_hpp

#include "Node.hpp"

template <typename T>
class DNode : public Node<T>
{
public:
    T val;
    std::shared_ptr<DNode<T>> next;
    std::shared_ptr<DNode<T>> prev;

    DNode();            
    DNode(T x);   
};

#ifndef DNode_CPP
#include "DNode.cpp"
#endif

#endif