#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <functional>
#include <stdexcept>

using namespace std;

template<typename K, typename V>

class vvMap {
    private:
        struct Pair {
            K key;
            V value; 

            Pair(K k, V v) : key(std::move(k)), value(std::move(v)) {}
        };

        float loadf_ = 0.75f;
        vector<vector<Pair>> table_;
        size_t capacity_ = 0;
        size_t size_ = 0;
        
        std::hash<K> hasher_;

        size_t get_hash(const K& key, size_t cap) const {
            return hasher_(key) % cap; 
        }
    
    public:
        
        // Constructor
        vvMap(size_t initial_cap = 64) : capacity_(initial_cap) { 
            table_.resize(capacity_); 
        }

        void rehash(size_t new_cap) {
            vector<vector<Pair>> new_table(new_cap);

            for (auto& bucket : table_) {
                for (auto& pair: bucket) {
                    size_t idx = get_hash(pair.key, new_cap);
                    new_table[idx].push_back(std::move(pair));
                }
            }

            table_ = std::move(new_table);
            capacity_ = new_cap; 
        }

        void insert(const K& key, const V& value) {
            // Check load factor and resize
            if (loadf_ <= (float) size_ / capacity_) {
                rehash(capacity_*2);
            }

            // Check if key already exists
            size_t idx = get_hash(key, capacity_);
            vector<Pair>& bucket = table_[idx];

            for (Pair& pair : bucket) {
                if (pair.key == key) {
                    pair->value = value;
                    return;
                }
            }

            bucket.emplace_back(key, value);
            size_++;
        }

        V& operator[](const K& key) {
            size_t idx = get_hash(key, capacity_);

            for (Pair& pair : table_[idx]) {
                if (pair.key == key) {
                    return pair.value;
                }
            }

            // Add key if it doesn't exist
            // Check load factor
            if (loadf_ <= (float) size_ / capacity_) {
                rehash(capacity_*2);
                idx = get_hash(key, capacity_);
            }

            table_[idx].emplace_back(key, V());
            size_++; 

            return table_[idx].back().value;
        }

        V& at(const K& key) {
            size_t idx = get_hash(key, capacity_);

            for (Pair& pair : table_[idx]) {
                if (pair.key == key) {
                    return pair.value;
                }
            }

            throw std::out_of_range("Key not found in vvMap operator[]");
        }

        bool erase(const K& key) {
            size_t idx = get_hash(key, capacity_);
            vector<Pair>& bucket = table_[idx];

            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->key == key) {
                    *it = std::move(bucket.back());
                    bucket.pop_back();
                    size_--;
                    return true;
                }
            }

            return false;
        }

};

int main() {
    
    return 0; 
}