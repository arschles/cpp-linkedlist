#pragma once

#include "ll.hpp"
#include "node.hpp"

namespace linkedlist {

// LinkedListTransformers houses static functions that
// implement the member functions that transform LinkedList
template <typename T>
class LinkedListTransformers {
    public:
    
    // reduce collapses the list down to a single value.
    // see the comments on reduce_fn in ll_funcs.hpp.
    template<typename U>
    static U& reduce(
        const U& accum,
        reduce_fn<T, U> fn,
        Node<T>* head
    ) {
        auto cur = head;
        auto cur_accum = accum;
        while(cur != NULL) {
            cur_accum = reducer(cur_accum, cur->value);
            cur = cur->next;
        }
        return cur_accum;
    }

    // find returns the first element whose value 
    // satisfies fn(index, value), or none if no
    // such element exists.
    static std::optional<T> find(
        find_fn<T> fn,
        Node<T>* head
    ) {
        auto cur = head;
        size_t idx = 0;
        while (cur != NULL) {
            if (fn(idx, cur->val)) {
                return std::make_optional(cur->val);
            }
            cur = cur->next;
            ++idx;
        }
        return std::nullopt;
    }
}; // LinkedListTransformers

} // linkedlist
