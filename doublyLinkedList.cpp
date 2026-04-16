#include <memory>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

template <typename T>

class DoublyLinkedList {
    private:
        struct Node {
            T data;
            Node* prev;
            Node* next;
        };
    
        Node* head_;
        Node* tail_;
        size_t size_;

        void free_mem() {

            while (head_) {
                Node* temp = head_->next;
                delete head_;
                head_ = temp; 
            }

            tail_ = nullptr;
            size_ = 0; 
        }
    
    public:

        // Iterator
        class iterator {
            private:
                Node* cur_;

            public:
                iterator(Node* node) : cur_(node) {}

                T& operator*() { return cur_->data; }

                iterator& operator++() {
                    cur_ = cur_->next;

                    return *this; 
                }

                iterator& operator--() {
                    cur_ = cur_->prev;
                    
                    return *this;
                }

                bool operator==(const iterator& other) const {
                    return cur_ == other.cur_;
                }

                bool operator!=(const iterator& other) const {
                    return cur_ != other.cur_;
                }

                friend class DoublyLinkedList<T>;
        };
        
        // Rule of Five
        DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

        ~DoublyLinkedList() { free_mem(); }

        DoublyLinkedList(const DoublyLinkedList& other) 
            : head_(nullptr), tail_(nullptr), size_(0) {
            
            Node* cur = other.head_;

            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }

        DoublyLinkedList(DoublyLinkedList&& other) noexcept
            : head_(other.head_), tail_(other.tail_), size_(other.size_) {
            
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }

        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            
            if (this == &other) { return this; }
            
            // Free all memory of 'this' 
            free_mem();

            Node* cur = other.head_;

            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }

            return this; 
        }

        DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {

            if (this == &other) { return this; }

            // Free all memory of 'this'
            free_mem();

            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;


            return this; 
        }


        // Element Access
        Node* front() { return head_; }
        Node* back() { return tail_; }

        // Modifiers
        void push_front(T val) {

            Node* temp = new Node{val, nullptr, head_};

            if (head_) {
                head_->prev = temp;
            } else {
                tail_ = temp;
            }

            head_ = temp; 
            size_++;
        }

        void push_back(T val) {
            Node* temp = new Node{val, tail_, nullptr};

            if (tail_) {
                tail_->next = temp;
            } else {
                head_ = temp;
            }

            tail_ = temp;
            size_++;
        }

        void pop_front() {
            if (!head_) return;

            Node* temp = head_;
            head_ = head_->next;

            if (head_) {
                head_->prev = nullptr;
            } else {
                tail_ = nullptr;  // list became empty
            }

            delete temp;
            size_--;
        }

        void pop_back() {
            if (!tail_) return;

            Node* temp = tail_;
            tail_ = tail_->prev;

            if (tail_) {
                tail_->next = nullptr;
            } else {
                head_ = nullptr;
            }

            delete temp;
            size_--;
        }

        void clear() {
            free_mem();
        }

};


int main() {

    return 0;
}