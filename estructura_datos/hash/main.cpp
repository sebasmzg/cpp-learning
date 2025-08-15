//=============================================================================
// ÍNDICE
// =============================================================================
//
// 0. CONCEPTOS FUNDAMENTALES
//    - ¿Qué es Hashing?
//    - Función de Hash
//    - Tabla de Hash (Hash Table)
//    - Colisiones
//    - Factor de Carga (Load Factor)
//
// 1. FUNCIONES DE HASH (EJEMPLOS)
//    1.1. Función de Hash para Enteros
//    1.2. Función de Hash para Cadenas de Texto (Strings)
//
// 2. ESTRATEGIAS DE MANEJO DE COLISIONES
//    2.1. Encadenamiento Separado (Separate Chaining) - (Implementada)
//    2.2. Direccionamiento Abierto (Open Addressing) - (Conceptual)
//         - Sondeo Lineal (Linear Probing)
//         - Sondeo Cuadrático (Quadratic Probing)
//         - Doble Hashing (Double Hashing)
//
// 3. IMPLEMENTACIÓN DE UNA TABLA DE HASH (CON ENCADENAMIENTO SEPARADO)
//    3.1. Estructura del Nodo (Clave-Valor)
//    3.2. Clase HashTable
//         - Atributos
//         - Constructor y Destructor
//    3.3. Métodos Principales
//         - hashFunction(key)
//         - insert(key, value)
//         - search(key)
//         - remove(key)
//    3.4. Funcionalidades Avanzadas
//         - rehash() (Redimensionamiento)
//         - getLoadFactor()
//    3.5. Utilidades
//         - display()
//
// 4. APLICACIONES Y PROBLEMAS COMUNES (ESTILO LEETCODE)
//    4.1. Contar Frecuencia de Elementos
//    4.2. Encontrar Duplicados en un Array
//    4.3. Problema de "Two Sum" (LeetCode 1)
//    4.4. Agrupar Anagramas (LeetCode 49)
//
// 5. INTERFAZ DE USUARIO Y PRUEBAS
//    5.1. Menú Interactivo (menu)
//    5.2. Función Principal (main)
//
// =============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <list>       // Útil para implementaciones alternativas de encadenamiento
#include <climits>    // Para INT_MIN como valor de retorno en caso de error

using namespace std;

// =============================================================================
// 0. CONCEPTOS FUNDAMENTALES
// =============================================================================
//
// - ¿Qué es Hashing?: Es el proceso de convertir una entrada de tamaño variable
//   (como un string) en una salida de tamaño fijo (un número entero), llamado
//   "valor hash".
//
// - Función de Hash: Es el algoritmo que realiza esta conversión. Una buena
//   función de hash debe ser:
//   1. Determinista: La misma entrada siempre produce la misma salida.
//   2. Rápida: Debe calcularse en tiempo O(1) o O(L) donde L es la longitud de la clave.
//   3. Uniforme: Debe distribuir las claves de manera uniforme sobre el rango
//      de salida para minimizar colisiones.
//
// - Tabla de Hash (Hash Table): Es una estructura de datos que utiliza una función
//   de hash para mapear claves a índices dentro de un array (llamado "tabla" o
//   "buckets"). Su principal ventaja es que permite inserciones, búsquedas y
//   eliminaciones en tiempo promedio O(1).
//
// - Colisiones: Ocurren cuando dos claves diferentes producen el mismo índice
//   en la tabla de hash. Son inevitables y deben ser gestionadas con una
//   estrategia de resolución de colisiones.
//
// - Factor de Carga (Load Factor): Es una medida de cuán llena está la tabla.
//   Se calcula como: (Número de elementos) / (Tamaño de la tabla).
//   Un factor de carga alto aumenta la probabilidad de colisiones. Cuando supera
//   cierto umbral (ej. 0.75), es necesario redimensionar la tabla (rehash).

// =============================================================================
// 2. ESTRATEGIAS DE MANEJO DE COLISIONES
// =============================================================================
//
// 2.1. Encadenamiento Separado (Separate Chaining):
//      - Concepto: Cada índice de la tabla apunta a una lista enlazada (u otra
//        estructura de datos) que contiene todos los elementos que hashean a ese índice.
//      - Ventajas: Simple de implementar, el rendimiento degrada gradualmente
//        con un factor de carga alto.
//      - Desventajas: Requiere memoria adicional para los punteros de la lista.
//      - ESTA ES LA ESTRATEGIA QUE IMPLEMENTAREMOS.
//
// 2.2. Direccionamiento Abierto (Open Addressing):
//      - Concepto: Todos los elementos se almacenan en la misma tabla. Cuando
//        ocurre una colisión, se busca ("sondea") el siguiente espacio disponible
//        en la tabla según una secuencia predefinida.
//      - Tipos:
//        - Sondeo Lineal: Se prueba `(hash(k) + i) % N` para i=1, 2, 3...
//          - Ventaja: Buen uso de la caché del procesador.
//          - Desventaja: Sufre de "agrupamiento primario", donde los elementos
//            tienden a formar bloques, degradando el rendimiento.
//        - Sondeo Cuadrático: Se prueba `(hash(k) + i^2) % N` para i=1, 2, 3...
//          - Ventaja: Evita el agrupamiento primario.
//          - Desventaja: Puede causar "agrupamiento secundario" y no garantiza
//            que se explore toda la tabla si no se elige bien el tamaño.
//        - Doble Hashing: Se usa una segunda función de hash: `(hash1(k) + i * hash2(k)) % N`.
//          - Ventaja: Es la técnica de sondeo más robusta, minimiza ambos tipos de agrupamiento.
//          - Desventaja: Más complejo de implementar.
// =============================================================================
// 3. IMPLEMENTACIÓN DE UNA TABLA DE HASH (CON ENCADENAMIENTO SEPARADO)
// =============================================================================

// 3.1. Estructura del Nodo (Clave-Valor)
// Cada nodo almacenará una clave (string) y un valor (int), además de un
// puntero al siguiente nodo en caso de colisión (formando una lista enlazada).
struct HashNode {
    string key;
    int value;
    HashNode* next;

    HashNode(string k, int v) : key(k), value(v), next(nullptr) {}
};

// 3.2. Clase HashTable
class HashTable {
    private:
        // La tabla es un vector de punteros a HashNode. cada elemento es un "bucket"
        vector<HashNode*> table;
        int capacity;   // Tamaño del vector (número de buckets)
        int size;       // Número total de elementos en la tabla.
        
        // 1.1 y 1.2. Función de Hash: Convierte una clave en un índice de la tabla
        int hashFunction(const string& key){
            // Se utiliza una función de hash polinominal simple, es una tecinica común y sugestiva
            // Se elige un número primo grande (31) para multiplicar, lo que ayuda a distribuir
            // mejor las claves y reducir colisiones
            unsigned long hash = 0;
            for(char c : key){
                hash = (hash * 31 + c) % capacity; // Evitar overflow y mantener dentro del rango
            }
            return hash;
        }

        // 3.4 Redimensionamiento (rehash)
        void rehash(){
            cout << "[INFO] Factor de carga superado. Realizando rehash..." << endl;
            // Guardamos la tabla actual y creamos una nueva con el doble de capacidad
            // elegir un número primo como nueva capacidad puede mejorar la distribución
            vector<HashNode*> oldTable = table;
            int oldCapacity = capacity;
            capacity = capacity * 2 + 1; // Duplicar y sumar 1 para aumentar la probabilidad de ser primo.
            table.assign(capacity, nullptr); // asignar nueva tabla
            size = 0; // El tamaño se re-calculará a insetar de nuevo

            // Recorremos tabla antigua y re-insertamos cada elemento en la nueva tabla.
            // Es necesario re-calcular el hash porque la capacidad ha cambiado
            for(int i = 0; i < oldCapacity; ++i){
                HashNode* current = oldTable[i];
                while(current != nullptr){
                    insert(current->key, current->value);
                    HashNode* toDelete = current;
                    current = current->next; // Avanzar al siguiente nodo
                    delete toDelete; // Liberar memoria del nodo antiguo
                }
            }
            cout << "[INFO] Rehash completado. Nueva capacidad: " << capacity << endl;
        }
    public:
        // Constructor: Inicializa la tabla con una capacidad inicial
        HashTable(int initialCapacity = 10){
            capacity = initialCapacity;
            size = 0;
            table.assign(capacity, nullptr); // asigna 'capacity' buckets, todos nulos
        }

        // Destructor: Libera la memoria utilizada por la tabla hash
        ~HashTable(){
            for(int i = 0; i < capacity; ++i){
                HashNode* current = table[i];
                while(current != nullptr){
                    HashNode* toDelete = current;
                    current = current->next;
                    delete toDelete;
                }
            }
        }

        // 3.4 Obtener el Factor de Carga
        double getLoadFactor(){
            return static_cast<double>(size) / capacity;
            // retorna un valor entre 0 y 1 que indica la carga de la tabla hash
        }

        // 3.3 Inserción
        void insert(const string& key, int value){
            // Antes de insertar, verifacmos si es necesario redimensionar la tabla
            // un umbral común es 0.75
            if(getLoadFactor() > 0.75){
                rehash();
            }
            int index = hashFunction(key); // Obtener el índice usando la función de hash
            HashNode* current = table[index]; // obtener el bucket correspondiente

            // Recorremos la lista enlazada en el bucket correspondiente.
            // Si la clave ya existe, actualizamos su valor
            while(current != nullptr){
                if(current->key == key){
                    cout << "[UPDATE] Clave '" << key << "' actualizada con el valor " << value << endl;
                    current->value = value; // Actualizar el valor
                    return;
                }
                current = current->next; // Avanzar al siguiente nodo
            }

            // Si la clave no existe, creamos un nuevo nodo y lo insertamos al
            // principio de la lista enlazada
            HashNode* newNode = new HashNode(key, value);
            newNode->next = table[index];
            table[index] = newNode; // Insertar el nuevo nodo al inicio del bucket
            size++; // Incrementar el tamaño de la tabla
            cout << "[INSERT] Clave '" << key << "' insertada con valor " << value << "." << endl;
        }

        // Método de búsqueda
        int search(const string& key){
            int index = hashFunction(key);
            HashNode* current = table[index];

            // Recorremos la lista enlazada en el bucket buscando la clave
            while(current != nullptr){
                if(current->key == key){
                    return current->value; // Retornar el valor asociado a la clave
                }
                current = current->next; // Avanzar al siguiente nodo
            }
            return -1; // Retornar -1 si la clave no fue encontrada
        }

        // Método eliminación
        void remove(const string& key){
            int index = hashFunction(key);
            HashNode* current = table[index];
            HashNode* prev = nullptr;

            // Recorremos la lista buscando el nodo a eliminar
            while(current != nullptr && current->key != key){
                prev = current; // Guardamos el nodo anterior
                current = current->next; // Avanzar al siguiente nodo
            }

            // si current es nullptr, la clave no estaba en la tabla
            if(current == nullptr){
                cout << "[ERROR] Clave '" << key << "' no encontrada para eliminar." << endl;
                return;
            }

            // Si el nodo a eliminar es el primero de la lista (prev es nullptr)
            if(prev == nullptr){
                table[index] = current->next; // Actualizar el bucket al siguiente nodo
            } else {
                // Si está al medio o al final de la lista
                prev->next = current->next; // Saltar el nodo actual
            }

            delete current; // Liberar memoria del nodo
            size--; // Decrementar el tamaño de la tabla
            cout << "[DELETE] Clave '" << key << "' eliminada." << endl;
        }

        // 3.5 Mostrar tabla
        void display(){
            cout << "\n--- Contenido de HashTable ---" << endl;
            cout << "Capacidad: " << capacity << " | Tamaño: " << size << " \ Factor de carga: " << getLoadFactor() << endl;
            for(int i = 0; i < capacity; ++i){
                cout << "Bucket " << i << ": ";
                HashNode* current = table[i];
                if(current == nullptr){
                    cout << "[VACIO]" << endl;
                } else {
                    while(current != nullptr){
                        cout << "[K:" << current->key << ", V:" << current->value << "] -> ";
                        current = current->next;
                    }
                    cout << "nullptr" << endl;
                }
                cout << endl;
            }
            cout << "-----------------------------------\n" << endl;
        }
    };

    void menu() {
    HashTable* ht = new HashTable(5); // Empezar con una capacidad pequeña para ver el rehash.
    int opcion;
    string key;
    int value;

    do {
        cout << "\n\t.:MENÚ TABLA DE HASH:." << endl;
        cout << "1. Insertar/Actualizar un par clave-valor" << endl;
        cout << "2. Buscar un valor por clave" << endl;
        cout << "3. Eliminar un par por clave" << endl;
        cout << "4. Mostrar tabla completa" << endl;
        cout << "5. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                cout << "Ingrese la clave (string): ";
                cin >> key;
                cout << "Ingrese el valor (int): ";
                cin >> value;
                ht->insert(key, value);
                break;
            case 2:
                cout << "Ingrese la clave a buscar: ";
                cin >> key;
                value = ht->search(key);
                if (value != INT_MIN) {
                    cout << "Valor encontrado para '" << key << "': " << value << endl;
                } else {
                    cout << "Clave '" << key << "' no encontrada." << endl;
                }
                break;
            case 3:
                cout << "Ingrese la clave a eliminar: ";
                cin >> key;
                ht->remove(key);
                break;
            case 4:
                ht->display();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        if (opcion != 5) {
             cout << "\nPresione Enter para continuar...";
             cin.ignore();
             cin.get();
        }
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (opcion != 5);
    
    // Es crucial liberar la memoria al final.
    delete ht;
    cout << "Memoria liberada. Programa terminado." << endl;
}

int main() {
    menu();
    return 0;
}

// =============================================================================
// 4. APLICACIONES Y PROBLEMAS COMUNES (ESTILO LEETCODE)
// =============================================================================
// Las tablas de hash (o `unordered_map` en C++) son extremadamente útiles para
// resolver problemas que requieren búsquedas rápidas.

/*
// 4.1. Contar Frecuencia de Elementos
// Problema: Dado un array de strings, contar cuántas veces aparece cada uno.
// Solución: Usar una tabla de hash donde la clave es el string y el valor es su frecuencia.
void contarFrecuencia() {
    vector<string> data = {"manzana", "platano", "manzana", "naranja", "platano", "manzana"};
    HashTable freqMap;
    for (const string& fruta : data) {
        int currentValue = freqMap.search(fruta);
        if (currentValue == INT_MIN) { // Si no existe
            freqMap.insert(fruta, 1);
        } else {
            freqMap.insert(fruta, currentValue + 1);
        }
    }
    freqMap.display();
}

// 4.2. Encontrar Duplicados en un Array
// Problema: Determinar si un array de números contiene algún duplicado.
// Solución: Iterar por el array. Para cada número, intentar insertarlo en una
// tabla de hash (o un set, que es una tabla de hash de solo claves). Si ya existe,
// has encontrado un duplicado. Retorna true. Si terminas el bucle, retorna false.
// Esto es O(n) en promedio, mucho mejor que el O(n^2) de comparar cada elemento con todos los demás.

// 4.3. Problema de "Two Sum" (LeetCode 1)
// Problema: Dado un array de enteros `nums` y un entero `target`, retornar los
// índices de dos números tales que su suma sea `target`.
// Solución: Usar una tabla de hash para almacenar `(valor, índice)`.
// Para cada número `x` en el array, calcula el complemento `y = target - x`.
// Busca `y` en la tabla de hash. Si lo encuentras, has hallado la solución.
// Si no, inserta `(x, su_indice)` en la tabla. Esto es O(n).

// 4.4. Agrupar Anagramas (LeetCode 49)
// Problema: Dado un array de strings, agrupar los anagramas.
// Solución: Usar una tabla de hash donde la clave es una representación canónica
// de una palabra (ej. la palabra ordenada alfabéticamente) y el valor es una
// lista de todas las palabras que son anagramas (comparten esa clave).
// ej. "eat", "tea", "ate" -> clave "aet" -> valor ["eat", "tea", "ate"]
*/