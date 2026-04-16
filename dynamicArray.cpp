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
        CustomArray()
            : data_(new T[16]), size_(0), capacity_(16) {}

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