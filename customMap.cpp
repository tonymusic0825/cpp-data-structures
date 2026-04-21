#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <functional>
#include <stdexcept>

using namespace std;

template<typename K, typename V>

class CustomHashMap {
    private:
        struct Node {
            K key;
            V value;
            Node* next;

            Node(const K& k, const V& v)
                : key(k), value(v), next(nullptr) {}
        };

        Node** buckets_;
        size_t capacity_;
        size_t size_;
        float max_load_factor_;

        std::hash<K> hasher_;

    public:

        // Rule of 5
        CustomHashMap(size_t initial_capacity = 16)
            : capacity_(initial_capacity), size_(0), max_load_factor_(0.75f) {
            buckets_ = new Node*[capacity_]();
        }

        // Destructor 
        ~CustomHashMap() {
            for (size_t i = 0; i < capacity_; ++i) {
                Node* curr = buckets_[i];
                while (curr) {
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
            }
            delete[] buckets_;
        }

        // Copy Constructor 
        CustomHashMap(const CustomHashMap& other) {
            capacity_ = other.capacity_;
            size_ = other.size_;
            max_load_factor_ = other.max_load_factor_;

            buckets_ = new Node*[capacity_]();

            for (size_t i = 0; i < capacity_; ++i) {
                Node* curr = other.buckets_[i];
                Node** tail = &buckets_[i];

                while (curr) {
                    *tail = new Node(curr->key, curr->value);
                    tail = &((*tail)->next);
                    curr = curr->next;
                }
            }
        }

        // Move Constructor 
        CustomHashMap(CustomHashMap&& other) noexcept
            : buckets_(other.buckets_),
            capacity_(other.capacity_),
            size_(other.size_),
            max_load_factor_(other.max_load_factor_) {

            other.buckets_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }

        CustomHashMap& operator=(const CustomHashMap& other) {

            for (size_t i = 0; i < capacity_; ++i) {
                Node* curr = buckets_[i];
                while (curr) {
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
            }
            delete[] buckets_;
            
            if (this == &other) return *this;

            deleteBuckets();
            copyFrom(other);
            return *this;
        }
};

int main() {
    
    return 0; 
}