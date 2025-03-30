#ifndef IGROUPRING_H
#define IGROUPRING_H

template<typename T>
class IGroup {
public:
    virtual T operation(T a, T b) const = 0;
    virtual T identity() const = 0;
    virtual T inverse(T a) const = 0;
    virtual ~IGroup() {}
};

template<typename T>
class IRing : public IGroup<T> {
public:
    virtual T multiply(T a, T b) const = 0;
};

#endif
