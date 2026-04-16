#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

template <typename T>

class CustomArray {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;

    public:
        CustomArray() : data_(new T[16]), size_(0), capacity_(16) {}
        
        // Rule of 5
        // 1. Destructor
        // 2. Copy Constructor
        // 3. Copy Assignment Operator
        // 4. Move Constructor
        // 5. Move Assignment Operator
        // This is purely for learning purposes...
        // Using unique_ptr<T[]> would be much more smarter
        ~CustomArray() {
            delete[] data_;
        }

        // Deep Copy Constructor
        // 'other' is the pre-existing object
        // E.g. (CustomArray b = a;)
        CustomArray(const CustomArray& other)
            : data_(new T[other.capacity_]),
              size_(other.size_),
              capacity_(other.capacity_) {

            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

        // Copy Assignment Operator
        // CustomArray a; -> Already exists
        // CustomArray b; -> Already exists
        // b = a; 'other is a'
        CustomArray& operator=(const CustomArray& other) {
            
            if (this == &other) return *this; // Self-assignment
            
            data_ = new T[other.capacity_]; // Alocate first before deleting!

            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;

            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }

            return *this; 
        }

        // Move Consturctor
        CustomArray(CustomArray&& other) noexcept
            : data_(other.data_),
              size_(other.size_),
              capacity_(other.capacity_) {
            
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        // Move Operator
        CustomArray& operator=(CustomArray&& other) noexcept {

            if (this == &other) return *this;

            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity = 0;

            return *this; 
        }


        // Element access
        T& operator[](size_t index) {
            if (index >= size_) {
                throw std::out_of_range("CustomArray: index out of bounds");
            }
            return data_[index];
        }

        T& at(size_t index) {
            if (index >= size_) {
                throw std::out_of_range("CustomArray: index out of bounds");
            }
            return data_[index];
        }

        T& front() {
            if (empty()) {
                throw std::out_of_range("CustomArray: front() on empty array");
            }
            return data_[0];
        }

        T& back() {
            if (empty()) {
                throw std::out_of_range("CustomArray: back() on empty array");
            }
            return data_[size_ - 1];
        }

        // Capacity
        bool empty() const { return size_ == 0; }
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }

        // Raw access
        T* data() { return data_; }

        // Insertions
};





int main() {

    CustomArray<int> test_arr;

    return 0;
} 