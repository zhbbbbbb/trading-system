#ifndef DNode_hpp
#define DNode_hpp

#include "Node.hpp"

template <typename T>
class DNode : public Node<T>
{
public:
    DNode();            
    DNode(T x);
    virtual ~DNode();

    T val;
    std::shared_ptr<DNode<T>> next;
    std::shared_ptr<DNode<T>> prev;    //point to the previous one
};

#ifndef DNode_CPP
#include "DNode.cpp"
#endif

#endif