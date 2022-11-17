#ifndef DLinkedList_hpp
#define DLinkedList_hpp

#include <iostream>
#include "LinkedList.hpp"
#include "ListIterator.hpp"


template <typename T>
class Node;

template <typename T>
class LinkedList;

template <typename T>
class ListIterator;


template <typename T>
class DoublyLinkedList: public LinkedList<T>{

private:
    std::shared_ptr<DNode<T>> head_ptr;
    std::shared_ptr<DNode<T>> tail_ptr;
    int size;

public:
    DoublyLinkedList();

    void Add(T& value);
    
    void Insert(T& value, int index);
    
    T& Get(int index);
    
    int IndexOf(T& value);
    
    T& Remove(int index);
     
    int Size();

    ListIterator2<T> Iterator();
};


#ifndef DoublyLinkedList_CPP
#include "DoublyLinkedList.cpp"
#endif


#endif
