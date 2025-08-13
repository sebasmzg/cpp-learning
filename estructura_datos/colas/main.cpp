#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <queue>
#include <algorithm>
#include <chrono>
#include <string>
#include <map>
#include <stack>

using namespace std;

// Estructura FIFO (First In, First Out)
// Operaciones restringidas a dos extremos (frente y final)
// Frente eliminación, final inserción
// Aplicaciones: sistemas de impresión, gestión de tareas, simulaciones sistemas de espera

// ======================= COLA SIMPLE (IMPLEMENTACIÓN CON ARRAY) =======================

class ColaArray {
private:
    int* arr;
    int capacidad;
    int frente;   // Índice del primer elemento
    int final;    // Índice del último elemento
    int tamaño;   // Número de elementos actuales

public:
    ColaArray(int cap) : capacidad(cap), frente(0), final(-1), tamaño(0) {
        arr = new int[capacidad];
    }
    
    ~ColaArray() {
        delete[] arr;
    }
    
    // Insertar elemento al final de la cola
    void enqueue(int valor) {
        if (isFull()) {
            throw "Cola llena";
        }
        final = (final + 1) % capacidad; // Circular para reutilizar espacio
        arr[final] = valor;
        tamaño++;
        cout << "Enqueued: " << valor << endl;
    }
    
    // Remover elemento del frente de la cola
    int dequeue() {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        int valor = arr[frente];
        frente = (frente + 1) % capacidad; // Circular
        tamaño--;
        cout << "Dequeued: " << valor << endl;
        return valor;
    }
    
    // Obtener el elemento del frente sin removerlo
    int front() const {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        return arr[frente];
    }
    
    // Obtener el elemento del final sin removerlo
    int rear() const {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        return arr[final];
    }
    
    bool isEmpty() const { return tamaño == 0; }
    bool isFull() const { return tamaño == capacidad; }
    int size() const { return tamaño; }
    
    // Mostrar contenido de la cola
    void display() const {
        if (isEmpty()) {
            cout << "Cola vacía" << endl;
            return;
        }
        cout << "Cola: ";
        for (int i = 0; i < tamaño; i++) {
            cout << arr[(frente + i) % capacidad] << " ";
        }
        cout << endl;
    }
    
    // Limpiar toda la cola
    void clear() {
        frente = 0;
        final = -1;
        tamaño = 0;
        cout << "Cola limpiada" << endl;
    }
    
    // Buscar elemento en la cola
    bool buscar(int valor) const {
        for (int i = 0; i < tamaño; i++) {
            if (arr[(frente + i) % capacidad] == valor) {
                return true;
            }
        }
        return false;
    }
};

// ======================= COLA SIMPLE (IMPLEMENTACIÓN CON LISTA ENLAZADA) =======================

struct NodoCola {
    int dato;
    NodoCola* siguiente;
    NodoCola(int valor) : dato(valor), siguiente(nullptr) {}
};

class ColaLista {
private:
    NodoCola* frente;
    NodoCola* final;
    int tamaño;

public:
    ColaLista() : frente(nullptr), final(nullptr), tamaño(0) {}
    
    ~ColaLista() {
        clear();
    }
    
    void enqueue(int valor) {
        NodoCola* nuevo = new NodoCola(valor);
        if (isEmpty()) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamaño++;
        cout << "Enqueued: " << valor << endl;
    }
    
    int dequeue() {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        NodoCola* temp = frente;
        int valor = temp->dato;
        frente = frente->siguiente;
        
        if (frente == nullptr) { // Si la cola queda vacía
            final = nullptr;
        }
        
        delete temp;
        tamaño--;
        cout << "Dequeued: " << valor << endl;
        return valor;
    }
    
    int front() const {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        return frente->dato;
    }
    
    int rear() const {
        if (isEmpty()) {
            throw "Cola vacía";
        }
        return final->dato;
    }
    
    bool isEmpty() const { return frente == nullptr; }
    int size() const { return tamaño; }
    
    void display() const {
        if (isEmpty()) {
            cout << "Cola vacía" << endl;
            return;
        }
        cout << "Cola: ";
        NodoCola* temp = frente;
        while (temp) {
            cout << temp->dato << " ";
            temp = temp->siguiente;
        }
        cout << endl;
    }
    
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
        cout << "Cola limpiada" << endl;
    }
    
    bool buscar(int valor) const {
        NodoCola* temp = frente;
        while (temp) {
            if (temp->dato == valor) return true;
            temp = temp->siguiente;
        }
        return false;
    }
};

// ======================= COLA CIRCULAR =======================
// Versión optimizada donde el array se comporta como un anillo

class ColaCircular {
private:
    int* arr;
    int capacidad;
    int frente;
    int final;
    int tamaño;

public:
    ColaCircular(int cap) : capacidad(cap), frente(0), final(0), tamaño(0) {
        arr = new int[capacidad];
    }
    
    ~ColaCircular() {
        delete[] arr;
    }
    
    void enqueue(int valor) {
        if (isFull()) {
            throw "Cola circular llena";
        }
        arr[final] = valor;
        final = (final + 1) % capacidad;
        tamaño++;
    }
    
    int dequeue() {
        if (isEmpty()) {
            throw "Cola circular vacía";
        }
        int valor = arr[frente];
        frente = (frente + 1) % capacidad;
        tamaño--;
        return valor;
    }
    
    int front() const {
        if (isEmpty()) throw "Cola vacía";
        return arr[frente];
    }
    
    bool isEmpty() const { return tamaño == 0; }
    bool isFull() const { return tamaño == capacidad; }
    int size() const { return tamaño; }
    
    void display() const {
        if (isEmpty()) {
            cout << "Cola circular vacía" << endl;
            return;
        }
        cout << "Cola circular: ";
        for (int i = 0; i < tamaño; i++) {
            cout << arr[(frente + i) % capacidad] << " ";
        }
        cout << endl;
    }
    
    // Redimensionar la cola (útil para aplicaciones dinámicas)
    void resize(int nuevaCapacidad) {
        if (nuevaCapacidad < tamaño) {
            throw "Nueva capacidad menor que el tamaño actual";
        }
        
        int* nuevoArr = new int[nuevaCapacidad];
        for (int i = 0; i < tamaño; i++) {
            nuevoArr[i] = arr[(frente + i) % capacidad];
        }
        
        delete[] arr;
        arr = nuevoArr;
        capacidad = nuevaCapacidad;
        frente = 0;
        final = tamaño;
        
        cout << "Cola redimensionada a capacidad: " << nuevaCapacidad << endl;
    }
};

// ======================= COLA DOBLE FIN (DEQUE) =======================
// Permite inserción y eliminación en ambos extremos

class ColaDoble {
private:
    int* arr;
    int capacidad;
    int frente;
    int final;
    int tamaño;

public:
    ColaDoble(int cap) : capacidad(cap), frente(0), final(0), tamaño(0) {
        arr = new int[capacidad];
    }
    
    ~ColaDoble() {
        delete[] arr;
    }
    
    // Insertar al frente
    void enqueueFront(int valor) {
        if (isFull()) {
            throw "Cola doble llena";
        }
        frente = (frente - 1 + capacidad) % capacidad;
        arr[frente] = valor;
        tamaño++;
        cout << "Enqueued front: " << valor << endl;
    }
    
    // Insertar al final (operación normal de cola)
    void enqueueRear(int valor) {
        if (isFull()) {
            throw "Cola doble llena";
        }
        arr[final] = valor;
        final = (final + 1) % capacidad;
        tamaño++;
        cout << "Enqueued rear: " << valor << endl;
    }
    
    // Eliminar del frente (operación normal de cola)
    int dequeueFront() {
        if (isEmpty()) {
            throw "Cola doble vacía";
        }
        int valor = arr[frente];
        frente = (frente + 1) % capacidad;
        tamaño--;
        cout << "Dequeued front: " << valor << endl;
        return valor;
    }
    
    // Eliminar del final
    int dequeueRear() {
        if (isEmpty()) {
            throw "Cola doble vacía";
        }
        final = (final - 1 + capacidad) % capacidad;
        int valor = arr[final];
        tamaño--;
        cout << "Dequeued rear: " << valor << endl;
        return valor;
    }
    
    int front() const {
        if (isEmpty()) throw "Cola vacía";
        return arr[frente];
    }
    
    int rear() const {
        if (isEmpty()) throw "Cola vacía";
        return arr[(final - 1 + capacidad) % capacidad];
    }
    
    bool isEmpty() const { return tamaño == 0; }
    bool isFull() const { return tamaño == capacidad; }
    int size() const { return tamaño; }
    
    void display() const {
        if (isEmpty()) {
            cout << "Cola doble vacía" << endl;
            return;
        }
        cout << "Cola doble: ";
        for (int i = 0; i < tamaño; i++) {
            cout << arr[(frente + i) % capacidad] << " ";
        }
        cout << endl;
    }
};

// ======================= COLAS DE PRIORIDAD =======================

// Estructura para elementos con prioridad
struct ElementoPrioridad {
    int valor;
    int prioridad; // Menor número = mayor prioridad
    
    ElementoPrioridad(int v, int p) : valor(v), prioridad(p) {}
    
    // Operador para ordenamiento (menor prioridad = mayor importancia)
    bool operator>(const ElementoPrioridad& otro) const {
        return prioridad > otro.prioridad;
    }
};

class ColaPrioridad {
private:
    vector<ElementoPrioridad> heap;
    
    void heapifyUp(int indice) {
        while (indice > 0) {
            int padre = (indice - 1) / 2;
            if (heap[indice].prioridad >= heap[padre].prioridad) break;
            swap(heap[indice], heap[padre]);
            indice = padre;
        }
    }
    
    void heapifyDown(int indice) {
        int tamaño = heap.size();
        while (true) {
            int menor = indice;
            int izq = 2 * indice + 1;
            int der = 2 * indice + 2;
            
            if (izq < tamaño && heap[izq].prioridad < heap[menor].prioridad) {
                menor = izq;
            }
            if (der < tamaño && heap[der].prioridad < heap[menor].prioridad) {
                menor = der;
            }
            
            if (menor == indice) break;
            swap(heap[indice], heap[menor]);
            indice = menor;
        }
    }

public:
    void enqueue(int valor, int prioridad) {
        heap.emplace_back(valor, prioridad);
        heapifyUp(heap.size() - 1);
        cout << "Enqueued: " << valor << " (prioridad: " << prioridad << ")" << endl;
    }
    
    int dequeue() {
        if (isEmpty()) {
            throw "Cola de prioridad vacía";
        }
        
        int valor = heap[0].valor;
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        cout << "Dequeued: " << valor << endl;
        return valor;
    }
    
    ElementoPrioridad top() const {
        if (isEmpty()) {
            throw "Cola de prioridad vacía";
        }
        return heap[0];
    }
    
    bool isEmpty() const { return heap.empty(); }
    int size() const { return heap.size(); }
    
    void display() const {
        if (isEmpty()) {
            cout << "Cola de prioridad vacía" << endl;
            return;
        }
        cout << "Cola de prioridad: ";
        for (const auto& elem : heap) {
            cout << elem.valor << "(p:" << elem.prioridad << ") ";
        }
        cout << endl;
    }
};

// ======================= APLICACIONES AVANZADAS =======================

// Simulación de sistema de atención al cliente
class SistemaAtencion {
private:
    ColaLista colaRegular;
    ColaPrioridad colaVIP;
    int tiempoActual;
    
public:
    SistemaAtencion() : tiempoActual(0) {}
    
    void llegarCliente(int id, bool esVIP = false, int prioridad = 5) {
        if (esVIP) {
            colaVIP.enqueue(id, prioridad);
            cout << "Cliente VIP " << id << " llegó (prioridad: " << prioridad << ")" << endl;
        } else {
            colaRegular.enqueue(id);
            cout << "Cliente regular " << id << " llegó" << endl;
        }
    }
    
    void atenderCliente() {
        tiempoActual++;
        
        // Primero atender VIPs si hay
        if (!colaVIP.isEmpty()) {
            int cliente = colaVIP.dequeue();
            cout << "Tiempo " << tiempoActual << ": Atendiendo cliente VIP " << cliente << endl;
        } else if (!colaRegular.isEmpty()) {
            int cliente = colaRegular.dequeue();
            cout << "Tiempo " << tiempoActual << ": Atendiendo cliente regular " << cliente << endl;
        } else {
            cout << "Tiempo " << tiempoActual << ": No hay clientes esperando" << endl;
        }
    }
    
    void mostrarEstado() const {
        cout << "\n=== ESTADO DEL SISTEMA ===\n";
        cout << "Tiempo actual: " << tiempoActual << endl;
        cout << "Clientes VIP esperando: " << colaVIP.size() << endl;
        cout << "Clientes regulares esperando: " << colaRegular.size() << endl;
        colaVIP.display();
        colaRegular.display();
        cout << "==========================\n" << endl;
    }
};

// BFS (Breadth-First Search) usando cola
vector<int> BFS(const vector<vector<int>>& grafo, int inicio) {
    vector<int> resultado;
    vector<bool> visitado(grafo.size(), false);
    queue<int> cola;
    
    cola.push(inicio);
    visitado[inicio] = true;
    
    while (!cola.empty()) {
        int nodo = cola.front();
        cola.pop();
        resultado.push_back(nodo);
        
        // Agregar vecinos no visitados
        for (int vecino : grafo[nodo]) {
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                cola.push(vecino);
            }
        }
    }
    
    return resultado;
}

// Generador de números usando cola circular (Round Robin)
class GeneradorRoundRobin {
private:
    ColaCircular* cola;
    int posicionActual;

public:
    GeneradorRoundRobin(const vector<int>& numeros) {
        cola = new ColaCircular(numeros.size());
        for (int num : numeros) {
            cola->enqueue(num);
        }
        posicionActual = 0;
    }
    
    ~GeneradorRoundRobin() {
        delete cola;
    }
    
    int siguiente() {
        if (cola->isEmpty()) {
            throw "Generador vacío";
        }
        
        int valor = cola->dequeue();
        cola->enqueue(valor); // Volver a agregar al final
        return valor;
    }
    
    vector<int> generar(int cantidad) {
        vector<int> resultado;
        for (int i = 0; i < cantidad; i++) {
            resultado.push_back(siguiente());
        }
        return resultado;
    }
};

// Buffer circular para streaming de datos
class BufferCircular {
private:
    vector<int> buffer;
    int cabeza, cola, tamaño, capacidad;

public:
    BufferCircular(int cap) : capacidad(cap), cabeza(0), cola(0), tamaño(0) {
        buffer.resize(capacidad);
    }
    
    bool escribir(int dato) {
        if (tamaño == capacidad) {
            // Sobrescribir dato más antiguo
            cabeza = (cabeza + 1) % capacidad;
            tamaño--;
        }
        
        buffer[cola] = dato;
        cola = (cola + 1) % capacidad;
        tamaño++;
        return true;
    }
    
    bool leer(int& dato) {
        if (tamaño == 0) return false;
        
        dato = buffer[cabeza];
        cabeza = (cabeza + 1) % capacidad;
        tamaño--;
        return true;
    }
    
    bool estaLleno() const { return tamaño == capacidad; }
    bool estaVacio() const { return tamaño == 0; }
    int getTamaño() const { return tamaño; }
    
    void mostrarBuffer() const {
        cout << "Buffer: ";
        if (tamaño == 0) {
            cout << "vacío" << endl;
            return;
        }
        
        for (int i = 0; i < tamaño; i++) {
            cout << buffer[(cabeza + i) % capacidad] << " ";
        }
        cout << endl;
    }
};

// ======================= HEAP SORT IMPLEMENTACIÓN =======================

class HeapSort {
public:
    static void heapify(vector<int>& arr, int n, int i) {
        int mayor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        
        if (izq < n && arr[izq] > arr[mayor])
            mayor = izq;
        
        if (der < n && arr[der] > arr[mayor])
            mayor = der;
        
        if (mayor != i) {
            swap(arr[i], arr[mayor]);
            heapify(arr, n, mayor);
        }
    }
    
    static void heapSort(vector<int>& arr) {
        int n = arr.size();
        
        // Construir heap máximo
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extraer elementos del heap uno por uno
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
    static void mostrarPasosHeapSort(vector<int> arr) {
        cout << "Array original: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
        
        int n = arr.size();
        
        // Mostrar construcción del heap
        cout << "\nConstruyendo heap máximo:\n";
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
            cout << "Después de heapify en índice " << i << ": ";
            for (int x : arr) cout << x << " ";
            cout << endl;
        }
        
        // Mostrar extracción
        cout << "\nExtrayendo elementos:\n";
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            cout << "Intercambiar " << arr[i] << " y " << arr[0] << ": ";
            for (int j = 0; j < n; j++) {
                if (j <= i) cout << arr[j] << " ";
                else cout << "[" << arr[j] << "] ";
            }
            cout << endl;
            
            heapify(arr, i, 0);
            cout << "Después de heapify: ";
            for (int j = 0; j < n; j++) {
                if (j < i) cout << arr[j] << " ";
                else cout << "[" << arr[j] << "] ";
            }
            cout << endl << endl;
        }
        
        cout << "Array ordenado: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
};

// ======================= FUNCIONES UTILITARIAS =======================

// Invertir cola usando pila auxiliar
template<typename T>
void invertirCola(queue<T>& cola) {
    stack<T> pila;
    
    // Pasar elementos de cola a pila
    while (!cola.empty()) {
        pila.push(cola.front());
        cola.pop();
    }
    
    // Pasar elementos de pila de vuelta a cola
    while (!pila.empty()) {
        cola.push(pila.top());
        pila.pop();
    }
}

// Generar números de K dígitos usando cola
vector<string> generarNumerosKDigitos(int k) {
    vector<string> resultado;
    queue<string> cola;
    
    cola.push("1");
    cola.push("2");
    
    for (int count = 0; count < k; count++) {
        string numero = cola.front();
        cola.pop();
        resultado.push_back(numero);
        
        cola.push(numero + "1");
        cola.push(numero + "2");
    }
    
    return resultado;
}

// Encontrar primer elemento no repetido en stream usando cola
class PrimerNoRepetido {
private:
    queue<char> cola;
    map<char, int> frecuencia;

public:
    void agregar(char c) {
        frecuencia[c]++;
        cola.push(c);
        
        // Remover elementos repetidos del frente
        while (!cola.empty() && frecuencia[cola.front()] > 1) {
            cola.pop();
        }
    }
    
    char getPrimeroNoRepetido() {
        return cola.empty() ? '\0' : cola.front();
    }
};

// ======================= FUNCIÓN MAIN COMPLETA =======================
int main() {
    cout << "=== PRUEBAS COMPLETAS DE COLAS ===\n\n";
    
    try {
        // 1. PRUEBAS DE IMPLEMENTACIONES BÁSICAS
        cout << "1. IMPLEMENTACIONES BÁSICAS:\n";
        cout << "============================\n";
        
        // Cola con Array
        cout << "COLA CON ARRAY:\n";
        ColaArray colaArray(5);
        colaArray.enqueue(10);
        colaArray.enqueue(20);
        colaArray.enqueue(30);
        colaArray.display();
        cout << "Front: " << colaArray.front() << ", Rear: " << colaArray.rear() << endl;
        colaArray.dequeue();
        colaArray.display();
        cout << "Buscar 20: " << (colaArray.buscar(20) ? "Encontrado" : "No encontrado") << endl;
        
        // Cola con Lista Enlazada
        cout << "\nCOLA CON LISTA ENLAZADA:\n";
        ColaLista colaLista;
        colaLista.enqueue(100);
        colaLista.enqueue(200);
        colaLista.enqueue(300);
        colaLista.display();
        cout << "Front: " << colaLista.front() << ", Rear: " << colaLista.rear() << endl;
        colaLista.dequeue();
        colaLista.display();
        
        // 2. COLA CIRCULAR
        cout << "\n\n2. COLA CIRCULAR:\n";
        cout << "==================\n";
        ColaCircular colaCircular(4);
        colaCircular.enqueue(1);
        colaCircular.enqueue(2);
        colaCircular.enqueue(3);
        colaCircular.enqueue(4);
        colaCircular.display();
        
        colaCircular.dequeue();
        colaCircular.dequeue();
        colaCircular.enqueue(5);
        colaCircular.enqueue(6);
        colaCircular.display();
        
        cout << "Redimensionando cola circular...\n";
        colaCircular.resize(6);
        colaCircular.enqueue(7);
        colaCircular.enqueue(8);
        colaCircular.display();
        
        // 3. COLA DOBLE FIN (DEQUE)
        cout << "\n\n3. COLA DOBLE FIN (DEQUE):\n";
        cout << "===========================\n";
        ColaDoble deque(5);
        deque.enqueueRear(10);
        deque.enqueueRear(20);
        deque.enqueueFront(5);
        deque.enqueueFront(1);
        deque.display();
        
        cout << "Front: " << deque.front() << ", Rear: " << deque.rear() << endl;
        deque.dequeueFront();
        deque.dequeueRear();
        deque.display();
        
        // 4. COLA DE PRIORIDAD
        cout << "\n\n4. COLA DE PRIORIDAD:\n";
        cout << "=====================\n";
        ColaPrioridad colaPrioridad;
        colaPrioridad.enqueue(10, 3);
        colaPrioridad.enqueue(20, 1);  // Alta prioridad
        colaPrioridad.enqueue(30, 5);
        colaPrioridad.enqueue(40, 2);
        colaPrioridad.display();
        
        cout << "Desencolando por prioridad:\n";
        while (!colaPrioridad.isEmpty()) {
            colaPrioridad.dequeue();
        }
        
        // 5. SISTEMA DE ATENCIÓN AL CLIENTE
        cout << "\n\n5. SISTEMA DE ATENCIÓN:\n";
        cout << "========================\n";
        SistemaAtencion sistema;
        
        // Simulación de llegada de clientes
        sistema.llegarCliente(101, false);      // Regular
        sistema.llegarCliente(102, true, 1);    // VIP alta prioridad
        sistema.llegarCliente(103, false);      // Regular
        sistema.llegarCliente(104, true, 3);    // VIP baja prioridad
        sistema.llegarCliente(105, true, 2);    // VIP media prioridad
        
        sistema.mostrarEstado();
        
        // Atender clientes
        for (int i = 0; i < 6; i++) {
            sistema.atenderCliente();
        }
        
        sistema.mostrarEstado();
        
        // 6. BFS EN GRAFO
        cout << "\n\n6. BFS EN GRAFO:\n";
        cout << "================\n";
        // Crear grafo de ejemplo: 0-1-2
        //                         |   |
        //                         3-4-5
        vector<vector<int>> grafo = {
            {1, 3},        // 0 conectado con 1, 3
            {0, 2, 4},     // 1 conectado con 0, 2, 4
            {1, 5},        // 2 conectado con 1, 5
            {0, 4},        // 3 conectado con 0, 4
            {1, 3, 5},     // 4 conectado con 1, 3, 5
            {2, 4}         // 5 conectado con 2, 4
        };
        
        cout << "Grafo: 0-1-2\n";
        cout << "       |   |\n";
        cout << "       3-4-5\n";
        
        vector<int> recorridoBFS = BFS(grafo, 0);
        cout << "BFS desde nodo 0: ";
        for (int nodo : recorridoBFS) {
            cout << nodo << " ";
        }
        cout << endl;
        
        // 7. GENERADOR ROUND ROBIN
        cout << "\n\n7. GENERADOR ROUND ROBIN:\n";
        cout << "=========================\n";
        vector<int> numeros = {10, 20, 30, 40};
        GeneradorRoundRobin generador(numeros);
        
        cout << "Números base: ";
        for (int num : numeros) cout << num << " ";
        cout << endl;
        
        cout << "Generando 10 números en round robin: ";
        vector<int> generados = generador.generar(10);
        for (int num : generados) cout << num << " ";
        cout << endl;
        
        // 8. BUFFER CIRCULAR
        cout << "\n\n8. BUFFER CIRCULAR:\n";
        cout << "===================\n";
        BufferCircular buffer(4);
        
        cout << "Escribiendo datos al buffer...\n";
        for (int i = 1; i <= 6; i++) {
            buffer.escribir(i * 10);
            cout << "Escribió " << (i * 10) << " - ";
            buffer.mostrarBuffer();
        }
        
        cout << "\nLeyendo datos del buffer...\n";
        int dato;
        while (buffer.leer(dato)) {
            cout << "Leyó " << dato << " - ";
            buffer.mostrarBuffer();
        }
        
        // 9. HEAP SORT
        cout << "\n\n9. HEAP SORT:\n";
        cout << "=============\n";
        vector<int> arrHeap = {64, 34, 25, 12, 22, 11, 90};
        HeapSort::mostrarPasosHeapSort(arrHeap);
        
        // 10. FUNCIONES UTILITARIAS
        cout << "\n\n10. FUNCIONES UTILITARIAS:\n";
        cout << "==========================\n";
        
        // Invertir cola
        queue<int> colaOriginal;
        colaOriginal.push(1);
        colaOriginal.push(2);
        colaOriginal.push(3);
        colaOriginal.push(4);
        
        cout << "Cola original: ";
        queue<int> temp = colaOriginal;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
        
        invertirCola(colaOriginal);
        cout << "Cola invertida: ";
        while (!colaOriginal.empty()) {
            cout << colaOriginal.front() << " ";
            colaOriginal.pop();
        }
        cout << endl;
        
        // Generar números de K dígitos
        cout << "\nGenerando primeros 8 números binarios:\n";
        vector<string> numerosBinarios = generarNumerosKDigitos(8);
        for (const string& num : numerosBinarios) {
            cout << num << " ";
        }
        cout << endl;
        
        // Primer elemento no repetido
        cout << "\nPrimer elemento no repetido en stream:\n";
        PrimerNoRepetido detector;
        string stream = "abacabad";
        
        for (char c : stream) {
            detector.agregar(c);
            char primero = detector.getPrimeroNoRepetido();
            cout << "Después de '" << c << "': " 
                 << (primero == '\0' ? "ninguno" : string(1, primero)) << endl;
        }
        
        // 11. PRUEBAS DE RENDIMIENTO
        cout << "\n\n11. PRUEBAS DE RENDIMIENTO:\n";
        cout << "============================\n";
        
        const int N = 100000;
        
        auto inicio = chrono::high_resolution_clock::now();
        queue<int> colaSTL;
        for (int i = 0; i < N; i++) {
            colaSTL.push(i);
        }
        for (int i = 0; i < N; i++) {
            colaSTL.pop();
        }
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
        cout << "Operaciones en cola STL con " << N << " elementos: " 
             << duracion.count() << " ms" << endl;
        
        // Comparar con priority_queue
        inicio = chrono::high_resolution_clock::now();
        priority_queue<int> pq;
        for (int i = 0; i < N; i++) {
            pq.push(i);
        }
        for (int i = 0; i < N; i++) {
            pq.pop();
        }
        fin = chrono::high_resolution_clock::now();
        
        duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
        cout << "Operaciones en priority_queue STL con " << N << " elementos: " 
             << duracion.count() << " ms" << endl;
        
        cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE ===\n";
        
    } catch (const char* error) {
        cout << "Error durante las pruebas: " << error << endl;
        return 1;
    } catch (const exception& e) {
        cout << "Excepción capturada: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}