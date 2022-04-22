#pragma once

#include <cstdlib>

namespace linkedlist {
template <typename T>
struct Node {
    public:
        Node<T>* next;
        T val;
        
        explicit Node(const T& val): val(val), next(NULL) {}
};
} // linkedlist
