#pragma once

#include <functional>
#include <cassert>
#include <stdexcept>

// non-owning wrapper for references
template<typename T>
using Ref = std::reference_wrapper<T>;


// non-owning wrapper for pointers, works like a smart pointer without being smart
template<typename T>
class Ptr
{   
public:
    constexpr Ptr(T *ptr) : pointer(ptr) {}
    constexpr Ptr(const Ptr &other) : pointer(other.pointer) {}
    template<typename U> constexpr Ptr(const Ptr<U> &other) : pointer(other.get()) {}

    constexpr operator T*() const { return pointer; }
    constexpr T& operator*() const { return *pointer; }
    constexpr T* operator->() const { return pointer; }
    constexpr Ptr& operator=(const Ptr &other) { if (this != &other) { pointer = other.pointer; } return *this; }

    [[nodiscard]] constexpr T* get() const { return pointer; }

private:
    T *pointer{};
};
