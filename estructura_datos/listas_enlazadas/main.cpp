// Lista simple
struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

// Recorrido unidireccional
// secuencias lineales
// complejidad O(1) para inserción al inicio, O(n) para inserción al final, O(n) para búsqueda

// Lista doble
struct NodoDoble {
    int dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(int valor) : dato(valor) , siguiente(nullptr), anterior(nullptr) {}
};

// Recorrido bidireccional
// Flexibilidad en operaciones
// Útil para navegación en ambas direcciones
// complejidad: O(1) inserción/eliminación con referencia a nodos, O(n) para búsqueda

// Lista circular
struct NodoCircular {
    int dato;
    NodoCircular* siguiente;

    NodoCircular(int valor) : dato(valor), siguiente(nullptr) {}
};
// Recorrido continuo
// Variantes:
    // Circular simple: último nodo apunta al primero
    // circular doble: conexion bidireccional
// Aplicaciones:
    // Sistemas operativos (round-robin) es decir, todos tienen el mismo tiempo de ejecución
    // Juegos de turnos
    // reproducción cíclica de multimedia

