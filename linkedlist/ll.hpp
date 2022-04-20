#pragma once

#include <functional>
#include <memory>
#include <optional>

template <typename T>
struct Node {
    public:
        T val;
        Node<T>* next;
};

template <typename T>
class LinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;
        size_t size;
    
    public:
        using find_fn = std::function<bool(size_t, T)>;
        template <typename U>
        using map_fn = std::function<U(size_t, T)>;


        LinkedList(): head(NULL), tail(NULL), size(0) {}

        LinkedList(const LinkedList<T>& other): head(NULL), tail(NULL), size(0) {
            for (size_t i = 0; i < other.size; ++i) {
                auto otherVal = other.get(i).value();
                this->append(otherVal);
            }
        }
        
        ~LinkedList() {
            auto cur = this->head;
            while (cur != NULL) {
                auto next = cur->next;
                delete cur;
                cur = next;
            }
        }

        bool operator==(const LinkedList<T>& other) {
            if (this->size != other.size) {
                return false;
            }
            
            Node<T>* thisCur = this->head;
            Node<T>* otherCur = other.head;
            // iterate each list item by item and compare
            // values
            while (thisCur != NULL) {
                if (thisCur->val != otherCur->val) {
                    return false;
                }
                thisCur = thisCur->next;
                otherCur = otherCur->next;
            }
            return true;
        };

        bool operator!=(const LinkedList<T>& other) {
            return !(*this==other);
        };

        // swap swaps the contents of other with this linked list and returns the
        // previous contents of this one. the returned value will be a copy of the 
        // contents of this linked list before the call to swap.
        std::shared_ptr<LinkedList<T>> swap(const std::shared_ptr<LinkedList<T>> other) {
            auto ret = std::shared_ptr<LinkedList<T>>(new LinkedList<T>(*this));
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
            Node<T>* otherNode = other->head;
            while(otherNode != NULL) {
                this->append(otherNode->val);
                otherNode = otherNode->next;
            }
            
            return ret;
        }
        
        // len returns the current length of the list
        size_t len() const {
            return this->size;
        };
        
        // append adds val to the end of the list
        void append(const T& val) {
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

        // first returns the first element in the list
        // if there is one, or nullopt otherwise
        std::optional<T> first() const {
            if (this->head == NULL) {
                return std::nullopt;
            }
            return std::make_optional(this->head->val);
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
            if(this->head == NULL) {
                // if there's no head, there's no middle
                return std::nullopt;
            }

            // to find the middle, keep one pointer that advances
            // one node at a time, and the other that advances
            // two at a time. when the second pointer hits the
            // end, the first pointer will be in the middle.
            auto one = this->head, two=one;
            while(two->next != NULL) {
                one = one->next;
                two = two->next->next;
                if (two == NULL) {
                    break;
                }
            }

            return std::make_optional(one->val);
        }
        
        template <typename U>
        std::shared_ptr<LinkedList<U>> map(map_fn<U> fn) const {
            auto new_list = std::make_shared<LinkedList<U>>();
            auto cur = this->head;
            size_t i = 0;
            while (cur != NULL) {
                auto new_val = fn(i, cur->val);
                new_list->append(new_val);
                cur = cur->next;
            }
            return new_list;
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
        
        // get returns the node at index idx, or nullopt if 
        // no such node exists
        std::optional<T> get(size_t idx) const {
            auto cur = this->head;
            size_t i = 0;
            while(NULL != cur) {
                if (i == idx) {
                    return std::make_optional<T>(cur->val);
                }
                cur = cur->next;
                ++i;
            }
            return std::nullopt;
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

        // find returns the first element whose value 
        // satisfies fn(index, value), or none if no
        // such element exists.
        std::optional<T> find(find_fn fn) const {
            auto cur = this->head;
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
};
