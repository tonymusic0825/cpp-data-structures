#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
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
            
            T* temp = new T[other.capacity_]; // Alocate first before deleting!

            
            for (size_t i = 0; i < other.size_; ++i) {
                temp[i] = other.data_[i];
            }
            
            delete[] data_;

            data_ = temp;
            size_ = other.size_;
            capacity_ = other.capacity_;
            
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
            other.capacity_ = 0;

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

        void shrink_to_fit() {

            if (size_ == capacity_) { return; }

            // If empty
            if (size_ == 0) {
                delete[] data;
                data_ = nullptr;
                capacity_ = 0;
                return;                 
            }

            T* temp = new T[size_];

            for (size_t i = 0; i < size_; ++i) {
                temp[i] = std::move(data_[i]);
            }

            delete[] data_;


            data_ = temp; 
            capacity_ = size_;
        }

        void reserve(size_t new_cap) {

            if (capacity_ >= new_cap) { return; }

            T* temp = new T[new_cap];

            for (size_t i = 0; i < size_; ++i) {
                temp[i] = move(data_[i]);
            }

            delete[] data_;
            data_ = temp;
            capacity_ = new_cap;
        }


        // Raw access
        T* data() { return data_; }


        // Modifiers
        void push_back(const T& val) {

            // Check if array is currently full
            if (size_ == capacity_) { 
                
                T* temp = new T[capacity_*2];

                for (size_t i = 0; i < size_; ++i) {
                    temp[i] = move(data_[i]);
                }

                delete[] data_;
                data_ = temp;
                capacity_ *= 2; 
            }
            
            data_[size_++] = val;
        }

        void pop_back() {
            if (size_ > 0) {
                data_[size_ - 1].~T();

                --size_;
            }
        }

        void erase(size_t index) {
            if (index >= size_) {
                throw std::out_of_range("CustomArray: erase() index out of bounds");
            }

            data_[index].~T();

            for (size_t i = index; i < size_ - 1; ++i) {
                data_[i] = move(data_[i + 1]);
            }
        }

        void insert(size_t index, const T& val) {
            if (index >= size_) {
                throw std::out_of_range("CustomArray: insert() index out of bounds");
            }

            // Check if current array is full
            if (size_ == capacity_) { 
                
                T* temp = new T[capacity_*2];

                for (size_t i = 0; i < index; ++i) {
                    temp[i] = move(data_[i]);
                }

                temp[index] = val;

                for (size_t i = index + 1; i < size_; ++i) {
                    temp[i] = move(data_[i]);
                }

                delete[] data_;
                data_ = temp;
                capacity_ *= 2; 

            } else {
                for (size_t i = size_ - 1; i > index; --i) {
                    data_[i + 1] = move(data_[i]); 
                }

                data_[index] = val;
            }
        }

        void clear() {
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }

            size_ = 0;
        }

};


template <typename T>

// Test code
bool compare_parity(std::vector<T>& ref, CustomArray<T>& custom) {
    if (ref.size() != custom.size()) return false;
    for (size_t i = 0; i < ref.size(); ++i) {
        if (ref[i] != custom[i]) return false;
    }
    return true;
}


int main() {

    int total_ops = 10000000;

    std::mt19937 rng(1337);
    std::uniform_int_distribution<int> op_dist(0, 5);
    std::uniform_int_distribution<int> val_dist(1, 1000000);

    // Pre-generate operations so both containers get identical workload
    std::vector<int> ops(total_ops);
    std::vector<int> vals(total_ops);

    for (int i = 0; i < total_ops; ++i) {
        ops[i] = op_dist(rng);
        vals[i] = val_dist(rng);
    }

    // -------------------------------
    // Test std::vector
    // -------------------------------
    {
        std::vector<int> ref_vec;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < total_ops; ++i) {
            int op = ops[i];
            int val = vals[i];

            switch (op) {
                case 0:
                    ref_vec.push_back(val);
                    break;
                case 1:
                    if (!ref_vec.empty()) ref_vec.pop_back();
                    break;
                case 2:
                    ref_vec.reserve(val % 2000);
                    break;
                case 3:
                    if (!ref_vec.empty()) {
                        size_t idx = val % ref_vec.size();
                        ref_vec[idx] = val;
                    }
                    break;
                case 4:
                    if (i % 10000 == 0) {
                        ref_vec.clear();
                    }
                    break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[std::vector] Time: " << diff.count() << " seconds\n";
    }

    // -------------------------------
    // Test CustomArray
    // -------------------------------
    {
        CustomArray<int> test_arr;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < total_ops; ++i) {
            int op = ops[i];
            int val = vals[i];

            switch (op) {
                case 0:
                    test_arr.push_back(val);
                    break;
                case 1:
                    if (!test_arr.empty()) test_arr.pop_back();
                    break;
                case 2:
                    test_arr.reserve(val % 2000);
                    break;
                case 3:
                    if (!test_arr.empty()) {
                        size_t idx = val % test_arr.size();
                        test_arr[idx] = val;
                    }
                    break;
                case 4:
                    if (i % 10000 == 0) {
                        test_arr.clear();
                    }
                    break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "[CustomArray] Time: " << diff.count() << " seconds\n";
    }

    return 0;
}