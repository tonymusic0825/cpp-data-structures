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
            
            if (this == &other) { return this*; }
            
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

            if (this == &other) { return this*; }

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



};


int main() {

    return 0;
}