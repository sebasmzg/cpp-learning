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
#include <list>          // Útil para implementaciones alternativas de encadenamiento
#include <climits>       // Para INT_MIN como valor de retorno en caso de error
#include <unordered_map> // Para problemas LeetCode con hash maps
#include <unordered_set> // Para problemas LeetCode con hash sets
#include <algorithm>     // Para sort() en agrupar anagramas

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
            cout << "Capacidad: " << capacity << " | Tamaño: " << size << " | Factor de carga: " << getLoadFactor() << endl;
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

    // Declaración anticipada de la función para usarla en el menu
    void demostrarProblemasLeetCode();

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
        cout << "5. Demostrar problemas LeetCode (Índice 4)" << endl;
        cout << "6. Salir" << endl;
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
                demostrarProblemasLeetCode();
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        if (opcion != 6) {
             cout << "\nPresione Enter para continuar...";
             cin.ignore();
             cin.get();
        }
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (opcion != 6);
    
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

// 4.1. Contar Frecuencia de Elementos
// =============================================================================
// PROBLEMA: Dado un array de strings, contar cuántas veces aparece cada uno.
// ALGORITMO: Usar una tabla de hash donde la clave es el string y el valor es su frecuencia.
// COMPLEJIDAD: O(n) tiempo, O(k) espacio (donde k = número de elementos únicos)
void contarFrecuencia() {
    cout << "\n=== 4.1 CONTAR FRECUENCIA DE ELEMENTOS ===" << endl;
    
    // Datos de ejemplo: frutas con repeticiones
    vector<string> data = {"manzana", "platano", "manzana", "naranja", "platano", "manzana", "kiwi", "naranja"};
    
    cout << "Array original: [";
    for (size_t i = 0; i < data.size(); i++) {
        cout << "\"" << data[i] << "\"";
        if (i < data.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Usando nuestra implementación de HashTable
    HashTable freqMap;
    
    // Procesamos cada elemento del array
    for (const string& fruta : data) {
        // Buscamos si el elemento ya existe en la tabla
        int currentValue = freqMap.search(fruta);
        
        if (currentValue == INT_MIN) { 
            // El elemento no existe: lo insertamos con frecuencia 1
            freqMap.insert(fruta, 1);
            cout << "Insertando '" << fruta << "' por primera vez (frecuencia: 1)" << endl;
        } else {
            // El elemento ya existe: incrementamos su frecuencia
            freqMap.insert(fruta, currentValue + 1);  // insert sobrescribe el valor
            cout << "Actualizando '" << fruta << "' (nueva frecuencia: " << (currentValue + 1) << ")" << endl;
        }
    }
    
    cout << "\nTabla de frecuencias resultante:" << endl;
    freqMap.display();
    
    // Alternativa usando std::unordered_map (más simple)
    cout << "\n--- Alternativa con std::unordered_map ---" << endl;
    unordered_map<string, int> freqMapSTL;
    for (const string& fruta : data) {
        freqMapSTL[fruta]++;  // Operador [] crea automáticamente entrada con valor 0 si no existe
    }
    
    cout << "Frecuencias usando STL:" << endl;
    for (const auto& pair : freqMapSTL) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
}

// 4.2. Encontrar Duplicados en un Array
// =============================================================================
// PROBLEMA: Determinar si un array de números contiene algún duplicado.
// ALGORITMO: Usar un set/tabla de hash para rastrear elementos ya vistos.
// COMPLEJIDAD: O(n) tiempo, O(n) espacio en el peor caso
bool encontrarDuplicados(const vector<int>& nums) {
    cout << "\n=== 4.2 ENCONTRAR DUPLICADOS EN UN ARRAY ===" << endl;
    
    cout << "Array a analizar: [";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Usamos unordered_set para rastrear elementos vistos
    unordered_set<int> vistos;
    
    for (int i = 0; i < (int)nums.size(); i++) {
        int num = nums[i];
        
        // Verificamos si ya hemos visto este número
        if (vistos.find(num) != vistos.end()) {
            cout << "¡DUPLICADO ENCONTRADO! El número " << num 
                 << " aparece en el índice " << i << " y ya había sido visto antes." << endl;
            return true;
        }
        
        // Si no lo hemos visto, lo agregamos al conjunto
        vistos.insert(num);
        cout << "Número " << num << " agregado al conjunto (índice " << i << ")" << endl;
    }
    
    cout << "No se encontraron duplicados." << endl;
    return false;
}

// 4.3. Problema de "Two Sum" (LeetCode 1)
// =============================================================================
// PROBLEMA: Dado un array de enteros y un target, encontrar dos números que sumen target.
// ALGORITMO: Hash table para almacenar (valor, índice). Para cada número x, buscar (target - x).
// COMPLEJIDAD: O(n) tiempo, O(n) espacio
vector<int> twoSum(const vector<int>& nums, int target) {
    cout << "\n=== 4.3 TWO SUM (LEETCODE 1) ===" << endl;
    
    cout << "Array: [";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "], Target: " << target << endl;
    
    // Mapa que almacena (valor, índice)
    unordered_map<int, int> valorIndice;
    
    for (int i = 0; i < (int)nums.size(); i++) {
        int numeroActual = nums[i];
        int complemento = target - numeroActual;
        
        cout << "Índice " << i << ": número = " << numeroActual 
             << ", complemento necesario = " << complemento;
        
        // Buscamos si el complemento ya existe en nuestro mapa
        auto it = valorIndice.find(complemento);
        if (it != valorIndice.end()) {
            // ¡Encontramos la solución!
            cout << " -> ¡ENCONTRADO! El complemento está en el índice " << it->second << endl;
            cout << "SOLUCIÓN: números " << complemento << " (índice " << it->second 
                 << ") + " << numeroActual << " (índice " << i << ") = " << target << endl;
            return {it->second, i};
        }
        
        // Si no encontramos el complemento, agregamos el número actual al mapa
        valorIndice[numeroActual] = i;
        cout << " -> Agregando " << numeroActual << " al mapa con índice " << i << endl;
    }
    
    cout << "No se encontró solución." << endl;
    return {};  // Vector vacío si no hay solución
}

// 4.4. Agrupar Anagramas (LeetCode 49)
// =============================================================================
// PROBLEMA: Dado un array de strings, agrupar todos los anagramas juntos.
// ALGORITMO: Usar la representación canónica (string ordenado) como clave del hash.
// COMPLEJIDAD: O(n * k log k) donde n = número de strings, k = longitud promedio de strings
vector<vector<string>> agruparAnagramas(const vector<string>& strs) {
    cout << "\n=== 4.4 AGRUPAR ANAGRAMAS (LEETCODE 49) ===" << endl;
    
    cout << "Strings de entrada: [";
    for (size_t i = 0; i < strs.size(); i++) {
        cout << "\"" << strs[i] << "\"";
        if (i < strs.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Mapa: clave = string ordenado (representación canónica), valor = grupo de anagramas
    unordered_map<string, vector<string>> grupos;
    
    for (const string& str : strs) {
        // Creamos la clave canónica ordenando los caracteres del string
        string clave = str;
        sort(clave.begin(), clave.end());
        
        cout << "String: \"" << str << "\" -> Clave canónica: \"" << clave << "\"";
        
        // Agregamos el string original al grupo correspondiente
        grupos[clave].push_back(str);
        
        cout << " -> Grupo actual: [";
        for (size_t i = 0; i < grupos[clave].size(); i++) {
            cout << "\"" << grupos[clave][i] << "\"";
            if (i < grupos[clave].size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    // Convertimos el mapa a vector de vectores
    vector<vector<string>> resultado;
    cout << "\nGrupos de anagramas encontrados:" << endl;
    int grupoNum = 1;
    for (const auto& pair : grupos) {
        cout << "Grupo " << grupoNum++ << " (clave: \"" << pair.first << "\"): [";
        for (size_t i = 0; i < pair.second.size(); i++) {
            cout << "\"" << pair.second[i] << "\"";
            if (i < pair.second.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        resultado.push_back(pair.second);
    }
    
    return resultado;
}

// Función para demostrar todos los problemas del índice 4
void demostrarProblemasLeetCode() {
    cout << "\n" << string(80, '=') << endl;
    cout << "DEMOSTRACION DE PROBLEMAS LEETCODE CON TABLAS DE HASH" << endl;
    cout << string(80, '=') << endl;
    
    // 4.1 Contar frecuencias
    contarFrecuencia();
    
    // 4.2 Encontrar duplicados
    vector<int> arrayConDuplicados = {1, 2, 3, 4, 5, 2, 6, 7};
    vector<int> arraySinDuplicados = {1, 2, 3, 4, 5, 6, 7, 8};
    
    encontrarDuplicados(arrayConDuplicados);
    encontrarDuplicados(arraySinDuplicados);
    
    // 4.3 Two Sum
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> resultado1 = twoSum(nums1, target1);
    
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> resultado2 = twoSum(nums2, target2);
    
    // 4.4 Agrupar Anagramas
    vector<string> palabras = {"eat", "tea", "tan", "ate", "nat", "bat", "tab"};
    vector<vector<string>> grupos = agruparAnagramas(palabras);
    
    cout << "\n" << string(80, '=') << endl;
    cout << "RESUMEN DE COMPLEJIDADES:" << endl;
    cout << "- Contar Frecuencias: O(n) tiempo, O(k) espacio" << endl;
    cout << "- Encontrar Duplicados: O(n) tiempo, O(n) espacio" << endl;
    cout << "- Two Sum: O(n) tiempo, O(n) espacio" << endl;
    cout << "- Agrupar Anagramas: O(n * k log k) tiempo, O(n * k) espacio" << endl;
    cout << string(80, '=') << endl;
}