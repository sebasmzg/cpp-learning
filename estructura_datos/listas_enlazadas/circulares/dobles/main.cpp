#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <unordered_map>

using namespace std;

// Lista circular doble: el último nodo apunta al primero Y el primero apunta al último
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(int v) : dato(v), siguiente(nullptr), anterior(nullptr) {}
};
// ======================= INSERCIÓN =======================
Nodo* insertarInicio(Nodo* cabeza, int dato) {
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza) {
        nuevo->siguiente = nuevo; // El único nodo apunta a sí mismo
        nuevo->anterior = nuevo;
        return nuevo;
    }
    Nodo* ultimo = cabeza->anterior; // Encontrar el último nodo
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
    nuevo->anterior = ultimo; // El nuevo nodo apunta al último nodo
    cabeza->anterior = nuevo; // La antigua cabeza apunta al nuevo nodo
    ultimo->siguiente = nuevo; // El último nodo apunta al nuevo nodo
    return nuevo; // Retornar nueva cabeza
}

Nodo* insertarFinal(Nodo* cabeza, int dato) { // mantiene la misma cabeza
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza) {
        nuevo->siguiente = nuevo; // El único nodo apunta a sí mismo
        nuevo->anterior = nuevo;
        return nuevo;
    }
    Nodo* ultimo = cabeza->anterior; // En circular doble, cabeza->anterior es el último
    ultimo->siguiente = nuevo; // El último nodo apunta al nuevo nodo
    nuevo->anterior = ultimo; // El nuevo nodo apunta al último nodo
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la cabeza
    cabeza->anterior = nuevo; // La cabeza apunta al nuevo nodo
    return cabeza; // Mantener la misma cabeza
}

Nodo* insertarPosicion(Nodo* cabeza, int dato, int posicion) {
    if (!cabeza || posicion == 0) {
        return insertarInicio(cabeza, dato);
    }
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
        if (temp == cabeza) break; // Si damos la vuelta completa
    }
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = temp;
    nuevo->anterior = temp->anterior;
    temp->anterior->siguiente = nuevo;
    temp->anterior = nuevo;
    return cabeza;
}

Nodo* insertarOrdenado(Nodo* cabeza, int dato) { // Inserta un nodo en orden ascendente, asumiendo que la lista está ordenada
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza || dato < cabeza->dato) {
        return insertarInicio(cabeza, dato);
    }
    Nodo* temp = cabeza;
    do {
        if (temp->siguiente == cabeza || temp->siguiente->dato > dato) {
            // Insertar después de temp
            nuevo->siguiente = temp->siguiente;
            nuevo->anterior = temp;
            temp->siguiente->anterior = nuevo;
            temp->siguiente = nuevo;
            break;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    return cabeza;
}

void insertarDespuesDe(Nodo* nodo, int dato) {
    if (!nodo) return;
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo->siguiente;
    nuevo->anterior = nodo;
    nodo->siguiente->anterior = nuevo;
    nodo->siguiente = nuevo;
}

void insertarAntesDe(Nodo*& cabeza, Nodo* nodo, int dato) {
    if (!cabeza || !nodo) return;
    
    if (nodo == cabeza) {
        cabeza = insertarInicio(cabeza, dato);
        return;
    }
    
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo;
    nuevo->anterior = nodo->anterior;
    nodo->anterior->siguiente = nuevo;
    nodo->anterior = nuevo;
}

void insertarDespuesDe(Nodo* cabeza, Nodo* nodo, int dato) {
    if(!cabeza || !nodo) return; // Si la lista o el nodo son nulos, no hacer nada
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo->siguiente; // Enlazar el nuevo nodo con el siguiente
    nuevo->anterior = nodo; // Enlazar el nuevo nodo con el nodo actual
    if(nodo->siguiente) {
        nodo->siguiente->anterior = nuevo; // Actualizar el anterior del siguiente nodo
    }
    nodo->siguiente = nuevo; // Enlazar el nodo actual con el nuevo nodo
    nuevo->siguiente->anterior = nuevo;
}

Nodo* insertarEntreNodos(Nodo* cabeza, Nodo* nodoIzquierda, Nodo* nodoDerecha, int dato) {
    if (!cabeza || !nodoIzquierda || !nodoDerecha) return cabeza;
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodoDerecha;
    nuevo->anterior = nodoIzquierda;
    nodoIzquierda->siguiente = nuevo;
    nodoDerecha->anterior = nuevo;
    return cabeza;
}

// ======================= BÚSQUEDA =======================

Nodo* buscar(Nodo* cabeza, int valor) {
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza;
    do {
        if (temp->dato == valor) return temp;
        temp = temp->siguiente;
    } while (temp != cabeza);
    return nullptr;
}

Nodo* buscarDesdeElFinal(Nodo* cabeza, int valor) { 
// Buscar desde el final (ventaja de listas dobles circulares)
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza->anterior; // Empezar desde el último
    do {
        if (temp->dato == valor) return temp;
        temp = temp->anterior;
    } while (temp != cabeza->anterior);
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

int obtenerPosicion(Nodo* cabeza, int valor) {
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

void encontrarOcurrencias(Nodo* cabeza, int valor, std::vector<Nodo*>& resultados) { // Encuentra todas las ocurrencias del valor dado y las almacena en el vector resultados
    if (!cabeza) return;
    Nodo* temp = cabeza;
    do {
        if (temp->dato == valor) {
            resultados.push_back(temp);
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
}

// ======================= ELIMINACIÓN =======================

Nodo* eliminarInicio(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    if (cabeza->siguiente == cabeza) {
        // Solo hay un nodo
        delete cabeza;
        return nullptr;
    }
    Nodo* ultimo = cabeza->anterior;
    Nodo* nuevaCabeza = cabeza->siguiente;
    ultimo->siguiente = nuevaCabeza;
    nuevaCabeza->anterior = ultimo;
    delete cabeza;
    return nuevaCabeza;
}

Nodo* eliminarFinal(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    if (cabeza->siguiente == cabeza) {
        // Solo hay un nodo
        delete cabeza;
        return nullptr;
    }
    Nodo* ultimo = cabeza->anterior;
    Nodo* penultimo = ultimo->anterior;
    penultimo->siguiente = cabeza;
    cabeza->anterior = penultimo;
    delete ultimo;
    return cabeza;
}

Nodo* eliminarValor(Nodo* cabeza, int valor) {
    if (!cabeza) return nullptr;
    
    // Si el valor está en la cabeza
    if (cabeza->dato == valor) {
        return eliminarInicio(cabeza);
    }
    
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        if (temp->dato == valor) {
            temp->anterior->siguiente = temp->siguiente;
            temp->siguiente->anterior = temp->anterior;
            delete temp;
            break;
        }
        temp = temp->siguiente;
    }
    
    return cabeza;
}

Nodo* eliminarTodasOcurrencias(Nodo* cabeza, int valor) { // elimina todas las ocurrencias del valor dado
    if (!cabeza) return nullptr;
    while (cabeza && cabeza->dato == valor) { // Eliminar de la cabeza mientras sea necesario
        cabeza = eliminarInicio(cabeza);
    }
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        Nodo* siguiente = temp->siguiente;
        if (temp->dato == valor) {
            temp->anterior->siguiente = temp->siguiente;
            temp->siguiente->anterior = temp->anterior;
            delete temp;
        }
        temp = siguiente;
    }
    return cabeza;
}

Nodo* eliminarPosicion(Nodo* cabeza, int posicion) {
    if (!cabeza || posicion < 0) return cabeza;
    if (posicion == 0) {
        return eliminarInicio(cabeza);
    }
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion; ++i) {
        temp = temp->siguiente;
        if (temp == cabeza) return cabeza; // Posición fuera de rango
    }
    temp->anterior->siguiente = temp->siguiente;
    temp->siguiente->anterior = temp->anterior;
    delete temp;
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

Nodo* eliminarDuplicados(Nodo* cabeza) { // Elimina duplicados manteniendo primera ocurrencia
    if (!cabeza) return nullptr;
    std::unordered_set<int> vistos;
    Nodo* actual = cabeza;
    vistos.insert(cabeza->dato); // Procesar la cabeza primero
    actual = cabeza->siguiente;
    while (actual != cabeza) {
        if (vistos.count(actual->dato)) {
            // Es duplicado, eliminarlo
            Nodo* temp = actual;
            actual = actual->siguiente;
            
            temp->anterior->siguiente = temp->siguiente;
            temp->siguiente->anterior = temp->anterior;
            delete temp;
        } else {
            vistos.insert(actual->dato);
            actual = actual->siguiente;
        }
    }
    return cabeza;
}

// ======================= UTILIDAD Y ALGORITMOS =======================

void printList(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza;
    std::cout << "Adelante: ";
    do {
        std::cout << temp->dato << " <-> ";
        temp = temp->siguiente;
    } while (temp != cabeza);
    std::cout << "(cabeza: " << cabeza->dato << ")\n";
}

void printListReverse(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza->anterior; // Empezar desde el último
    std::cout << "Atrás: ";
    do {
        std::cout << temp->dato << " <-> ";
        temp = temp->anterior;
    } while (temp != cabeza->anterior);
    std::cout << "(último: " << cabeza->anterior->dato << ")\n";
}
void printListBidirectional(Nodo* cabeza) {
    printList(cabeza);
    printListReverse(cabeza);
    std::cout << std::endl;
}
void imprimirConIndices(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza;
    int index = 0;
    std::cout << "Lista con índices:\n";
    do {
        std::cout << "[" << index << "]: " << temp->dato << " <-> ";
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

bool esCircularDobleValida(Nodo* cabeza) { // Verifica si la lista está bien formada (es circular doble válida)
    if (!cabeza) return true; // Lista vacía es válida
    Nodo* temp = cabeza; // Verificar que todos los enlaces bidireccionales sean correctos
    do { 
        if (temp->siguiente->anterior != temp) {
            std::cout << "Error: Enlace bidireccional roto en nodo " << temp->dato << "\n";
            return false;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    if (cabeza->anterior->siguiente != cabeza) { // Verificar que efectivamente sea circular
        std::cout << "Error: No es circular\n";
        return false;
    }
    std::cout << "Lista circular doble válida\n";
    return true;
}

Nodo* invertirLista(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) return cabeza;
    Nodo* actual = cabeza;
    do {
        std::swap(actual->siguiente, actual->anterior);  // Intercambiar siguiente y anterior
        actual = actual->anterior; // Mover al siguiente (que ahora es anterior)
    } while (actual != cabeza);
    
    return cabeza->siguiente; // Nueva cabeza (la que era anterior a la cabeza original)
}

Nodo* clonarLista(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* nuevaCabeza = new Nodo(cabeza->dato);
    Nodo* actual = nuevaCabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp != cabeza) {
        actual->siguiente = new Nodo(temp->dato);
        actual->siguiente->anterior = actual;
        actual = actual->siguiente;
        temp = temp->siguiente;
    }
    actual->siguiente = nuevaCabeza; // Hacer circular
    nuevaCabeza->anterior = actual;
    return nuevaCabeza;
}

Nodo* concatenarListas(Nodo* l1, Nodo* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    Nodo* tail1 = l1->anterior;
    Nodo* tail2 = l2->anterior; 
    // Conectar las listas
    tail1->siguiente = l2;
    l2->anterior = tail1;
    tail2->siguiente = l1;
    l1->anterior = tail2;
    return l1;
}

// ======================= ALGORITMOS AVANZADOS =======================
Nodo* rotarDerecha(Nodo* cabeza, int k) {
    if (!cabeza || k == 0) return cabeza;
    int longitud = contarNodos(cabeza);
    k = k % longitud; // Normalizar k
    if (k == 0) return cabeza;
    // Encontrar nueva cabeza (longitud - k posiciones desde la cabeza actual)
    Nodo* nuevaCabeza = cabeza;
    for (int i = 0; i < longitud - k; ++i) {
        nuevaCabeza = nuevaCabeza->siguiente;
    }
    return nuevaCabeza;
}

Nodo* rotarIzquierda(Nodo* cabeza, int k) {
    if (!cabeza || k == 0) return cabeza;
    int longitud = contarNodos(cabeza);
    k = k % longitud; // Normalizar k
    if (k == 0) return cabeza;
    // Encontrar nueva cabeza (k posiciones desde la cabeza actual)
    Nodo* nuevaCabeza = cabeza;
    for (int i = 0; i < k; ++i) {
        nuevaCabeza = nuevaCabeza->siguiente;
    }
    return nuevaCabeza;
}

std::pair<Nodo*, Nodo*> dividirLista(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) {
        return {cabeza, nullptr};
    }
    Nodo* lento = cabeza; // Encontrar el punto medio usando técnica del puntero lento/rápido
    Nodo* rapido = cabeza;
    do {
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
    } while (rapido != cabeza && rapido->siguiente != cabeza);
    Nodo* segundaLista = lento;
    Nodo* primeroUltimo = lento->anterior;
    Nodo* segundoUltimo = cabeza->anterior;
    primeroUltimo->siguiente = cabeza; // Dividir las listas
    cabeza->anterior = primeroUltimo;
    segundoUltimo->siguiente = segundaLista;
    segundaLista->anterior = segundoUltimo;
    return {cabeza, segundaLista};
}

bool esPalindromo(Nodo* cabeza) {
    if (!cabeza || cabeza->siguiente == cabeza) return true;
    Nodo* izquierda = cabeza;
    Nodo* derecha = cabeza->anterior;
    int pasos = contarNodos(cabeza) / 2;
    for (int i = 0; i < pasos; ++i) {
        if (izquierda->dato != derecha->dato) {
            return false;
        }
        izquierda = izquierda->siguiente;
        derecha = derecha->anterior;
    }
    return true;
}
// Encuentra el n-ésimo nodo desde cualquier punto
Nodo* nEsimoDesde(Nodo* inicio, int n) {
    if (!inicio || n <= 0) return nullptr;
    Nodo* temp = inicio;
    for (int i = 1; i < n; ++i) {
        temp = temp->siguiente;
    }
    return temp;
}

// Problema de Josephus para lista circular doble
Nodo* josephus(Nodo* cabeza, int k) { // Elimina cada k-ésimo nodo hasta que queda uno solo
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
        aEliminar->siguiente->anterior = actual;
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
        actual->siguiente->anterior = actual;
        actual = actual->siguiente;
    }
    actual->siguiente = cabeza;  // Hacer circular
    cabeza->anterior = actual;
    return cabeza;
}

Nodo* ordenarLista(Nodo* cabeza) {
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

// ======================= ALGORITMOS ESPECÍFICOS PARA RETOS =======================

bool tieneCiclo(Nodo* cabeza) { // ejemplo lista: // 1 <-> 2 <-> 3 <-> 4 (cabeza apunta a 1, último apunta a cabeza)
    // hay un ciclo, el puntero lento y rápido se encontrarán
    if (!cabeza) return false;
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza;
    do {
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
        if (lento == rapido) return true;
    } while (rapido != cabeza && rapido->siguiente != cabeza);
    return true; // En lista circular siempre debería ser true
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

void intercambiarNodos(Nodo*& cabeza, int x, int y) {
    if (x == y) return;
    Nodo* nodoX = buscar(cabeza, x);
    Nodo* nodoY = buscar(cabeza, y);
    if (!nodoX || !nodoY) return;
    std::swap(nodoX->dato, nodoY->dato);
}

// Buscar intersección de dos listas circulares dobles (valores comunes)
std::vector<int> interseccionListas(Nodo* l1, Nodo* l2) {
    std::vector<int> resultado;
    if (!l1 || !l2) return resultado;
    std::unordered_set<int> valores1;
    Nodo* temp = l1;
    do {
        valores1.insert(temp->dato);
        temp = temp->siguiente;
    } while (temp != l1);
    std::unordered_set<int> yaAgregados;
    temp = l2;
    do {
        if (valores1.count(temp->dato) && !yaAgregados.count(temp->dato)) {
            resultado.push_back(temp->dato);
            yaAgregados.insert(temp->dato);
        }
        temp = temp->siguiente;
    } while (temp != l2);
    return resultado;
}

std::vector<int> listaAVector(Nodo* cabeza) { // Convertir lista circular a vector (útil para algoritmos complejos)
    std::vector<int> resultado;
    if (!cabeza) return resultado;
    Nodo* temp = cabeza;
    do {
        resultado.push_back(temp->dato);
        temp = temp->siguiente;
    } while (temp != cabeza);
    return resultado;
}

Nodo* vectorALista(const std::vector<int>& vec) { // Crear lista circular doble desde vector
    if (vec.empty()) return nullptr;
    Nodo* cabeza = new Nodo(vec[0]);
    Nodo* actual = cabeza;
    for (size_t i = 1; i < vec.size(); ++i) {
        actual->siguiente = new Nodo(vec[i]);
        actual->siguiente->anterior = actual;
        actual = actual->siguiente;
    }
    // Hacer circular
    actual->siguiente = cabeza;
    cabeza->anterior = actual;
    return cabeza;
}

// Buscar patrones específicos
Nodo* buscarSecuencia(Nodo* cabeza, const std::vector<int>& secuencia) { // ejemplo: buscar 1, 2, 3 en lista circular
    // lista circular doble: 1 <-> 2 <-> 3 <-> 4 (cabeza apunta a 1, último apunta a cabeza)
    // Retorna el nodo donde comienza la secuencia o nullptr si no se encuentra
    // en este caso la secuencia es 1, 2, 3
    if (!cabeza || secuencia.empty()) return nullptr;
    Nodo* temp = cabeza;
    int n = contarNodos(cabeza);
    for (int i = 0; i < n; ++i) {
        Nodo* inicio = temp;
        Nodo* actual = temp;
        bool encontrado = true;
        for (int val : secuencia) {
            if (actual->dato != val) {
                encontrado = false;
                break;
            }
            actual = actual->siguiente;
        }
        if (encontrado) return inicio;
        temp = temp->siguiente;
    }
    return nullptr;
}

// ======================= MAIN DE PRUEBA =======================
int main() {
    std::cout << "=== PRUEBAS DE LISTAS CIRCULARES DOBLES ===\n\n";  
    Nodo* lista = nullptr;
    // 1. INSERCIÓN
    std::cout << "1. PRUEBAS DE INSERCIÓN:\n";
    lista = insertarFinal(lista, 3);
    lista = insertarFinal(lista, 5);
    lista = insertarFinal(lista, 7);
    lista = insertarInicio(lista, 1);
    lista = insertarPosicion(lista, 4, 2);
    insertarDespuesDe(lista, lista->siguiente, 9); // Insertar después del segundo nodo
    printListBidirectional(lista);
    
    return 0;
}

// Para llamar funciones en main:
// Nodo* cabeza = nullptr;
// cabeza = insertarInicio(cabeza, valor);
// cabeza = insertarFinal(cabeza, valor);
// cabeza = eliminarValor(cabeza, valor);
// etc.