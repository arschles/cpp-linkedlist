#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <optional>

#include "ll_funcs.hpp"
#include "node.hpp"

namespace linkedlist {

template <typename T>
class LinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;
        size_t size;
    
    public:
        
        ///// 
        // constructors and destructor
        /////
        LinkedList(): head(NULL), tail(NULL), size(0) {}

        explicit LinkedList(const LinkedList<T>& other): head(NULL), tail(NULL), size(0) {
            other.for_each([this](size_t idx, const T& val) {
                this->append(val);
            });
        }
        
        ~LinkedList() {
            auto cur = this->head;
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
            
            Node<T>* otherCur = other.head;
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
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
            Node<T>* otherNode = other->head;
            other->for_each([this](size_t idx, const T& val) {
                this->append(val);
            });
            
            return ret;
        }

        // append adds val to the end of the list
        void append(const T& val) {
            auto node = new Node<T>(val);

            if (this->head == NULL) {
                this->head = node;
                this->tail = node;
            } else {
                this->tail->next = node;
                this->tail = node;
            }
            this->size++;
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
        std::optional<T> first() const {
            return this->find([](size_t idx, T val) {
                return idx == 0;
            });
        }

        // last returns the last element in the list
        // if there is one, or nullopt otherwise
        std::optional<T> last() const {
            if (this->tail == NULL) {
                return std::nullopt;
            }
            return std::make_optional(this->tail->val);
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
            // if there's no head, return nothing
            if (this->head == NULL) {
                return std::nullopt;
            }

            auto curHead = this->head;
            auto newHead = this->head->next;
            if (newHead == NULL) {
                // if the new head is null,
                // set everything to null and 0
                this->head = NULL;
                this->tail = NULL;
                this->size = 0;
            } else {
                // otherwise, there is a new head
                // so set the official head to 
                // the new head and decrement the size
                this->head = newHead;
                this->size--;
            }
            auto ret = curHead->val;
            delete curHead;
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
            auto old_head = this->head;
            auto cur = old_head;
            Node<T> * prev = NULL;
            while (cur != NULL) {
                auto old_next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = old_next;
            }
            // after we finish visiting all nodes,
            // the prev pointer will be pointing to the 
            // new head of the list.
            this->head = prev;
            this->tail = old_head;
        }
        
        /////
        // transformers
        /////

        // map iterates this list, applies fn to each element in the
        // list, constructs a new list with the results and returns
        // it
        template <typename U>
        std::shared_ptr<LinkedList<U>> map(map_fn<T, U> fn) const {
            auto new_list = std::make_shared<LinkedList<U>>();
            auto cur = this->head;
            size_t i = 0;
            while (cur != NULL) {
                auto new_val = fn(i, cur->val);
                new_list->append(new_val);
                cur = cur->next;
                ++i;
            }
            return new_list;
        }

        // for_each iterates through each element in this list and
        // calls fn for each, sequentially and in order.
        void for_each(const for_each_fn<T>& fn) const {
            auto cur = this->head;
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

        // reduce collapses the entire list into a single value.
        // see reducer_fn documentation in ll_funcs.hpp for
        // more detail.
        template <typename U>
        U reduce(const U& accum, reduce_fn<T, U> reducer) const {
            auto cur = this->head;
            U ret = accum;
            size_t i = 0;
            while(cur != NULL) {
                ret = reducer(i++, ret, cur->val);
                cur = cur->next;
            }
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
            // this could use reduce or flatMap, but the code ends up being
            // shorter with just a normal loop
            auto ret = std::make_shared<LinkedList<T>>();
            auto thisCur = this->head;
            auto otherCur = other->head;
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
