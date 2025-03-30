#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include <vector>

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* items;
public:
    ArraySequence(T* items, int count);
    ArraySequence();
    ArraySequence(const ArraySequence<T>& other);
    virtual ~ArraySequence();
    
    virtual T GetFirst() const;
    virtual T GetLast() const;
    virtual T Get(int index) const;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const;
    virtual int GetLength() const;
    
    virtual Sequence<T>* Append(T item);
    virtual Sequence<T>* Prepend(T item);
    virtual Sequence<T>* InsertAt(T item, int index);
    virtual Sequence<T>* Concat(Sequence<T>* list);
    
    virtual Sequence<T>* Map(T (*func)(T)) const;
    virtual T Reduce(T (*func)(T, T), T init) const;
    
    virtual Sequence<Sequence<T>*>* Split(bool (*predicate)(T)) const;
    virtual Sequence<T>* Slice(int index, int count, Sequence<T>* replacement);
    
    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* Clone() const;
};

template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
    virtual ArraySequence<T>* Instance() override {
        return this;
    }
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
    virtual ArraySequence<T>* Instance() override {
        return this->Clone();
    }
};

#include "ArraySequence.tpp"
#endif
