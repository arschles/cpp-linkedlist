#pragma once

#include <functional>

namespace linkedlist {
// find_fn is the type of the function used in
// LinkedList<T>::find. The function will be
// applied for each element in the list, in
// order, and be passed the index of that
// element and its value. it should return
// true if that element is considered "found"
// and false otherwise.
template <typename T>
using find_fn = std::function<bool(size_t, const T&)>;

// for_each_fn is the type of the function used
// in LinkedList<T>::for_each. The function is 
// called in the same way as find_fn, but it
// should not return any value.
template <typename T>
using for_each_fn = std::function<void(size_t, const T&)>;

// map_fn is the type of the function used in
// LinkedList<T>::map<U>. The function is called
// in the same way as find_fn is, but it should
// return the transformed value for each element.
template <typename T, typename U>
using map_fn = std::function<U(size_t, T)>;

// reduce_fn is the type of function used in 
// LinkedList<T>::reduce<U>. The intention of
// this function is to collapse an entire list
// into a single value. this result is achieved
// by doing the following:
//
// 1. starting with a given initial value, called the
// accumulator
// 2. passing the value from (1) to the function along
// with the index of the first element in the list
// and its value
// 3. using the function's return value as the new
// accumulator and returning to (2)
template <typename T, typename U>
using reduce_fn = std::function<U(size_t, const U&, const T&)>;

}// linkedlist
