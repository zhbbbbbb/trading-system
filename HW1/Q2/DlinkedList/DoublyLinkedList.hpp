#pragma once
#include <iostream>
#include "../LinkedList/LinkedList.hpp"
#include "DNode.hpp"
#include "../LinkedList/ListIterator.hpp"

template <typename T>
class DoublyLinkedList: public LinkedList<T>{

private:
    std::shared_ptr<DNode<T> > head_ptr;
    std::shared_ptr<DNode<T> > tail_ptr;
    int size;

public:
    DoublyLinkedList();
    virtual ~DoublyLinkedList();

    void Add(T& value);
    
    void Insert(T& value, int index);
    
    T& Get(int index);
    
    int IndexOf(T& value);
    
    T& Remove(int index);
     
    int Size();

//    ListIterator<T> Iterator();
};
