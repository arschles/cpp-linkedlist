#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>

#include "ll_funcs.hpp"
#include "node.hpp"

namespace linkedlist {

template <typename T>
class LinkedList {
    private:
        Node<T> *first;
        Node<T> *last;
        size_t size;
    
    public:
        
        ///// 
        // constructors and destructor
        /////
        LinkedList(): first(NULL), last(NULL), size(0) {}

        explicit LinkedList(const LinkedList<T>& other): first(NULL), last(NULL), size(0) {
            other.forEach([this](size_t idx, const T& val) {
                this->append(val);
            });
        }
        
        ~LinkedList() {
            auto cur = this->first;
            while (cur != NULL) {
                auto next = cur->next;
                delete cur;
                cur = next;
            }
        }
        
        /////
        // operators
        /////
        bool operator==(const LinkedList<T>& other) const {
            if (this->size != other.size) {
                return false;
            }
            
            Node<T>* otherCur = other.first;
            // iterate each list item by item and compare
            // values. in the reduce, the accumulator starts
            // off as true. the first element in this that 
            // is not equal to other sets the accumulator
            // to false, and it remains that for all
            // subsequent elements.
            return this->reduce<bool>(true, [&otherCur](size_t idx, const bool accum, T elt) {
                auto otherVal = otherCur->val;
                auto ret = accum && (elt == otherVal);
                otherCur = otherCur->next;
                return ret;
            });
        };

        bool operator!=(const LinkedList<T>& other) const {
            return !(*this==other);
        };

        /////
        // modifiers
        /////

        // swap swaps the contents of other with this linked list and returns the
        // previous contents of this one. the returned value will be a copy of the 
        // contents of this linked list before the call to swap.
        std::shared_ptr<LinkedList<T>> swap(const std::shared_ptr<LinkedList<T>> other) {
            auto ret = std::make_shared<LinkedList<T>>(*this);
            this->first = NULL;
            this->last = NULL;
            this->size = 0;
            Node<T>* otherNode = other->first;
            other->forEach([this](size_t idx, const T& val) {
                this->append(val);
            });
            
            return ret;
        }

        // append adds val to the end of the list
        void append(const T& val) {
            auto node = new Node<T>(val);

            if (this->first == NULL) {
                this->first = node;
                this->last = node;
            } else {
                this->last->next = node;
                this->last = node;
            }
            this->size++;
        }

        // appends adds all values in elts, in order, to
        // the end of this
        void append(const std::shared_ptr<LinkedList<T>> elts) {
            elts->forEach([this](size_t idx, const T& val) {
                this->append(val);
            });
        }
        
        /////
        // getters
        /////
        
        // get returns the node at index idx, or nullopt if 
        // no such node exists. this is an O(N) operation.
        std::optional<T> get(size_t idx) const {
            return this->find([idx] (size_t this_idx, T val) {
                return idx == this_idx;
            });
        }

        // len returns the current length of the list
        size_t len() const {
            return this->size;
        };
        
        // first returns the first element in the list
        // if there is one, or nullopt otherwise
        std::optional<T> head() const {
            return this->find([](size_t idx, T val) {
                return idx == 0;
            });
        }

        // tail returns a new list containing all elements
        // except the head, if any elements exists. otherwise,
        // returns nullopt
        std::optional<std::shared_ptr<LinkedList<T>>> tail() const {
            if(this->first == NULL || this->first->next == NULL) {
                return std::nullopt;
            }
            auto ret = std::make_shared<LinkedList<T>>();
            auto cur = this->first->next;
            while(cur != NULL) {
                ret->append(cur->val);
                cur = cur->next;
            }
            return ret;
        }

        // middle returns the value in the middle of the
        // list. if no items exist in the list, returns
        // nullopt. if the list has an odd number of 
        // items in it, middle returns the item closer
        // to the end of the list
        std::optional<T> middle() const {
            const size_t mid_idx = this->size / 2;
            return this->get(mid_idx);
        }

        // pop removes the first element of the list
        // or returns nullopt if the list is empty
        std::optional<T> pop() {
            // if there's no first, return nothing
            if (this->first == NULL) {
                return std::nullopt;
            }

            auto curFirst = this->first;
            auto newFirst = this->first->next;
            if (newFirst == NULL) {
                // if the new first is null,
                // set everything to null and 0
                this->first = NULL;
                this->last = NULL;
                this->size = 0;
            } else {
                // otherwise, there is a new first
                // so set the official first to 
                // the new first and decrement the size
                this->first = newFirst;
                this->size--;
            }
            auto ret = curFirst->val;
            delete curFirst;
            return ret;
        }

        // reverse reverses this linked list in place
        void reverse() {
            // if the list has 0 or 1 elements, do nothing
            if (this->size < 2) {
                return;
            }
            // otherwise, visit every node in the list and
            // reverse the next pointer of each. for each 
            // node visited, we'll need to keep track of the
            // previous node so that we can set the
            // current node's next pointer to the previous
            auto oldFirst = this->first;
            auto cur = oldFirst;
            Node<T> * prev = NULL;
            while (cur != NULL) {
                auto oldNext = cur->next;
                cur->next = prev;
                prev = cur;
                cur = oldNext;
            }
            // after we finish visiting all nodes,
            // the prev pointer will be pointing to the 
            // new first of the list.
            this->first = prev;
            this->last = oldFirst;
        }
        
        /////
        // transformers
        /////

        // map iterates this list, applies fn to each element in the
        // list, constructs a new list with the results and returns
        // it
        template <typename U>
        std::shared_ptr<LinkedList<U>> map(map_fn<T, U> fn) const {
            // calling flatMap here is a few lines less code,
            // but refactoring ends up being difficult because clang
            // compile errors are prohibitive when you get something
            // wrong. I'd rather use a little duplication and allow
            // for code that is approximately as easy to read
            // but much easier to refactor.
            auto ret = std::make_shared<LinkedList<U>>();
            this->forEach([fn, ret](size_t idx, const T& val) {
                ret->append(fn(idx, val));
            });
            return ret;
        }


        // note that flat_map_fn should not go into ll_funcs.hpp 
        // because it references LinkedList, and that would be a circular reference
        template<typename U>
        using flat_map_fn = std::function<std::shared_ptr<LinkedList<U>>(size_t, const T&)>;

        template<typename U>
        std::shared_ptr<LinkedList<U>> flatMap(flat_map_fn<U> fn) const {
            auto ret = std::make_shared<LinkedList<U>>();
            auto cur = this->first;
            size_t i = 0;
            while(cur != NULL) {
                auto new_list = fn(i++, cur->val);
                ret->append(new_list);
                cur = cur->next;
            }
            return ret;
        }

        // forEach iterates through each element in this list and
        // calls fn for each, sequentially and in order.
        void forEach(const for_each_fn<T>& fn) const {
            auto cur = this->first;
            size_t i = 0;
            while(cur != NULL) {
                fn(i++, cur->val);
                cur = cur->next;
            }
        }

        // find returns the first element whose value 
        // satisfies fn(index, value), or none if no
        // such element exists.
        std::optional<T> find(find_fn<T> fn) const {
            auto cur = this->first;
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

        // filter returns a new list containing all elements
        // for which fn returned true
        std::shared_ptr<LinkedList<T>> filter(find_fn<T> fn) const {
            return this->flatMap<T>([fn](size_t idx, const T& val) {
                auto ret = std::make_shared<LinkedList<T>>();
                if (fn(idx, val)) {
                    ret->append(val);
                }
                return ret;
            });
        }

        // partition returns two lists. the first contains
        // all the elements, in order, for which
        // fn returned true. the second contains all
        // elements, in order, for which fn returned
        // false.
        std::pair<
            std::shared_ptr<LinkedList<T>>,
            std::shared_ptr<LinkedList<T>>
        > partition(
            find_fn<T> fn
        ) const {
            auto list1 = std::make_shared<LinkedList<T>>();
            auto list2 = std::make_shared<LinkedList<T>>();
            this->forEach([fn, list1, list2](size_t idx, const T& val) {
                if(fn(idx, val)) {
                    list1->append(val);
                } else {
                    list2->append(val);
                }
            });
            return std::make_pair(list1, list2);
        }

        // reduce collapses the entire list into a single value.
        // see reducer_fn documentation in ll_funcs.hpp for
        // more detail.
        template <typename U>
        U reduce(const U& accum, reduce_fn<T, U> fn) const {
            auto cur = this->first;
            U ret = accum;
            this->forEach([&ret, fn](size_t idx, const T& val) {
                ret = fn(idx, ret, val);
            });
            return ret;
        }

        // zip returns a new linked list in wihch the elements of this
        // and elements of other are alternated (like a zipper). In
        // all alternations, elements from this list come first.
        //
        // for example, if this is [1, 2, 3] and other is [4, 5, 6, 7],
        // the newly returned linked list is [1, 4, 2, 5, 3, 6, 7].
        //
        // Note that if the lists are not the same size, the longer
        // one continues without alternation after all elements
        // are exhausted in the shorter one.
        const std::shared_ptr<LinkedList<T>> zip(const std::shared_ptr<LinkedList<T>> other) const {
            // this could use reduce or flatMap, but this code
            // ends up being shorter and slighly more straightforward
            // to read
            auto ret = std::make_shared<LinkedList<T>>();
            auto thisCur = this->first;
            auto otherCur = other->first;
            while((thisCur != NULL) || (otherCur != NULL)) {
                if(thisCur != NULL) {
                    ret->append(thisCur->val);
                    thisCur = thisCur->next;
                }
                if(otherCur != NULL) {
                    ret->append(otherCur->val);
                    otherCur = otherCur->next;
                }
            }
            return ret;
        };
};
} // linkedlist
