#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    T* data;
    int size;
public:
    DynamicArray(T* items, int count) : size(count) {
        data = new T[count];
        for (int i = 0; i < count; i++) {
            data[i] = items[i];
        }
    }
    DynamicArray(int size) : size(size) {
        if (size < 0)
            throw std::invalid_argument("Size must be non-negative");
        data = new T[size];
    }
    DynamicArray(const DynamicArray<T>& other) : size(other.size) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    ~DynamicArray() { delete[] data; }
    
    T Get(int index) const {
        if (index < 0 || index >= size)
            throw std::out_of_range("IndexOutOfRange");
        return data[index];
    }
    void Set(int index, T value) {
        if (index < 0 || index >= size)
            throw std::out_of_range("IndexOutOfRange");
        data[index] = value;
    }
    int GetSize() const { return size; }
    void Resize(int newSize) {
        if (newSize < 0)
            throw std::invalid_argument("newSize must be non-negative");
        T* newData = new T[newSize];
        int copySize = (newSize < size) ? newSize : size;
        for (int i = 0; i < copySize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
};

#endif
