#ifndef DoublyLinkedList_CPP
#define DoublyLinkedList_CPP


#include "DoublyLinkedList.hpp"
#include <iostream>
using namespace std;


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(): head_ptr(std::make_shared<DNode<T>>()), tail_ptr(nullptr), size(0) {}


template <typename T>
void DoublyLinkedList<T>::Add(T& value){
    if (size > 0)
    {
        // first, traverse thru the end of the list
        std::shared_ptr<DNode<T>> curr_ptr = head_ptr;
        for (int i = 0; i < size - 1; ++i)
        {
            curr_ptr = curr_ptr->next;
        }
        // add value to the end
        curr_ptr->next = std::make_shared<DNode<T>>(value);
        curr_ptr->next->prev = curr_ptr;
    }
    else
        head_ptr = std::make_shared<DNode<T>>(value);
    // update size
    ++size;
}
//
//
template <typename T>
void DoublyLinkedList<T>::Insert(T& value, int index){
    if (index < 0 || index > size) throw std::out_of_range("Invalid index.");
    std::shared_ptr<DNode<T>> curr_ptr = head_ptr;
    if (index > 0)
    {
        for (int i = 0; i < index - 1; ++i)
        {
            curr_ptr = curr_ptr->next;
        }
        std::shared_ptr<DNode<T>> temp = std::move(curr_ptr->next);
        curr_ptr->next = std::make_shared<DNode<T>>(DNode<T>(value));	// insert new node at inedx
        curr_ptr->next->next = temp;// attach the previous member at that index to the one after.
        curr_ptr->next->prev = curr_ptr;
        if (index<size)
            curr_ptr->next->next->prev = curr_ptr->next;
    }
    else
    {
        std::shared_ptr<DNode<T>> temp = std::move(curr_ptr);
        head_ptr = std::make_shared<DNode<T>>(DNode<T>(value));	// insert new node at inedx
        head_ptr->next = temp;
        head_ptr->next->prev = head_ptr;
    }
    ++size; // update size
}


template <typename T>
T& DoublyLinkedList<T>::Get(int index){
    if (index < 0 || index >= size) throw std::out_of_range("Invalid index.");
    std::shared_ptr<DNode<T>> curr_ptr = head_ptr;
    for (int i = 0; i < index; ++i)
    {
        curr_ptr = curr_ptr->next;
    }
    return curr_ptr->val;

}
//
//
template <typename T>
int DoublyLinkedList<T>::IndexOf(T& value){
    auto curr=head_ptr;
    int index=0;
    
    while(curr!=nullptr && curr->val != value){
        curr = curr->next;
        index++;
    }
    if (curr==nullptr) return -1;
    return index;
}


template <typename T>
T& DoublyLinkedList<T>::Remove(int index){
    if (index < 0 || index >= size) throw std::out_of_range("Invalid index.");
    std::shared_ptr<DNode<T>> ptr;
    // first, traverse to the index
    std::shared_ptr<DNode<T>> curr_ptr = head_ptr;
    if (index > 0)
    {
        for (int i = 0; i < index - 1; ++i)
        {
            curr_ptr = curr_ptr->next;
        }
        ptr = curr_ptr->next;
        curr_ptr->next = curr_ptr->next->next;
    }
    else
    {
        ptr = head_ptr;
        head_ptr = curr_ptr->next;
    }
    --size; // update size
    return ptr->val;
}

// Return the size of the list
template <typename T>
int DoublyLinkedList<T>::Size() {
    return size;
}


template <typename T>
ListIterator2<T> DoublyLinkedList<T>::Iterator(){
    ListIterator2<T> res(head_ptr);
    return res;
}


#endif