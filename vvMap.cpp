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
        
};

int main() {
    
    return 0; 
}