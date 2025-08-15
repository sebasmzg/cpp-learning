#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include <optional>
#include <utility>

using namespace std;

unsigned long best_hash(const string& key, int bits);

template<typename T>

class HashTable {
    public:
        HashTable(size_t initial_capacity = 16);

        // Insert or update a key-value pair.
        void setKey(const string& key, T value);
        bool setValue(const string& key, T new_value);

        // Get value by key. Returns nullopt if key is not found.
        optional<T> getKey(const string& key) const;

        // Remove all key-value pairs from the hash table.
        void clear();

        void display() const;
    private:
        // Almacenar clave y valor juntos
        using KeyValuePair = std::pair<std::string, T>;

        // Chaining
        vector<std::list<KeyValuePair>> table;
        size_t current_size;

        // Función de hash interna
        size_t hash(const std::string& key) const;

        // Redimensionar
        void resize();
};
#include "../src/hashtable.tpp"

#endif //HASHTABLE_H
