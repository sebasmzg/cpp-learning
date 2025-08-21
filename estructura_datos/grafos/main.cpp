// =============================================================================
// ÍNDICE
// =============================================================================
//
// 0. CONCEPTOS FUNDAMENTALES
//    - ¿Qué es un Grafo?
//    - Tipos de Grafos (Dirigido/No Dirigido, Ponderado/No Ponderado)
//    - Terminología Clave (Vértice, Arista, Grado, Camino, Ciclo)
//
// 1. REPRESENTACIONES DE GRAFOS
//    1.1. Lista de Adyacencia (Implementada)
//    1.2. Matriz de Adyacencia (Conceptual)
//
// 2. ALGORITMOS DE RECORRIDO (TRAVERSALS)
//    2.1. Búsqueda en Anchura (BFS - Breadth-First Search)
//    2.2. Búsqueda en Profundidad (DFS - Depth-First Search)
//         - Versión Recursiva
//         - Versión Iterativa (con Pila)
//
// 3. ALGORITMOS DE CAMINO MÁS CORTO (SHORTEST PATH)
//    3.1. Algoritmo de Dijkstra (Para aristas con pesos no negativos)
//    3.2. BFS para Grafos no Ponderados (Caso especial)
//
// 4. ÁRBOLES DE EXPANSIÓN MÍNIMA (MINIMUM SPANNING TREE - MST)
//    4.1. Algoritmo de Kruskal (Requiere estructura Union-Find)
//    4.2. Algoritmo de Prim (Similar a Dijkstra)
//
// 5. ALGORITMOS PARA GRAFOS DIRIGIDOS
//    5.1. Detección de Ciclos en Grafos Dirigidos
//    5.2. Ordenamiento Topológico (Para Grafos Acíclicos Dirigidos - DAGs)
//
// 6. IMPLEMENTACIÓN DE LA CLASE GRAFO
//    6.1. Estructura de la Clase
//    6.2. Métodos Básicos (addVertex, addEdge)
//    6.3. Implementación de los Algoritmos
//
// 7. ESTRUCTURAS DE DATOS AUXILIARES
//    7.1. Union-Find / Disjoint Set Union (DSU) (Para Kruskal)
//
// 8. APLICACIONES Y PROBLEMAS COMUNES (ESTILO LEETCODE)
//    8.1. Contar Componentes Conexas (DFS/BFS)
//    8.2. "Number of Islands" (DFS/BFS en una matriz)
//    8.3. "Course Schedule" (Ordenamiento Topológico)
//    8.4. "Word Ladder" (BFS para camino más corto)
//
// 9. INTERFAZ DE USUARIO Y PRUEBAS
//    9.1. Menú Interactivo (menu)
//    9.2. Función Principal (main)
//
// =============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>

using namespace std;

// =============================================================================
// 0. CONCEPTOS FUNDAMENTALES
// =============================================================================
//
// - Un grafo es una estructura de datos que consiste en un conjunto de nodos (o vértices) y un conjunto de aristas (o arcos) que conectan pares de nodos.
// G = (V, E)
// Donde V es el conjunto de vértices y E es el conjunto de aristas.
//
// - Tipos de Grafos:
//  - No Dirigido: Las aristas son bidireccionales (una conexión de A a B estambién una conexión de B a A).
//  - Dirigido (Digraph): Las aristas tienen una dirección (una arista de A a B no implica una conexión de B a A).
//  - No ponderado: todas las aristas tienen el mismo "costo" o "distancia" (usualmente 1).
//  - Ponderado: cada arista tiene un peso asociado, que representa un costo, distancia, tiempo, etc.
//
// - Terminología Clave:
//   - Vértice (Vertex/Node): Un punto o nodo en el grafo.
//   - Arista (Edge/Arc): Una conexión entre dos vértices.
//   - Grado (Degree): Número de aristas conectadas a un vértice. En grafos dirigidos, se divide en grado de entrada (indegree) y de salida (outdegree).
//   - Camino (Path): Una secuencia de vértices donde cada vértice adyacente está conectado por una arista.
//   - Ciclo (Cycle): Un camino que empieza y termina en el mismo vértice. Un grafo sin ciclos se llama Acíclico. Un Grafo Dirigido Acíclico es un DAG.

// =============================================================================
// 1. REPRESENTACIONES DE GRAFOS
// =============================================================================
//
// 1.1. Lista de Adyacencia:
//      - Un array o  mapa donde cada índice/clave 'u' corresponde a un vértice, y su valor es una lista de los vértices 'v' a los que 'u' está conectado.
//      - Eficiente en espacio para grafos dispersos (pocas aristas), iterara sobre los vecinos es rápido.
//      - Desventaja: Verificar si existe una arista entre 'u' y 'v' puede tomar tiempo O(grado(u)).
//      - REPRESENTAACIÓN MÁS COMÚN
//
// 1.2. Matriz de Adyacencia:
//      - Una matriz V x V donde 'matriz[i][j] = 1' (o el peso) si hay una arista de 'i' a 'j', y 0 en caso contrario.
//      - Ventaja: verificar la existencia de una arista es O(1).
//      - Desventaja: requiere O(V^2) espacio, ineficiente para grafos dispersos.
// (grafo disperso es un grafo donde el número de aristas es mucho menor que el número máximo posible de aristas)
//      - Iterar sobre los vecinos de un nodo requiere O(V).

// =============================================================================
// 7. ESTRUCTURAS DE DATOS AUXILIARES
// =============================================================================

// 7.1. Union-Find / Disjoint Set Union (DSU)
// Estructura de datos optimizada para determinar si dos elementos pertenecen al mismo conjunto y para unit conjuntos. Escensial para el algoritmo de Kruskal.
class DSU {
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
public:
    // Crea un nuevo conjunto para el elemento 'i'.
    void make_set(int i){
        if(parent.find(i) == parent.end()){
            parent[i] = i; // El elemento es su propio padre inicialmente
            rank[i] = 0; // El rango (altura del árbol) es 0.
        }
    }

    // Encuentra el representante (raíz) del conjunto al que pertenece 'i'.
    // Utiliza compresión de caminos para optimizar futuras búsquedas.
    int find(int i){
        if(parent[i] == i){
            return i; // 'i' es la raíz de su conjunto
        }
        return parent[i] = find(parent[i]); // Compresión de caminos
    }

    // Une los conjuntos que contienen a 'i' y 'j'.
    // Utiliza unión por rango para mantener los árboles planos.
    void unite(int i, int j){
        int root_i = find(i); // Encontrar la raíz del conjunto de 'i'.
        int root_j = find(j); // Encontrar la raíz del conjunto de 'j'.
        if(root_i != root_j){ // Si las raíces son diferentes, unir los conjuntos.
            if(rank[root_i] < rank[root_j]){
                swap(root_i, root_j); // si el rango de 'i' es menor, intercambiar.
            }
            parent[root_j] = root_i; // si 'i' es la nueva raíz, actualizar el padre de 'j'.
            if(rank[root_i] == rank[root_j]){
                rank[root_i]++; // si los rangos son iguales, aumentar el rango de la nueva raíz.
            }
        }
    }
};

// =============================================================================
// 6. IMPLEMENTACIÓN DE LA CLASE GRAFO
// =============================================================================

class Graph {
private:
    // Lista de adyacencia: Mapea un vértice a una lista de sus vecinos.
    // Cada vecino es un par {vértice_destino, peso_arista}
    unordered_map<int, list<pair<int, int>>> adjList;
    bool directed;
public:
    // Constructor
    Graph(bool isDirected = false);

    // 6.2. Añadir un vértice (implícito al añadir arista)
    void addVertex(int u){
        // Si el vértice no existe, se crea una entrada vacía en el mapa.
        if(adjList.find(u) == adjList.end()){
            adjList[u] = {}; // crea {u: []}
        }
    }

    // 6.2. Añadir una arista
    void addEdge(int u, int v, int weight = 1){
        addVertex(u);
        addVertex(v);// Asegurarse de existencia de u y v, si no, los crea
        adjList[u].push_back({v, weight});
        if(!directed){
            adjList[v].push_back({u, weight}); // crea {v: [(u, weight)]}
        }
    }

    void display(){
        cout << "\n--- Lista adyacencia del Grafo ---" << endl;
        for(auto const& [vertex, neighbors] : adjList){
            cout << "Vértice " << vertex << ": -> ";
            for(auto const& neighbor : neighbors){
                cout << "[" << neighbor.first << " (w:)" << neighbor.second << ")] ";
            }
            cout << endl;
        }
        cout << "--------------------------------------\n" << endl;
    };

    // 2.1. Búsqueda en anchura (BFS)
    // Recorre el grafo por niveles. Útil para encontrar el camino más corto en grafos no ponderados.
    // complejidad: O(V + E)
    void bfs(int startVertex){
        if(adjList.find(startVertex) == adjList.end()) return; // Si no existe el vértice de inicio, salir.

        unordered_set<int> visited;
        queue<int> q;

        q.push(startVertex); // agregar vértice de inicio a la cola
        visited.insert(startVertex); // marcar como visitado

        cout << "BFS desde " << startVertex << ": ";
        while(!q.empty()){
            int u = q.front(); // Vértice al frente de la cola
            q.pop(); // Sacar de la cola
            cout << u << " ";

            for(auto const& neighbor : adjList[u]){
                int v = neighbor.first; // Obtener el vértice vecino
                if(visited.find(v) == visited.end()){ // Si no ha sido visitado
                    visited.insert(v); // marcar como visitado
                    q.push(v); // agregar a la cola
                }
            }
        }
        cout << endl;
    }

    // 2.2. Búsqueda en profundidad (DFS) - Versión Recursiva
    // Explora tan profundo como sea posible por cada rama antes de retroceder.
    // Complejidad: O(V + E)
    void dfs_recursive(int startVertex){
        if(adjList.find(startVertex) == adjList.end()) return;
        unordered_set<int> visited;
        cout << "DFS (Recursivo) desde " << startVertex << ": ";
        dfs_helper(startVertex, visited);
        cout << endl;
    }

    // 2.2.1 Búsqueda en profundidad - Sin recursividad (Iterativa con Pila)
    void dfs_iterative(int startVertex){
        if(adjList.find(startVertex) == adjList.end()) return;

        unordered_set<int> visited;
        stack<int> s; // Pila para el DFS iterativo
        s.push(startVertex); // Agregar vértice de inicio a la pila

        cout << "DFS (Iterativo) desde " << startVertex << ": ";
        while(!s.empty()){
            int u = s.top(); // Obtener el vértice al frente de la pila
            s.pop(); // Sacar de la pila

            if(visited.find(u) == visited.end()){ // Si no ha sido visitado
                visited.insert(u); 
                cout << u << " ";

                // Agregar vecinos a la pila
                for(auto const& neighbor : adjList[u]){
                    int v = neighbor.first; // Obtener el vértice vecino
                    if(visited.find(v) == visited.end()){
                        s.push(v); // Agregar vecino a la pila
                    }
                }
            }
        }
        cout << endl;
    }
private:
    // Función auxiliar recursiva para DFS
    /*
    @param u: vértice actual
    @param visited: conjunto de vértices visitados
    */
    void dfs_helper(int u, unordered_set<int>& visited){
        visited.insert(u); // Marcar como visitado
        cout << u << " "; // Imprimir el vértice actual
        for(auto const& neighbor : adjList[u]){
            int v = neighbor.first; // Obtener el vértice vecino
            if(visited.find(v) == visited.end()){ // Si no ha sido visitado
                dfs_helper(v, visited); // Llamada recursiva
            }
        }
    }
public:
    // 3.1. Algortimo de Djikstra
    // Encuentra el camino más corto desde un vértice origen a todos los demás en un grafo poderando pesos NO NEGATIVOS.
    void dijsktra(int startVertex){
        if(adjList.find(startVertex) == adjList.end()) return;

        // Min-priority queue para almacenar {distancia, vértice}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
        unordered_map<int, int> dist; // Mapa para almacenar la distancia mínima a cada vértice

        // Inicializar todas las distancias a infinito.
        for(auto const& [vertex, neighbors] : adjList){
            dist[vertex] = numeric_limits<int>::max(); // Inicializar a infinito
        }

        // Distancia del origen a sí mismo es 0.
        dist[startVertex] = 0;
        pq.push({0, startVertex}); // Agregar el vértice de inicio a la cola de prioridad

        cout << "Distancias más cortas desde " << startVertex << " (Dijkstra):" << endl;
        while(!pq.empty()){
            int u = pq.top().second; // Obtener el vértice con la distancia mínima
            pq.pop();

            // Explorar vecinos
            for(auto const& neighbor : adjList[u]){
                int v = neighbor.first; // Vértice vecino
                int weight = neighbor.second; // Peso de la arista

                // relajación de la arista
                if(dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]){ // si la distancia actual + peso < distancia conocida
                    dist[v] = dist[u] + weight; // Actualizar la distancia
                    pq.push({dist[v], v}); // Agregar el vecino a la cola de prioridad
                }
            }
        }

        for(auto const& [vertex, distance] : dist){
            cout << " Vértice " << vertex << ": " << (distance == numeric_limits<int>::max() ? "Infinito" : to_string(distance)) << endl;
        }

    }

    // 4.1. Algoritmo de Kruskal
    // Encuentra un Árbol de expansión Mínima (MST) para un grafo ponderado y no dirigido.
    // Un MST es un subconjunto de aristas que conecta todos los vértices con el mínimo coste de aristas-
    // Complejidad O(E log E) por el ordenamiento de aristas
    void kruskal_mst(){
        if(directed){
            cout << "Kruskal solo funciona en grafos no dirigidos." << endl;
            return;
        }

        vector<tuple<int, int, int>> edges;
        for(auto const& [u, neighbors] : adjList){
            for(auto const& neighbor : neighbors) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if(u < v){ // evitar aristas duplicadas en la lista
                    edges.emplace_back(weight, u, v);
                }
            }
        }

        
    }
};