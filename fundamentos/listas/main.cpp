#include <iostream>
#include <string>
#include <vector> // para usar std::vector
#include <array> // para usar std::array 
// el array es un contenedor que almacena elementos de un tipo determinado
// en una secuencia lineal, pero con un tamaño fijo
#include <algorithm> // para funciones como sort, find
using std::cout; // permite imprimir en consola
using std::endl; // fin de línea, equivalente a '\n'
using std::find; // para buscar un elemento en un contenedor
using std::sort; // para ordenar contenedores
using std::distance; // para calcular la distancia entre iteradores
using std::max_element; // para encontrar el elemento máximo en un rango
using std::min_element; // para encontrar el elemento mínimo en un rango
using std::string; // para usar cadenas de texto (strings)
using std::vector; // vector es contenedor que organiza los elementos de un tipo determinado
// en una secuencia lineal
// una unica dimensión 
// la diferencia con un array es que el vector puede crecer o decrecer en tamaño

int main(){
    // ==========================================
    // USO Y MANIPULACIÓN BÁSICA DE LISTAS 
    // ==========================================

    cout << "=== USO Y MANIPULACIÓN BÁSICA DE LISTAS ===" << endl << endl;

    // En C++ tenemos principalmente 3 tipos de "listas":
    // 1. Arrays estáticos (arreglos tradicionales de C)
    // 2. std:array (arrays modernos de C++)
    // 3. std:vector (arrays dinámicos - los más usados)

    // ==========================================
    // 1. ARRAYS ESTÁTICOS (TRADICIONALES)
    // ==========================================
    cout << "1. ARRAYS ESTÁTICOS:" << endl;

    // Declaracióń e inicialización
    int numeros[5] = {10,20,30,40,50}; // Array de 5 elementos
    char letras[] = {'A','B','C','D'}; // Tamaño determinado por inicialización

    // Acceso a elementos (índice comienza en 0)
    cout << "Primer número: " << numeros[0] << endl;
    cout << "Último número: " << numeros[4] << endl;

    // Modificar elementos 
    numeros[2] = 35;
    cout << "Número modificado en posición 2: " << numeros[2] << endl;

    // Recorrer array con bucle for tradicional
    cout << "Todos los números: ";
    for(int i; i < 5; i++){
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Recorrer letras con range-based for
    cout << "Todas las letras: ";
    for(char letra : letras) {
        cout << letra << " ";
    }
    cout << endl << endl;

    // ==========================================
    // 2. STD::ARRAY (ARRAYS MODERNOS)
    // ==========================================
    cout << "2. STD::ARRAY (ARRAYS MODERNOS)" << endl;

    std::array<int, 4> puntajes = {85, 92, 78, 96};  // Array moderno de 4 elementos

    // Métodos útilies de std::array
    cout << "Tamaño del array: " << puntajes.size() << endl;
    cout << "Primer elemento: " << puntajes.front() << endl;
    cout << "Último elemento: " << puntajes.back() << endl;

    // Acceso seguro con at() (lanza excepción si está fuera del rango)
    cout << "Elemento en posición 1: " << puntajes.at(1) << endl;

    // Recorrer con iteradores
    cout << "Todos los puntajes: ";
    for(auto it = puntajes.begin(); it != puntajes.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    cout << "Con range: ";
    for(int valor : puntajes){
        cout << valor << " ";
    }

    // ==========================================
    // 3. STD::VECTOR (ARRAYS DINÁMICOS)
    // ==========================================
    cout << "3. STD::VECTOR (ARRAYS DINÁMICOS):" << endl;

    // Declaracion e inicialización de vectors
    vector<int> lista_vacia;                        // Vector vacío
    vector<int> temperaturas = {25, 28, 22, 30};    // Vector con valore iniciales
    vector<string> nombres(3, "Desconocido");       // 3 elementos, todos "Desconocido"
    vector<double> precios(5);                      // 5 elementos inicializados en 0.0

    cout << "Vector inicial de temperaturas: ";
    for(int temp : temperaturas){
        cout << temp << "ºC ";
    }
    cout << endl;

    // ==========================================
    // OPERACIONES BÁSICAS CON VECTORS
    // ==========================================
    cout << "\nOPERACIONES BÁSICAS CON VECTORS:" << endl;

    // Añadir elementos al final
    temperaturas.push_back(32);
    temperaturas.push_back(27);

    cout << "Después de push_back: ";
    for(int temp : temperaturas){
        cout << temp << "ºC ";
    }
    cout << endl;

    // Información del vector
    cout << "Tamaño actual: " << temperaturas.size() << endl;
    cout << "Capacidad: " << temperaturas.capacity() << endl;
    cout << "¿Está vacío? " << (temperaturas.empty() ? "Sí" : "No") << endl;

    // Acceso a elementos
    cout << "Primera temperatura: " << temperaturas.front() << "ºC" << endl;
    cout << "Última temperatura: " << temperaturas.back() << "ºC" << endl;
    cout << "Temperatura en posición 2: " << temperaturas[2] << "ºC" << endl;

    // Modificar elementos
    temperaturas[1] = 26;
    cout << "Después de modificar posición 1: " << temperaturas[1] << "ºC" << endl;

    // Eliminar último elemento
    temperaturas.pop_back();
    cout << "Despues de pop_back, tamaño: " << temperaturas.size() << " elementos" << endl;

    // Insertar en posición específica
    temperaturas.insert(temperaturas.begin() + 1, 24);  // Insertar 24 en posición 1
    cout << "Después de insertar 24 en posición 1: ";
    for(int temp : temperaturas){
        cout << temp << "ºC ";
    }
    cout << endl;

    // Eliminar elementos en posición específica
    temperaturas.erase(temperaturas.begin() + 2);   // Eliminar elemento en posición 2
    cout << "Después de eleminar en posición 2: ";
    for(int temp : temperaturas){
        cout << temp << "ºC ";
    }
    cout << endl << endl; 

    // ==========================================
    // BÚSQUEDA Y ORDENAMIENTO
    // ==========================================
    cout << "BÚSQUEDA Y ORDENAMIENTO:" << endl;

    vector<int> numeros_vector = {64, 34, 25, 12, 22, 11, 90};

    cout << "Vector original: ";
    for(int num : numeros_vector){
        cout << num << " ";
    }
    cout << endl;

    // Buscar un elemento
    int buscar = 25;
    auto it = find(numeros_vector.begin(), numeros_vector.end(), buscar);
    if(it != numeros_vector.end()){
        int posicion = distance(numeros_vector.begin(), it);
        cout << "Elemento " << buscar << " encontrado en posición: " << posicion << endl;
    } else {
        cout << "Elemento " << buscar << " no encontrado" << endl;
    }

    // Ordenar el vector
    sort(numeros_vector.begin(), numeros_vector.end());
    cout << "Vector ordenado: ";
    for(int num : numeros_vector){
        cout << num << " ";
    }
    cout << endl;

    // Encontrar el máximo y mínimo
    auto max_it = std::max_element(numeros_vector.begin(), numeros_vector.end());
    auto min_it = std::min_element(numeros_vector.begin(), numeros_vector.end());
    cout << "Valor máximo: " << *max_it << endl;
    cout << "Valor mínimo: " << *min_it << endl;

    cout << endl;

    // ==========================================
    // VECTOR 2D (MATRIZ)
    // ==========================================
    cout << "VECTOR 2D (MATRIZ):" << endl;

    // Crear una matriz 3x3
    vector<vector<int>> matriz = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Matriz 3x3:" << endl;
    for(size_t i = 0; i < matriz.size(); i++){
        for(size_t j= 0; j < matriz[i].size(); j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    // Acceso y modificación
    matriz[1][1] = 50;  // Cambiar el elemento central
    cout << "Elemento central modificado: " << matriz[1][1] << endl;

    cout << endl;

    // ==========================================
    // OPERACIONES ÚTILES ADICIONALES
    // ==========================================
    cout << "OPERACIONES ÚTILES ADICIONALES:" << endl;

    vector<int> lista1 = {1,2,3};
    vector<int> lista2 = {4,5,6};

    cout << "Lista 1: ";
    for(int num : lista1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Lista 2: ";
    for(int num : lista2) {
        cout << num << " ";
    }
    cout << endl;

    // Concatenar vectors
    lista1.insert(lista1.end(), lista2.begin(), lista2.end());
    cout << "Lista concatenada: ";
    for(int num : lista1) {
        cout << num << " ";
    }
    cout << endl;

    // Limpiar vector
    vector<int> para_limpiar = {1,2,3,4,5};
    cout << "Tamaño antes de clear(): " << para_limpiar.size() << endl;
    para_limpiar.clear();
    cout << "Tamaño después de clear(): " << para_limpiar.size() << endl;

    // Redimensiona vector
    vector<int> redimensionable(3,10);  // 3 elementos con valor 10
    cout << "Vector original (3 elementos): ";
    for(int num : redimensionable){
        cout << num << " ";
    }
    cout << endl << endl;

    // ==========================================
    // BUENAS PRÁCTICAS Y CONSEJOS
    // ==========================================
    cout << "BUENAS PRÁCTICAS Y CONSEJOS:" << endl;
    cout << "1. Usar std::vector para la mayoría de casos (dinámico y flexible)" << endl;
    cout << "2. Usar std::array cuando el tamaño es fijo y conocido en tiempo de compilación" << endl;
    cout << "3. Evitar arrays estáticos C-style en código moderno" << endl;
    cout << "4. Siempre verifica los límites para evitar accesos fuera de rango" << endl;
    cout << "5. Usar range-based for loops cuando sea posible (más legible)" << endl;
    cout << "6. Reservar memoria con reserve() si conoces el tamaño aproximado" << endl;
    cout << "7. Usar const cuando no vas a modificar el vector" << endl;

    // Ejemplo de reserve()
    vector<int> optimizado;
    optimizado.reserve(1000);   // Reservar espacio para 1000 elementos
    cout << "\nVector con memoria reservada - Capacidad: " << optimizado.capacity() << endl;

    return 0;
}