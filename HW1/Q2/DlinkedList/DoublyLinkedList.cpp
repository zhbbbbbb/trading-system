#include "DoublyLinkedList.hpp"
#include "DNode.cpp"
#include <iostream>
using namespace std;


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
    head_ptr=nullptr;
    tail_ptr=nullptr;
    size=0;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){}

template <typename T>
void DoublyLinkedList<T>::Add(T& value){
    if (size > 0)
    {
        std::shared_ptr<DNode<T>> curr_tail=tail_ptr;
        std::shared_ptr<DNode<T>> new_ptr (new DNode<T>);
        new_ptr->val = value;
        curr_tail->next=new_ptr;
        tail_ptr = curr_tail->next;
        tail_ptr->prev = curr_tail;
        
    }
    else{
        std::shared_ptr<DNode<T>> new_head (new DNode<T>);
        new_head->val = value;
        head_ptr = new_head;
    }
    size++;
    return;
}


template <typename T>
void DoublyLinkedList<T>::Insert(T& value, int index){

    if(index > size || index < 0){
        std::cout << "Insert index out of range" << std::endl;
        return;
    }
    std::shared_ptr<DNode<T>> curr;
    if (index < size / 2) {
        curr = head_ptr;
        for(int i = 0; i < index;++i){
            curr = curr->next;
        }
    } else {
        curr = tail_ptr;
        for(int i = size-1; i > index;--i){
            curr=curr->prev;
        }
    }
    
    std::shared_ptr<DNode<T>> right = curr->next;
    DNode<T> new_node;
    new_node.val = value;
    curr->next = std::shared_ptr<DNode<T>>(&new_node);
    curr->next->next = right;
    right->prev = std::shared_ptr<DNode<T>>(&new_node);
    curr->next->prev = curr;
    
    size++;
    return;
}


template <typename T>
T& DoublyLinkedList<T>::Get(int index){
    
    std::shared_ptr<DNode<T>> curr = head_ptr;

    curr = head_ptr;
    for(int i = 0; i < index;++i){
        curr = curr->next;
    }

    return curr->val;
}


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
    
    std::shared_ptr<DNode<T> > curr = head_ptr;
    if (index < size / 2) {
        for(int i = 0; i < index;++i){
            curr = curr->next;
        }
    } else {
        curr = tail_ptr;
        for(int i = size-1; i >= index;--i){
            curr=curr->prev;
        }
    }
    
    auto temp=curr->next;
    
    if (curr -> next ->next == nullptr)
        tail_ptr = curr;
    else{
        curr -> next = curr -> next -> next;
        curr -> next -> prev = curr;
    }
    
    
    size--;
    return temp->val;
}

// Return the size of the list
template <typename T>
int DoublyLinkedList<T>::Size(){
    return size;
}

//template <typename T>
//ListIterator<T> DoublyLinkedList<T>::Iterator(){
//    ListIterator<T> res(head_ptr);
//    return res;
//}
