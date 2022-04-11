#include <iostream>
#include <optional>
#include <assert.h>

using namespace std;

// This file contains a simple code sample that shows my 
// object-oriented programming skills in C++.
//
// Since I have not written any C++, C#, Java, or C code
// that I am allowed to share, I have written a simple 
// class that implements a linked list data structure
// and several public methods that do common operations
// on it.

template <class T>
struct Node {
    public:
        T val;
        Node<T>* next;
};

template <class T>
class LinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;
        size_t size;
    public:
        LinkedList() {
            head = NULL;
            tail = NULL;
            size = 0;
        }
        ~LinkedList() {
            auto cur = head;
            while (cur != NULL) {
                auto next = cur->next;
                delete cur;
                cur = next;
            }
        }

        // len returns the current length of the list
        size_t len() {
            return this->size;
        }

        // append adds val to the end of the list
        void append(T val) {
            auto node = new Node<T>;
            node->val = val;
            node->next = NULL;

            if (this->head == NULL) {
                this->head = node;
                this->tail = node;
            } else {
                this->tail->next = node;
                this->tail = node;
            }
            this->size++;
        }

        // pop removes the first element of the list
        // or returns nullopt if the list is empty
        optional<T> pop() {
            // if there's no head, return nothing
            if (this->head == NULL) {
                return nullopt;
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

        // get returns the node at index idx, or none if 
        // no such node exists
        optional<T> get(size_t idx) {
            auto cur = this->head;
            size_t i = 0;
            while(NULL != cur) {
                if (i == idx) {
                    return optional<T>(cur->val);
                }
                cur = cur->next;
                i++;
            }
            return nullopt;
        }
};

int main() {
    // basic invariant checks
    LinkedList<int> l;
    assert(l.len() == 0);
    assert(l.get(0) == nullopt);
    assert(l.get(123) == nullopt);
    
    // append a bunch of elements, checking size and
    // the get function after each push.
    const size_t num_pushes = 200;
    for (size_t i = 0; i < num_pushes; i++) {
        l.append(i);
        assert(l.len() == i + 1);
        auto gotten = l.get(i);
        assert(gotten.has_value());
        assert(gotten.value() == i);
        // one index off the end should not
        // have a value
        assert(!l.get(i+1).has_value());
    }
    assert(l.len() == num_pushes);
    
    // next pop all the elements, checking size 
    // after each pop
    for (size_t i = 0; i < num_pushes; i++) {
        auto popped = l.pop();
        assert(popped.has_value());
        assert(popped.value() == i);
        assert(l.len() == num_pushes - i - 1);
    }

    assert(l.len() == 0);

    cout << "All tests passed" << endl;
    return 0;
}
