#ifndef HASHTABLE_TPP
#define HASHTABLE_TPP

#include "../include/hashtable.h"
// De acuerdo a la prueba de colisiones y la tasa que arroja, se elige la función xor
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <iomanip>

using namespace std;

unsigned long best_hash(const string& key, int bits) {
    // uso semilla FNV-1a para mejor distribución
    // hashig d cadenas y datos pequeños
    unsigned long long hash_value = 0;
    const unsigned long long fnv_prime = 0x100000001b3;
    hash_value = 0xcbf29ce484222325;

    for (char c : key) {
        hash_value ^= static_cast<unsigned char>(c); // XOR con el byte actual
        hash_value *= fnv_prime; // Multiplicación por el primo FNV
    }

    // Si se desea limitar a un número específico de bits (útil para el análisis, no tanto para el índice)
    if (bits < 64) {
        unsigned long mask = (1UL << bits) - 1;
        return hash_value & mask;
    }
    return hash_value;
}

// Constructor
template<typename T>
HashTable<T>::HashTable(size_t initial_capacity) : table(initial_capacity), current_size(0) {}

// hash interno para mapear el tamaño actual
template<typename T>
size_t HashTable<T>::hash(const string& key) const {
    // 64 bits para el hash intermedio para tener una buena distribución
    unsigned long h = best_hash(key, 64);
    return h % table.size(); // Módulo con el tamaño actual de la tabla
}

// Redimensionar
template<typename T>
void HashTable<T>::resize() {
    // primos cercanos a potencia 2
    static const size_t prime_sizes[] = {
        17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853
    };

    size_t target_size = table.size() * 2;
    size_t new_capacity = target_size;

    for (size_t prime : prime_sizes)
    {
        if (prime > target_size) {
            new_capacity = prime;
            break;
        }
    }

    if (new_capacity == target_size) {
        new_capacity = target_size * 2 + 1; // Duplicar y asegurar que sea impar
    }

    vector<list<KeyValuePair>> new_table(new_capacity);

    // Re-hash de todos los elementos existentes
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            // Calcular nuevo índice en nueva tabla
            unsigned long h = best_hash(pair.first, 64);
            size_t new_index = h % new_capacity; // Módulo con el nuevo tamaño de la tabla para indice
            new_table[new_index].push_back(pair);
        }
    }
    // Reemplazar la tabla vieja por la nueva
    table = move(new_table);
}

// Insertar o actualizar un par clave-valor
template<typename T>
void HashTable<T>::setKey(const string& key, T value) {
    // Comprobar factor de carga y redimensionar si es necesario
    // Un factor de carga > 0.75 es un umbral común
    if (static_cast<double>(current_size) / table.size() > 0.75) {
        resize();
    }

    size_t index = hash(key);
    auto& bucket = table[index];

    // Buscar si la clave ya existe para actualizarla
    for (auto& pair : bucket) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }

    // Si no se encuentra, insertatr
    bucket.emplace_back(key, value);
    current_size++; // aumentar tamaño
}

// Actualizar valor
template<typename T>
bool HashTable<T>::setValue(const string& key, T new_value) {
    if (current_size == 0) {
        return false;  // Tabla vacía
    }

    size_t index = hash(key);
    auto& bucket = table[index];

    // Buscar la clave en el bucket
    for (auto& pair : bucket) {
        if (pair.first == key) {
            // Clave encontrada, actualizar valor
            pair.second = new_value;
            return true;
        }
    }

    // Clave no encontrada
    return false;
}

// Obtener valor
template<typename T>
optional<T> HashTable<T>::getKey(const string& key) const {
    size_t index = hash(key);
    const auto& bucket = table[index];

    for (const auto& pair : bucket) {
        if (pair.first == key) {
            return pair.second; // Clave encontrada
        }
    }

    return nullopt; // No se encontró la clave
}

// Limpiar
template<typename T>
void HashTable<T>::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    current_size = 0;
}

// Mostrar tabla
template<typename T>
void HashTable<T>::display() const {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║             Visualización de HashTable           ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║ Elementos totales: " << current_size
         << " | Buckets: " << table.size()
         << " | Factor de carga: " << fixed << setprecision(2)
         << static_cast<double>(current_size) / table.size() << " ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;

    // Estadísticas
    size_t buckets_ocupados = 0;
    size_t max_colisiones = 0;

    // Mostrar buckets
    for (size_t i = 0; i < table.size(); ++i) {
        size_t elementos = table[i].size();

        if (elementos > 0) {
            buckets_ocupados++;
            max_colisiones = max(max_colisiones, elementos);
        }

        cout << "║ Bucket " << setw(3) << left << i << " │ ";

        if (table[i].empty()) {
            cout << "□ (vacío)";
        } else {
            bool primero = true;
            for (const auto& par : table[i]) {
                if (!primero) cout << " → ";
                primero = false;
                cout << "■ \"" << par.first << "\":" << par.second;
            }
        }
        cout << endl;
    }

    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║ Estadísticas:                                    ║" << endl;
    cout << "║ - Buckets ocupados: " << buckets_ocupados << "/" << table.size()
         << " (" << fixed << setprecision(1)
         << (buckets_ocupados * 100.0) / table.size() << "%)          ║" << endl;
    cout << "║ - Máxima longitud de colisión: " << max_colisiones << "           ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
}

#endif // HASHTABLE_TPP