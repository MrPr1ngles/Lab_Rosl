#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), length(0) {}

template<typename T>
LinkedList<T>::LinkedList(T* items, int count) : head(nullptr), length(0) {
    for (int i = 0; i < count; i++) {
        Append(items[i]);
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), length(0) {
    Node* current = other.head;
    while (current) {
        Append(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
T LinkedList<T>::GetFirst() const {
    if (!head)
        throw std::out_of_range("IndexOutOfRange");
    return head->data;
}

template<typename T>
T LinkedList<T>::GetLast() const {
    if (!head)
        throw std::out_of_range("IndexOutOfRange");
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("IndexOutOfRange");
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw std::out_of_range("IndexOutOfRange");
    LinkedList<T>* subList = new LinkedList<T>();
    Node* current = head;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }
    for (int i = startIndex; i <= endIndex; i++) {
        subList->Append(current->data);
        current = current->next;
    }
    return subList;
}

template<typename T>
int LinkedList<T>::GetLength() const {
    return length;
}

template<typename T>
void LinkedList<T>::Append(T item) {
    Node* newNode = new Node(item);
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
    length++;
}

template<typename T>
void LinkedList<T>::Prepend(T item) {
    Node* newNode = new Node(item);
    newNode->next = head;
    head = newNode;
    length++;
}

template<typename T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > length)
        throw std::out_of_range("IndexOutOfRange");
    if (index == 0) {
        Prepend(item);
        return;
    }
    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node* newNode = new Node(item);
    newNode->next = current->next;
    current->next = newNode;
    length++;
}

template<typename T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>* list) const {
    LinkedList<T>* result = new LinkedList<T>(*this);
    Node* current = list->head;
    while (current) {
        result->Append(current->data);
        current = current->next;
    }
    return result;
}

#endif
