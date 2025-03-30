#ifndef ARRAYSEQUENCEITERATOR_H
#define ARRAYSEQUENCEITERATOR_H

#include "IEnumerable.h"
#include "ArraySequence.h"

template<typename T>
class ArraySequenceIterator : public IEnumerator<T> {
private:
    const ArraySequence<T>* sequence;
    int index;
public:
    ArraySequenceIterator(const ArraySequence<T>* seq) : sequence(seq), index(-1) {}
    virtual bool MoveNext() override {
        if (index + 1 < sequence->GetLength()) {
            index++;
            return true;
        }
        return false;
    }
    virtual T Current() const override {
        if (index < 0 || index >= sequence->GetLength())
            throw std::out_of_range("Iterator out of range");
        return sequence->Get(index);
    }
    virtual void Reset() override {
        index = -1;
    }
};

#endif
