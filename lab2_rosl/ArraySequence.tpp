#ifndef ARRAYSEQUENCE_TPP
#define ARRAYSEQUENCE_TPP

#include "ArraySequence.h"

template<typename T>
ArraySequence<T>::ArraySequence(T* arr, int count) {
    this->items = new DynamicArray<T>(arr, count);
}

template<typename T>
ArraySequence<T>::ArraySequence() {
    this->items = new DynamicArray<T>(0);
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) {
    int size = other.GetLength();
    T* temp = new T[size];
    for (int i = 0; i < size; i++) {
        temp[i] = other.items->Get(i);
    }
    this->items = new DynamicArray<T>(temp, size);
    delete[] temp;
}

template<typename T>
ArraySequence<T>::~ArraySequence() {
    delete this->items;
}

template<typename T>
T ArraySequence<T>::GetFirst() const {
    if (GetLength() == 0)
        throw std::out_of_range("IndexOutOfRange");
    return this->items->Get(0);
}

template<typename T>
T ArraySequence<T>::GetLast() const {
    int len = GetLength();
    if (len == 0)
        throw std::out_of_range("IndexOutOfRange");
    return this->items->Get(len - 1);
}

template<typename T>
T ArraySequence<T>::Get(int index) const {
    return this->items->Get(index);
}

template<typename T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
        throw std::out_of_range("IndexOutOfRange");
    int newSize = endIndex - startIndex + 1;
    T* newItems = new T[newSize];
    for (int i = 0; i < newSize; i++) {
        newItems[i] = this->items->Get(startIndex + i);
    }
    ArraySequence<T>* seq = new MutableArraySequence<T>(newItems, newSize);
    delete[] newItems;
    return seq;
}

template<typename T>
int ArraySequence<T>::GetLength() const {
    return this->items->GetSize();
}

template<typename T>
Sequence<T>* ArraySequence<T>::Append(T item) {
    int oldSize = GetLength();
    this->items->Resize(oldSize + 1);
    this->items->Set(oldSize, item);
    return Instance();
}

template<typename T>
Sequence<T>* ArraySequence<T>::Prepend(T item) {
    int oldSize = GetLength();
    T* newArr = new T[oldSize + 1];
    newArr[0] = item;
    for (int i = 0; i < oldSize; i++) {
        newArr[i + 1] = this->items->Get(i);
    }
    delete this->items;
    this->items = new DynamicArray<T>(newArr, oldSize + 1);
    delete[] newArr;
    return Instance();
}

template<typename T>
Sequence<T>* ArraySequence<T>::InsertAt(T item, int index) {
    int len = GetLength();
    if (index < 0 || index > len)
        throw std::out_of_range("IndexOutOfRange");
    T* newArr = new T[len + 1];
    for (int i = 0; i < index; i++) {
        newArr[i] = this->items->Get(i);
    }
    newArr[index] = item;
    for (int i = index; i < len; i++) {
        newArr[i + 1] = this->items->Get(i);
    }
    delete this->items;
    this->items = new DynamicArray<T>(newArr, len + 1);
    delete[] newArr;
    return Instance();
}

template<typename T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    int len1 = GetLength();
    int len2 = list->GetLength();
    T* newArr = new T[len1 + len2];
    for (int i = 0; i < len1; i++) {
        newArr[i] = this->items->Get(i);
    }
    for (int i = 0; i < len2; i++) {
        newArr[len1 + i] = list->Get(i);
    }
    ArraySequence<T>* seq = new MutableArraySequence<T>(newArr, len1 + len2);
    delete[] newArr;
    return seq;
}

template<typename T>
Sequence<T>* ArraySequence<T>::Map(T (*func)(T)) const {
    int len = GetLength();
    T* newArr = new T[len];
    for (int i = 0; i < len; i++) {
        newArr[i] = func(this->items->Get(i));
    }
    ArraySequence<T>* seq = new MutableArraySequence<T>(newArr, len);
    delete[] newArr;
    return seq;
}

template<typename T>
T ArraySequence<T>::Reduce(T (*func)(T, T), T init) const {
    int len = GetLength();
    T result = init;
    for (int i = 0; i < len; i++) {
        result = func(this->items->Get(i), result);
    }
    return result;
}

template<typename T>
Sequence<Sequence<T>*>* ArraySequence<T>::Split(bool (*predicate)(T)) const {
    std::vector<Sequence<T>*> parts;
    int len = GetLength();
    int start = 0;
    for (int i = 0; i < len; i++) {
        if (predicate(this->items->Get(i))) {
            if (i > start)
                parts.push_back(GetSubsequence(start, i - 1));
            start = i + 1;
        }
    }
    if (start < len)
        parts.push_back(GetSubsequence(start, len - 1));
    int partsCount = parts.size();
    ArraySequence<Sequence<T>*>* seq = new MutableArraySequence<Sequence<T>*>(parts.data(), partsCount);
    return seq;
}

template<typename T>
Sequence<T>* ArraySequence<T>::Slice(int index, int count, Sequence<T>* replacement) {
    int len = GetLength();
    if (index < 0)
        index = len + index;
    if (index < 0 || index >= len)
        throw std::out_of_range("IndexOutOfRange");
    int newLen = len - count + replacement->GetLength();
    T* newArr = new T[newLen];
    for (int i = 0; i < index; i++) {
        newArr[i] = this->items->Get(i);
    }
    for (int i = 0; i < replacement->GetLength(); i++) {
        newArr[index + i] = replacement->Get(i);
    }
    for (int i = index + count; i < len; i++) {
        newArr[i - count + replacement->GetLength()] = this->items->Get(i);
    }
    delete this->items;
    this->items = new DynamicArray<T>(newArr, newLen);
    delete[] newArr;
    return Instance();
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Clone() const {
    return new MutableArraySequence<T>(*this);
}

#endif
