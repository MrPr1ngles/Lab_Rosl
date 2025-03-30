#ifndef OPTION_H
#define OPTION_H

#include <stdexcept>
#include <utility>

template<typename T>
class Option {
private:
    bool has_value;
    T value;
public:
    Option() : has_value(false) {}
    Option(const T& val) : has_value(true), value(val) {}
    Option(T&& val) : has_value(true), value(std::move(val)) {}
    bool IsSome() const { return has_value; }
    bool IsNone() const { return !has_value; }
    T& Unwrap() {
        if (!has_value)
            throw std::runtime_error("Option has no value");
        return value;
    }
};

#endif
