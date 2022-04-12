#ifndef LL
#define LL

#include <optional>
#include <functional>

using namespace std;

// This file contains a simple code sample that shows my 
// object-oriented programming skills in C++.
//
// Since I have not written any accessible C++, C#, Java, or 
// C code that I am allowed to share, I have written a 
// simple class that implements a linked list data structure
// along with several public methods that do common 
// operations on it.

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

        // reverse reverses this linked list
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
            auto cur = this->head;
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

        template <class U>
        U reduce(U init, function<U(U, size_t, T)> fn) {
            U accum = init;
            auto cur = this->head;
            size_t idx = 0;
            while (cur != NULL) {
                accum = fn(accum, idx, cur->val);
                cur = cur->next;
                idx++;
            }
            return accum;
        }
};

#endif
