#pragma once
#ifndef DNode_hpp
#define DNode_hpp

#include "../LinkedList/Node.hpp"

template <typename T>
class DNode : public Node<T>
{
public:
    DNode();
    virtual ~DNode();
    
    T val;
    std::shared_ptr<DNode<T> > next;    //point to the next one
    std::shared_ptr<DNode<T> > prev;    //point to the previous one
};


#endif
