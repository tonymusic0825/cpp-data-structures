#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

template <typename T>

class CustomArray {
    private:
        T* data;
        size_t size;
        size_t capacity;

    public:

        CustomArray() : data(new T[16]), size(0), capacity(16) {}

        T& operator[](size_t index) {
            
            if (index < size || index >= size) {
                throw std::out_of_range("CustomArray: Index out of bounds");
            }

            return data[index];
        }

        T front() {

            if (size < 1) {
                throw std::out_of_range("CustomArray:front array is empty")
            }

            return data[0];
        }

        T back() {

            if (size < 1) {
                throw std::out_of_range("CustomArray:back array is empty")
            }

            return data[size-1];
        }

        T at(size_t index) {
            
            if (index < 0 || index >= size) {
                throw std::out_of_range("CustomArray: Index out of bounds");
            }

            return data[index];
        }

        bool empty() {
            return (size == 0);
        }

        size_t size() {
            return size;
        }

        size_t capacity() {
            return capacity;
        }

        T* data() {
            return data;
        }

        




};





int main() {

    CustomArray<int> test_arr;

    return 0;
} 