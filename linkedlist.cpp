#include <iostream>
#include <optional>

using namespace std;

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
        int size;
    public:
        LinkedList() {
            head = NULL;
            tail = NULL;
            size = 0;
        }
        ~LinkedList() {
            Node<T> *cur = head;
            while (cur != NULL) {
                auto next = cur->next;
                delete cur;
                cur = next;
            }
        }

        // push adds val to the end of the list
        void push(T val) {
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

        // get returns the node at index idx,
        // or none if no such node exists
        std::optional<T> get(size_t idx) {
            auto cur = this.head;
            for(size_t i = 0; i <= idx; i++) {
                if(cur == NULL) {
                    return nullopt;
                }
                cur = cur->next;
            }
            if(cur == NULL) {
                return nullopt;
            }
            return optional<T>{cur->val};
        }
};

int main() {
    return 0;
}
