#ifndef IENUMERABLE_H
#define IENUMERABLE_H

template<typename T>
class IEnumerator {
public:
    virtual bool MoveNext() = 0;
    virtual T Current() const = 0;
    virtual void Reset() = 0;
    virtual ~IEnumerator() {}
};

template<typename T>
class IEnumerable {
public:
    virtual IEnumerator<T>* GetEnumerator() const = 0;
    virtual ~IEnumerable() {}
};

#endif
