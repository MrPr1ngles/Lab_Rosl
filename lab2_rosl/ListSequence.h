#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* list;
public:
    ListSequence(T* items, int count);
    ListSequence();
    ListSequence(const ListSequence<T>& other);
    virtual ~ListSequence();
    
    virtual T GetFirst() const;
    virtual T GetLast() const;
    virtual T Get(int index) const;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const;
    virtual int GetLength() const;
    
    virtual Sequence<T>* Append(T item);
    virtual Sequence<T>* Prepend(T item);
    virtual Sequence<T>* InsertAt(T item, int index);
    virtual Sequence<T>* Concat(Sequence<T>* seq);
    
    virtual Sequence<T>* Map(T (*func)(T)) const;
    virtual T Reduce(T (*func)(T, T), T init) const;
    
    virtual Sequence<Sequence<T>*>* Split(bool (*predicate)(T)) const;
    virtual Sequence<T>* Slice(int index, int count, Sequence<T>* replacement);
    
    virtual ListSequence<T>* Instance() = 0;
    virtual ListSequence<T>* Clone() const;
};

template<typename T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
    virtual MutableListSequence<T>* Instance() override {
        return this;
    }
};

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
    virtual ImmutableListSequence<T>* Instance() override {
        return this->Clone();
    }
};

#include "ListSequence.tpp"
#endif
