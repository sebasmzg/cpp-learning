#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <unordered_map>

using namespace std;

// Lista circular simple: el último nodo apunta al primero (no a nullptr)
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int v) : dato(v), siguiente(nullptr) {}
};

// ======================= INSERCIÓN =======================
Nodo* insertarInicio(Nodo* cabeza, int dato) { // (nuevo nodo será la nueva cabeza)
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza) {
        nuevo->siguiente = nuevo; // El único nodo apunta a sí mismo
        return nuevo;
    }
    Nodo* ultimo = cabeza; // Encontrar el último nodo que apunta a la cabeza
    while (ultimo->siguiente != cabeza) {
        ultimo = ultimo->siguiente;
    }
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
    ultimo->siguiente = nuevo; // El último nodo apunta al nuevo nodo
    return nuevo; // Retornar nueva cabeza
}

Nodo* insertarFinal(Nodo* cabeza, int dato) { // (mantiene la misma cabeza) 
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza) {
        nuevo->siguiente = nuevo; // El único nodo apunta a sí mismo
        return nuevo;
    }
    Nodo* ultimo = cabeza;
    while (ultimo->siguiente != cabeza) {
        ultimo = ultimo->siguiente;
    }
    ultimo->siguiente = nuevo; // El último nodo apunta al nuevo nodo
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la cabeza
    return cabeza; // Mantener la misma cabeza
}

Nodo* insertarPosicion(Nodo* cabeza, int dato, int posicion) { // Inserta en posición específica (0-indexed)
    if (!cabeza || posicion == 0) {
        return insertarInicio(cabeza, dato);
    }
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion - 1; ++i) {
        temp = temp->siguiente;
        if (temp == cabeza) break; // Si damos la vuelta completa
    }
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = temp->siguiente;
    temp->siguiente = nuevo;
    return cabeza;
}

Nodo* insertarOrdenado(Nodo* cabeza, int dato) { // Inserta en orden ascendente (asumiendo lista ordenada)
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza || dato < cabeza->dato) {
        return insertarInicio(cabeza, dato);
    }
    Nodo* temp = cabeza;
    while (temp->siguiente != cabeza && temp->siguiente->dato < dato) {
        temp = temp->siguiente;
    }
    nuevo->siguiente = temp->siguiente;
    temp->siguiente = nuevo;
    return cabeza;
}

void insertarDespuesDe(Nodo* nodo, int dato) { // Inserta después de un nodo específico
    if (!nodo) return;
    
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo->siguiente;
    nodo->siguiente = nuevo;
}

void insertarAntesDe(Nodo*& cabeza, Nodo* nodo, int dato) { // Inserta antes de un nodo específico
    if (!cabeza || !nodo) return;
    if (nodo == cabeza) {
        cabeza = insertarInicio(cabeza, dato);
        return;
    }
    Nodo* nuevo = new Nodo(dato);
    Nodo* temp = cabeza;
    while (temp->siguiente != nodo && temp->siguiente != cabeza) {
        temp = temp->siguiente;
    }
    nuevo->siguiente = nodo;
    temp->siguiente = nuevo;
}
Nodo* insertarEntreNodos(Nodo* cabeza, Nodo* nodoIzquierda, Nodo* nodoDerecha, int dato) { // Inserta entre dos nodos específicos
    if (!cabeza || !nodoIzquierda || !nodoDerecha) return cabeza;
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodoDerecha;
    nodoIzquierda->siguiente = nuevo;
    return cabeza;
}

// ======================= BÚSQUEDA =======================
Nodo* buscar(Nodo* cabeza, int valor) { // Busca el primer nodo con el valor dado
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza;
    do {
        if (temp->dato == valor) return temp;
        temp = temp->siguiente;
    } while (temp != cabeza);
    return nullptr;
}

std::vector<Nodo*> buscarTodos(Nodo* cabeza, int valor) { // Busca todos los nodos con el valor dado
    std::vector<Nodo*> resultados;
    if (!cabeza) return resultados;
    
    Nodo* temp = cabeza;
    do {
        if (temp->dato == valor) {
            resultados.push_back(temp);
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    
    return resultados;
}

int obtenerPosicion(Nodo* cabeza, int valor) { // Obtiene la posición de un valor (0-indexed)
    if (!cabeza) return -1;
    Nodo* temp = cabeza;
    int posicion = 0;
    do {
        if (temp->dato == valor) return posicion;
        temp = temp->siguiente;
        posicion++;
    } while (temp != cabeza);
    return -1;
}

Nodo* buscarMinimo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* minimo = cabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        if (temp->dato < minimo->dato) {
            minimo = temp;
        }
        temp = temp->siguiente;
    }
    return minimo;
}

Nodo* buscarMaximo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* maximo = cabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        if (temp->dato > maximo->dato) {
            maximo = temp;
        }
        temp = temp->siguiente;
    }
    return maximo;
}

Nodo* obtenerNodo(Nodo* cabeza, int posicion) {
    if (!cabeza || posicion < 0) return nullptr;
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
        if (temp == cabeza && i < posicion - 1) return nullptr; // Posición fuera de rango
    }
    return temp;
}

// ======================= ELIMINACIÓN =======================
Nodo* eliminarInicio(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    if (cabeza->siguiente == cabeza) { // Solo hay un nodo
        delete cabeza;
        return nullptr;
    }
    Nodo* ultimo = cabeza;
    while (ultimo->siguiente != cabeza) {  // Encontrar el último nodo
        ultimo = ultimo->siguiente;
    }
    Nodo* temp = cabeza;
    cabeza = cabeza->siguiente;
    ultimo->siguiente = cabeza; // El último nodo apunta a la nueva cabeza
    delete temp;
    return cabeza;
}

Nodo* eliminarFinal(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    if (cabeza->siguiente == cabeza) { // Solo hay un nodo
        delete cabeza;
        return nullptr;
    }
    Nodo* temp = cabeza; // Encontrar el penúltimo nodo
    while (temp->siguiente->siguiente != cabeza) {
        temp = temp->siguiente;
    }
    Nodo* aEliminar = temp->siguiente;
    temp->siguiente = cabeza; // El penúltimo nodo apunta a la cabeza
    delete aEliminar;
    return cabeza;
}


Nodo* eliminarValor(Nodo* cabeza, int valor) { // Elimina el primer nodo con el valor dado
    if (!cabeza) return nullptr;
    if (cabeza->dato == valor) { // Si el valor está en la cabeza
        return eliminarInicio(cabeza);
    }
    Nodo* temp = cabeza;
    while (temp->siguiente != cabeza && temp->siguiente->dato != valor) {
        temp = temp->siguiente;
    }
    if (temp->siguiente->dato == valor) {
        Nodo* aEliminar = temp->siguiente;
        temp->siguiente = aEliminar->siguiente;
        delete aEliminar;
    } 
    return cabeza;
}

Nodo* eliminarTodasOcurrencias(Nodo* cabeza, int valor) { 
    if (!cabeza) return nullptr;
    while (cabeza && cabeza->dato == valor) {  // Eliminar de la cabeza mientras sea necesario
        cabeza = eliminarInicio(cabeza);
    }
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza;
    do { // Recorrer la lista circular
        while (temp->siguiente != cabeza && temp->siguiente->dato == valor) { // Mientras el siguiente nodo tenga el valor a eliminar
            Nodo* aEliminar = temp->siguiente; // Guardar el nodo a eliminar
            temp->siguiente = aEliminar->siguiente; // Actualizar el enlace del nodo actual
            delete aEliminar; // Liberar memoria del nodo eliminado
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    } while (temp != cabeza);
    return cabeza;
}

Nodo* eliminarPosicion(Nodo* cabeza, int posicion) {
    if (!cabeza || posicion < 0) return cabeza;
    if (posicion == 0) {
        return eliminarInicio(cabeza);
    }
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion - 1; ++i) {
        temp = temp->siguiente;
        if (temp == cabeza) return cabeza; // Posición fuera de rango
    }
    if (temp->siguiente == cabeza) return cabeza; // Posición fuera de rango
    Nodo* aEliminar = temp->siguiente;
    temp->siguiente = aEliminar->siguiente;
    delete aEliminar;
    return cabeza;
}

void eliminarLista(Nodo*& cabeza) {
    if (!cabeza) return;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        Nodo* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    }
    delete cabeza;
    cabeza = nullptr;
}

Nodo* eliminarDuplicados(Nodo* cabeza) { // manteniendo primera ocurrencia
    if (!cabeza) return nullptr;
    std::unordered_set<int> vistos;
    Nodo* actual = cabeza;
    Nodo* prev = nullptr;
    vistos.insert(cabeza->dato); // Procesar la cabeza primero
    prev = cabeza;
    actual = cabeza->siguiente;
    while (actual != cabeza) {
        if (vistos.count(actual->dato)) {
            Nodo* temp = actual;  // Es duplicado, eliminarlo
            prev->siguiente = actual->siguiente;
            actual = actual->siguiente;
            delete temp;
        } else {
            vistos.insert(actual->dato);
            prev = actual;
            actual = actual->siguiente;
        }
    }
    return cabeza;
}

// ======================= UTILIDAD Y ALGORITMOS =======================

// Imprime la lista circular (con control de vuelta)
void printList(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza;
    std::cout << "Lista circular: ";
    do {
        std::cout << temp->dato << " -> ";
        temp = temp->siguiente;
    } while (temp != cabeza);
    std::cout << "(cabeza: " << cabeza->dato << ")\n";
}
// Imprime con índices
void imprimirConIndices(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza;
    int index = 0;
    std::cout << "Lista con índices:\n";
    do {
        std::cout << "[" << index << "]: " << temp->dato << " -> ";
        temp = temp->siguiente;
        index++;
    } while (temp != cabeza);
    std::cout << "(vuelta completa)\n";
}

int contarNodos(Nodo* cabeza) {
    if (!cabeza) return 0;
    int count = 0;
    Nodo* temp = cabeza;
    do {
        count++;
        temp = temp->siguiente;
    } while (temp != cabeza);
    return count;
}

// Verifica si la lista está bien formada (es circular)
bool esCircularValida(Nodo* cabeza) {
    if (!cabeza) return true; // Lista vacía es válida
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza;
    do {
        lento = lento->siguiente;
        rapido = rapido->siguiente ? rapido->siguiente->siguiente : nullptr;
        if (!rapido) return false; // Se terminó la lista, no es circular       
    } while (lento != rapido && rapido != cabeza);   
    Nodo* temp = cabeza; // Verificar que efectivamente regresa a la cabeza
    do {
        temp = temp->siguiente;
    } while (temp != cabeza && temp != nullptr);
    return temp == cabeza;
}

Nodo* invertirLista(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) return cabeza;
    Nodo* anterior = nullptr;
    Nodo* actual = cabeza;
    Nodo* inicio = cabeza;
    do {
        Nodo* siguiente = actual->siguiente;
        actual->siguiente = anterior;
        anterior = actual;
        actual = siguiente;
    } while (actual != inicio);
    cabeza->siguiente = anterior; // Conectar el último con el primero
    return anterior; // Nueva cabeza
}

Nodo* clonarLista(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* nuevaCabeza = new Nodo(cabeza->dato);
    Nodo* actual = nuevaCabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        actual->siguiente = new Nodo(temp->dato);
        actual = actual->siguiente;
        temp = temp->siguiente;
    }
    actual->siguiente = nuevaCabeza; // Hacer circular
    return nuevaCabeza;
}

Nodo* concatenarListas(Nodo* l1, Nodo* l2) { // no importa si son circulares o no
    if (!l1) return l2;
    if (!l2) return l1;
    Nodo* tail1 = l1; // Encontrar el último nodo de l1
    while (tail1->siguiente != l1) {
        tail1 = tail1->siguiente;
    }
    Nodo* tail2 = l2; // Encontrar el último nodo de l2
    while (tail2->siguiente != l2) {
        tail2 = tail2->siguiente;
    }
    // Conectar las listas
    tail1->siguiente = l2;
    tail2->siguiente = l1;
    return l1;
}

// ======================= ALGORITMOS AVANZADOS =======================

Nodo* rotarDerecha(Nodo* cabeza, int k) { // Rota la lista k posiciones hacia la derecha
    if (!cabeza || k == 0) return cabeza;
    int longitud = contarNodos(cabeza);
    k = k % longitud; // Normalizar k
    if (k == 0) return cabeza;
    Nodo* nuevaCabeza = cabeza;  // Encontrar nueva cabeza (longitud - k posiciones desde la cabeza actual)
    for (int i = 0; i < longitud - k; ++i) {
        nuevaCabeza = nuevaCabeza->siguiente;
    }
    return nuevaCabeza;
}

Nodo* rotarIzquierda(Nodo* cabeza, int k) { // Rota la lista k posiciones hacia la izquierda
    if (!cabeza || k == 0) return cabeza;
    int longitud = contarNodos(cabeza);
    k = k % longitud; // Normalizar k
    if (k == 0) return cabeza;
    Nodo* nuevaCabeza = cabeza; // Encontrar nueva cabeza (k posiciones desde la cabeza actual)
    for (int i = 0; i < k; ++i) {
        nuevaCabeza = nuevaCabeza->siguiente;
    } 
    return nuevaCabeza;
}

std::pair<Nodo*, Nodo*> dividirLista(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) {
        return {cabeza, nullptr};
    }
    // Encontrar el punto medio usando técnica del puntero lento/rápido
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza;
    Nodo* prevLento = nullptr;
    do {
        prevLento = lento;
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
    } while (rapido != cabeza && rapido->siguiente != cabeza);
    Nodo* segundaLista = lento; // Segunda mitad comienza en lento
    prevLento->siguiente = cabeza; // Hacer circular la primera lista
    Nodo* temp = segundaLista; // Encontrar el último nodo de la segunda lista
    while (temp->siguiente != cabeza) {
        temp = temp->siguiente; 
    }
    temp->siguiente = segundaLista; // Hacer circular la segunda lista
    return {cabeza, segundaLista};
}

bool esPalindromo(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) return true;
    std::vector<int> valores; // Convertir a vector para facilitar la comparación
    Nodo* temp = cabeza;
    do {
        valores.push_back(temp->dato);
        temp = temp->siguiente;
    } while (temp != cabeza);
    int n = valores.size();
    for (int i = 0; i < n / 2; ++i) {
        if (valores[i] != valores[n - 1 - i]) { // Comparar simétricamente  
            return false;
        }
    }
    return true;
}

Nodo* nEsimoDesde(Nodo* inicio, int n) { // Encuentra el n-ésimo nodo desde cualquier punto 
    if (!inicio || n <= 0) return nullptr;
    
    Nodo* temp = inicio;
    for (int i = 1; i < n; ++i) {
        temp = temp->siguiente;
    }
    
    return temp;
}

// Solución al problema de Josephus
// ejemplo: si k = 3, elimina cada tercer nodo hasta que queda uno solo
Nodo* josephus(Nodo* cabeza, int k) { // propone que elimina cada k-ésimo nodo hasta que queda uno solo
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    while (actual->siguiente != actual) {
        // Contar k-1 posiciones
        for (int i = 1; i < k; ++i) {
            actual = actual->siguiente;
        }
        // Eliminar el k-ésimo nodo
        Nodo* aEliminar = actual->siguiente;
        actual->siguiente = aEliminar->siguiente;
        delete aEliminar;
        actual = actual->siguiente;
    }
    return actual; // Último sobreviviente
}

bool sonIguales(Nodo* l1, Nodo* l2) {
    if (!l1 && !l2) return true;
    if (!l1 || !l2) return false;
    int len1 = contarNodos(l1);
    int len2 = contarNodos(l2);
    if (len1 != len2) return false;
    // Verificar todas las rotaciones posibles de l1 con l2
    Nodo* temp1 = l1;
    for (int i = 0; i < len1; ++i) {
        Nodo* t1 = temp1;
        Nodo* t2 = l2;
        bool iguales = true;
        for (int j = 0; j < len1; ++j) {
            if (t1->dato != t2->dato) {
                iguales = false;
                break;
            }
            t1 = t1->siguiente;
            t2 = t2->siguiente;
        }
        if (iguales) return true;
        temp1 = temp1->siguiente;
    }
    return false;
}

Nodo* generarListaAleatoria(int tamaño, int min = 1, int max = 100) {
    if (tamaño <= 0) return nullptr;
    Nodo* cabeza = new Nodo(min + rand() % (max - min + 1));
    Nodo* actual = cabeza;   
    for (int i = 1; i < tamaño; ++i) {
        actual->siguiente = new Nodo(min + rand() % (max - min + 1));
        actual = actual->siguiente;
    }   
    actual->siguiente = cabeza; // Hacer circular  
    return cabeza;
}

Nodo* ordenarLista(Nodo* cabeza) { // Ordena la lista circular (usando algoritmo burbuja adaptado)
    if (!cabeza || cabeza->siguiente == cabeza) return cabeza;
    int n = contarNodos(cabeza);
    bool intercambiado; 
    for (int i = 0; i < n - 1; ++i) {
        intercambiado = false;
        Nodo* actual = cabeza;       
        for (int j = 0; j < n - 1 - i; ++j) {
            Nodo* siguiente = actual->siguiente;
            if (actual->dato > siguiente->dato) {
                std::swap(actual->dato, siguiente->dato);
                intercambiado = true;
            }
            actual = actual->siguiente;
        }      
        if (!intercambiado) break;
    }
    return cabeza;
}

Nodo* obtenerMedio(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza;
    Nodo* prev = nullptr;
    
    while (rapido && rapido->siguiente) {
        prev = lento;
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
    }
    
    return prev;
}

bool tieneDuplicados(Nodo* cabeza) {
    if (!cabeza) return false;
    
    std::unordered_set<int> vistos;
    Nodo* temp = cabeza;
    
    do {
        if (vistos.count(temp->dato)) return true;
        vistos.insert(temp->dato);
        temp = temp->siguiente;
    } while (temp != cabeza);
    
    return false;
}

// Rotar hasta que el mínimo esté en la cabeza
Nodo* rotarHastaMinimo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    
    Nodo* minNodo = buscarMinimo(cabeza);
    return minNodo; // En lista circular, cambiar la cabeza es así de simple
}

Nodo* mergeOrdenado(Nodo* l1, Nodo* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->dato <= l2->dato) {
        l1->siguiente = mergeOrdenado(l1->siguiente, l2);
        return l1;
    } else {
        l2->siguiente = mergeOrdenado(l1, l2->siguiente);
        return l2;
    }
}

// ======================= MAIN DE PRUEBA =======================
int main() {
    std::cout << "=== PRUEBAS DE LISTAS CIRCULARES SIMPLES ===\n\n";
    
    Nodo* lista = nullptr;
    
    // 1. INSERCIÓN
    std::cout << "1. PRUEBAS DE INSERCIÓN:\n";
    lista = insertarFinal(lista, 3);
    lista = insertarFinal(lista, 5);
    lista = insertarFinal(lista, 7);
    lista = insertarInicio(lista, 1);
    lista = insertarPosicion(lista, 4, 2);
    printList(lista);
    imprimirConIndices(lista);
    
    // 2. BÚSQUEDAS
    std::cout << "\n2. BÚSQUEDAS:\n";
    std::cout << "Buscar 5: " << (buscar(lista, 5) ? "Encontrado" : "No encontrado") << "\n";
    std::cout << "Posición del 5: " << obtenerPosicion(lista, 5) << "\n";
    
    Nodo* minimo = buscarMinimo(lista);
    Nodo* maximo = buscarMaximo(lista);
    std::cout << "Mínimo: " << (minimo ? minimo->dato : -1) << "\n";
    std::cout << "Máximo: " << (maximo ? maximo->dato : -1) << "\n";
    std::cout << "Número de nodos: " << contarNodos(lista) << "\n";
    
    // 3. VALIDACIÓN
    std::cout << "\n3. VALIDACIÓN:\n";
    std::cout << "¿Es circular válida? " << (esCircularValida(lista) ? "Sí" : "No") << "\n";
    std::cout << "¿Es palíndromo? " << (esPalindromo(lista) ? "Sí" : "No") << "\n";
    
    // 4. MANIPULACIÓN
    std::cout << "\n4. MANIPULACIÓN:\n";
    std::cout << "Original: ";
    printList(lista);
    
    lista = rotarDerecha(lista, 2);
    std::cout << "Rotada 2 a la derecha: ";
    printList(lista);
    
    lista = rotarIzquierda(lista, 1);
    std::cout << "Rotada 1 a la izquierda: ";
    printList(lista);
    
    // 5. ORDENAMIENTO
    std::cout << "\n5. ORDENAMIENTO:\n";
    lista = ordenarLista(lista);
    std::cout << "Lista ordenada: ";
    printList(lista);
    
    // 6. CLONACIÓN
    std::cout << "\n6. CLONACIÓN:\n";
    Nodo* clon = clonarLista(lista);
    std::cout << "Lista original: ";
    printList(lista);
    std::cout << "Lista clonada: ";
    printList(clon);
    
    // 7. DIVISIÓN
    std::cout << "\n7. DIVISIÓN:\n";
    auto [mitad1, mitad2] = dividirLista(clonarLista(lista));
    std::cout << "Primera mitad: ";
    printList(mitad1);
    std::cout << "Segunda mitad: ";
    printList(mitad2);
    
    // 8. JOSEPHUS
    std::cout << "\n8. PROBLEMA DE JOSEPHUS (k=3):\n";
    Nodo* listaJosephus = generarListaAleatoria(7, 1, 7);
    std::cout << "Lista inicial: ";
    printList(listaJosephus);
    
    Nodo* superviviente = josephus(clonarLista(listaJosephus), 3);
    std::cout << "Superviviente: " << (superviviente ? superviviente->dato : -1) << "\n";
    
    // 9. ELIMINACIÓN
    std::cout << "\n9. ELIMINACIÓN:\n";
    lista = eliminarValor(lista, 4);
    std::cout << "Después de eliminar 4: ";
    printList(lista);
    
    lista = eliminarInicio(lista);
    std::cout << "Después de eliminar inicio: ";
    printList(lista);
    
    lista = eliminarFinal(lista);
    std::cout << "Después de eliminar final: ";
    printList(lista);
    
    // 10. LIMPIEZA
    std::cout << "\n10. LIMPIEZA:\n";
    eliminarLista(lista);
    eliminarLista(clon);
    eliminarLista(mitad1);
    eliminarLista(mitad2);
    eliminarLista(listaJosephus);
    
    std::cout << "Memoria liberada exitosamente.\n";
    std::cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS ===\n";
    
    return 0;
}

// Para llamar funciones en main:
// Nodo* cabeza = nullptr;
// cabeza = insertarInicio(cabeza, valor);
// cabeza = insertarFinal(cabeza, valor);
// cabeza = eliminarValor(cabeza, valor);
// etc.