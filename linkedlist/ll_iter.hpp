#pragma once

#include <memory>

#include "ll.hpp"
#include "node.hpp"

// LinkedListIterator is a standards-compliant C++ input_iterator.
// See this link for more detail on what an input_iterator is:
// https://www.cplusplus.com/reference/iterator/InputIterator/
template <typename T>
class LinkedListIterator {
    using Ptr = std::shared_ptr<Node<T>>;

    private:
        Ptr cur;
    public:
        LinkedListIterator(Ptr startNode): cur(startNode) {}

        LinkedListIterator(const LinkedListIterator<T>& other) {
            this->cur = other.cur;
        }

        ~LinkedListIterator() {}

        bool operator==(const LinkedListIterator<T>& other) {
            return (
                this->cur->val == other.cur->val &&
                this->cur->next == other.cur->next
            );
        }

        T operator*() {
            return this->cur->val;
        }

        bool operator!=(const LinkedListIterator<T>& other) {
            return !(*this == other);
        }

        LinkedListIterator<T>& operator=(LinkedListIterator<T> other) {
            LinkedListIterator formerThis(*this);
            this->cur = other.cur;
            return formerThis;
        }

        const LinkedListIterator<T>& operator++() {
            if(this->cur->next != NULL) {
                this->cur = this->cur->next;
            }
            return *this;
        }

        void swap(LinkedListIterator<T> &other) {
            auto tmpOtherCur = other.cur;
            other.cur = this->cur;
            this->cur = tmpOtherCur;
        }
};
