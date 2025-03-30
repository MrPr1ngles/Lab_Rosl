#ifndef LISTSEQUENCE_TPP
#define LISTSEQUENCE_TPP

#include "ListSequence.h"
#include <vector>

template<typename T>
ListSequence<T>::ListSequence(T* items, int count) {
    this->list = new LinkedList<T>(items, count);
}

template<typename T>
ListSequence<T>::ListSequence() {
    this->list = new LinkedList<T>();
}

template<typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) {
    this->list = new LinkedList<T>(*(other.list));
}

template<typename T>
ListSequence<T>::~ListSequence() {
    delete this->list;
}

template<typename T>
T ListSequence<T>::GetFirst() const {
    return this->list->GetFirst();
}

template<typename T>
T ListSequence<T>::GetLast() const {
    return this->list->GetLast();
}

template<typename T>
T ListSequence<T>::Get(int index) const {
    return this->list->Get(index);
}

template<typename T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    LinkedList<T>* sub = this->list->GetSubList(startIndex, endIndex);
    int len = sub->GetLength();
    T* arr = new T[len];
    for (int i = 0; i < len; i++) {
        arr[i] = sub->Get(i);
    }
    Sequence<T>* seq = new MutableListSequence<T>(arr, len);
    delete[] arr;
    delete sub;
    return seq;
}

template<typename T>
int ListSequence<T>::GetLength() const {
    return this->list->GetLength();
}

template<typename T>
Sequence<T>* ListSequence<T>::Append(T item) {
    this->list->Append(item);
    return Instance();
}

template<typename T>
Sequence<T>* ListSequence<T>::Prepend(T item) {
    this->list->Prepend(item);
    return Instance();
}

template<typename T>
Sequence<T>* ListSequence<T>::InsertAt(T item, int index) {
    this->list->InsertAt(item, index);
    return Instance();
}

template<typename T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* seq) {
    int len = seq->GetLength();
    for (int i = 0; i < len; i++) {
        this->list->Append(seq->Get(i));
    }
    return Instance();
}

template<typename T>
Sequence<T>* ListSequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* arr = new T[len];
    for (int i = 0; i < len; i++) {
        arr[i] = func(this->list->Get(i));
    }
    Sequence<T>* seq = new MutableListSequence<T>(arr, len);
    delete[] arr;
    return seq;
}

template<typename T>
T ListSequence<T>::Reduce(T (*func)(T, T), T init) const {
    int len = GetLength();
    T result = init;
    for (int i = 0; i < len; i++) {
        result = func(this->list->Get(i), result);
    }
    return result;
}

template<typename T>
Sequence<Sequence<T>*>* ListSequence<T>::Split(bool (*predicate)(T)) const {
    std::vector<Sequence<T>*> parts;
    int len = GetLength();
    int start = 0;
    for (int i = 0; i < len; i++) {
        if (predicate(this->list->Get(i))) {
            if (i > start)
                parts.push_back(GetSubsequence(start, i - 1));
            start = i + 1;
        }
    }
    if (start < len)
        parts.push_back(GetSubsequence(start, len - 1));
    int partsCount = parts.size();
    Sequence<Sequence<T>*>* seq = new MutableListSequence<Sequence<T>*>(parts.data(), partsCount);
    return seq;
}

template<typename T>
Sequence<T>* ListSequence<T>::Slice(int index, int count, Sequence<T>* replacement) {
    int len = GetLength();
    if (index < 0)
        index = len + index;
    if (index < 0 || index >= len)
        throw std::out_of_range("IndexOutOfRange");
    int newLen = len - count + replacement->GetLength();
    T* newArr = new T[newLen];
    for (int i = 0; i < index; i++) {
        newArr[i] = this->list->Get(i);
    }
    for (int i = 0; i < replacement->GetLength(); i++) {
        newArr[index + i] = replacement->Get(i);
    }
    for (int i = index + count; i < len; i++) {
        newArr[i - count + replacement->GetLength()] = this->list->Get(i);
    }
    delete this->list;
    this->list = new LinkedList<T>(newArr, newLen);
    delete[] newArr;
    return Instance();
}

template<typename T>
ListSequence<T>* ListSequence<T>::Clone() const {
    return new MutableListSequence<T>(*this);
}

#endif
