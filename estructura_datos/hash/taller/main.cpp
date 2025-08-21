#include "./include/hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>

using namespace std;
// 1UL << bits calcula 2^bits
unsigned long hash_sum(const string& key, int bits)
{
    unsigned long long sum = 0;
    for (char c : key)
    {
        sum += static_cast<unsigned char>(c);
    }
    unsigned long mask = (1UL << bits) - 1;
    return sum & mask;
};
unsigned long hash_prod(const string& key, int bits)
{
    unsigned long long product = 1;
    for (char c : key) {
        product *= (static_cast<unsigned char>(c) + 1);
    }
    // problema en anagramas -> solucion: usar un primo grande
    unsigned long mask = (1UL << bits) - 1;
    return product & mask;
};
unsigned long hash_xor(const string& key, int bits)
{
    // unsigned long long hash_value = 0;
    // const int chunk_size = sizeof(unsigned long long); // Procesar en trozos de 64 bits (8 bytes)
    //
    // for (size_t i = 0; i < key.length(); i += chunk_size) {
    //     unsigned long long chunk = 0;
    //     // Copiar trozo de la cadena en variable 'chunk'
    //     // min(chunk_size, key.length() - i) trozo si no es completo
    //     memcpy(&chunk, key.c_str() + i, min((size_t)chunk_size, key.length() - i));
    //     hash_value ^= chunk;
    // }
    //
    // //unsigned long mask = (1UL << bits) - 1;
    // return hash_value; //& mask;
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
};

void analyze_hash_function(
    const string& name,
    unsigned long (*hash_func)(const string&, int),
    const vector<string>& words,
    int bits)
{
    set<unsigned long> unique_hashes;
    int collisions = 0;
    long total_words = words.size();

    for (const auto& word : words) {
        unsigned long hash = hash_func(word, bits);
        // Si el hash ya está en el set, es una colisión
        if (unique_hashes.count(hash)) {
            collisions++;
        } else {
            unique_hashes.insert(hash);
        }
    }

    double collision_rate = static_cast<double>(collisions) / total_words;

    // --- CÁLCULO DE LA TASA ESPERADA ---
    long k = total_words;
    double N = static_cast<double>(1UL << bits); // Número total de posibles hashes
    // La fórmula del problema del cumpleaños estima el número esperado de colisiones
    double expected_collisions = k - N * (1.0 - std::pow(1.0 - 1.0/N, k));
    // Una aproximación más simple para cuando k es mucho menor que N es: (k * (k - 1.0)) / (2.0 * N)
    // double expected_collisions_approx = (static_cast<double>(k) * (k - 1.0)) / (2.0 * N);

    double expected_rate = expected_collisions / total_words;

    cout << "--- Análisis para: " << name << " (" << bits << " bits) ---" << endl;
    cout << "Palabras totales: " << total_words << endl;
    cout << "Colisiones encontradas: " << collisions << std::endl;
    cout << "Tasa de colisión: " << collision_rate * 100.0 << "%" << endl;
    cout << "Colisiones esperadas (ideal): ~" << static_cast<int>(expected_collisions)
              << " (" << expected_rate * 100.0 << "%)" << endl;
    cout << endl;
}

int main() {
    string path;
    #ifdef _WIN32
        // Windows
        path = "C:/Users/BGinvestments/software-development/c++/cpp-learning/estructura_datos/hash/taller/words.txt"; // modificar de acuerdo al lugar de almacenamiento
    #else
        // Linux/Unix
        path = "/usr/share/dict/words";
    #endif
    ifstream word_file(path);
    if (!word_file) {
        cout << "Error: No se pudo abrir el archivo words.txt" << endl;
        return 1;
    }

    vector<string> words;
    string word;
    while (getline(word_file, word)) {
        // Algunas versiones del archivo tienen \r al final en Windows
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }
        words.push_back(word);
    }
    cout << "Se cargaron " << words.size() << " palabras." << endl;

    HashTable<string> words_table;
    for (const auto& w : words) {
        words_table.setKey(w, w);
    }

    // cout << "==================================================" << endl;
    // cout << "               ANÁLISIS DE HASHING" << endl;
    // cout << "==================================================" << endl;

    // // Analizar para 8 bits
    // analyze_hash_function("Suma de Caracteres", hash_sum, words, 8);
    // analyze_hash_function("Producto de Caracteres", hash_prod, words, 8);
    // analyze_hash_function("XOR por Trozos", hash_xor, words, 8);

    // // Analizar para 14 bits
    // analyze_hash_function("Suma de Caracteres", hash_sum, words, 14);
    // analyze_hash_function("Producto de Caracteres", hash_prod, words, 14);
    // analyze_hash_function("XOR por Trozos", hash_xor, words, 14);

    // // Pruebas hash table
    // HashTable<int> my_table;

    // cout << "Insertando elementos..." << endl;
    // my_table.setKey("uno", 1);
    // my_table.setKey("dos", 2);
    // my_table.setKey("diez", 10);
    // my_table.setKey("test", 123);

    // cout << "El valor de 'dos' es: " << my_table.getKey("dos").value_or(-1) << endl;
    // cout << "El valor de 'diez' es: " << my_table.getKey("diez").value_or(-1) << endl;

    // // Actualizar un valor existente
    // cout << "Actualizando 'uno' a 111..." << endl;
    // my_table.setKey("uno", 111);
    // cout << "El nuevo valor de 'uno' es: " << my_table.getKey("uno").value_or(-1) << endl;
    // if (my_table.setValue("uno", 42)) {
    //     cout << "Valor actualizado correctamente" << endl;
    // } else {
    //     cout << "La clave no existe en la tabla" << endl;
    // }

    // // Probar una clave que no existe
    // if (!my_table.getKey("cinco")) {
    //     cout << "La clave 'cinco' no fue encontrada (correcto)." << endl;
    // }

    // // Probar con tipo de dato string
    // HashTable<string> string_table;
    // string_table.setKey("nombre", "Juan");
    // string_table.setKey("apellido", "Perez");
    // cout << "El valor de 'nombre' es: " << string_table.getKey("nombre").value_or("N/A") << endl;

    // // mostrar tabla
    // my_table.display();
    // string_table.display();
    words_table.display();
    return 0;
}


