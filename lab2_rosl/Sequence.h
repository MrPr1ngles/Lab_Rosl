#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdexcept>

template<typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    virtual T Reduce(T (*func)(T, T), T init) const = 0;

    virtual Sequence<Sequence<T>*>* Split(bool (*predicate)(T)) const = 0;
    virtual Sequence<T>* Slice(int index, int count, Sequence<T>* replacement) = 0;
    
    virtual ~Sequence() {}
};

#endif
