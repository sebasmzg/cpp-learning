// =============================================================================
// ÍNDICE
// =============================================================================
//
// 0. CONCEPTOS FUNDAMENTALES
// 1. ESTRUCTURA BÁSICA Y OPERACIONES FUNDAMENTALES (BST)
//    1.1. Estructura del Nodo (struct Nodo)
//    1.2. Creación de un Nodo (crearNodo)
//    1.3. Inserción en un BST (insertarNodo)
//    1.4. Búsqueda en un BST (buscarNodo)
//    1.5. Eliminación en un BST (eliminar, eliminarNodo, etc.)
//
// 2. MÉTODOS DE CONSTRUCCIÓN DE ÁRBOLES
//    2.1. Crear desde un Array (Nivel por Nivel) (crearDesdeArray)
//    2.2. Crear un BST Balanceado desde un Array Ordenado (crearBSTBalanceado)
//    2.3. Crear un Árbol Binario Completo (crearArbolCompleto)
//
// 3. RECORRIDOS (TRAVERSALS)
//    3.1. Recorridos en Profundidad (DFS - Depth-First Search)
//         3.1.1. Pre-Orden (Raíz, Izquierda, Derecha)
//         3.1.2. In-Orden (Izquierda, Raíz, Derecha)
//         3.1.3. Post-Orden (Izquierda, Derecha, Raíz)
//    3.2. Recorridos en Anchura (BFS - Breadth-First Search)
//         3.2.1. Por Niveles (recorridoPorNiveles)
//         3.2.2. Zigzag (recorridoZigzag)
//    3.3. Recorridos por Vistas
//         3.3.1. Recorrido Vertical (recorridoVertical)
//         3.3.2. Vista desde Arriba (vistaDesdeArriba)
//
// 4. PROPIEDADES Y VALIDACIONES
//    4.1. Calcular Altura (altura)
//    4.2. Contar Nodos (contarNodos)
//    4.3. Validar si es un Árbol Binario de Búsqueda (esValidoBST)
//    4.4. Validar si es un Árbol Balanceado (esBalanceado)
//    4.5. Validar si es un Árbol Completo (esCompleto)
//    4.6. Validar si es un Árbol Simétrico (esSimetrico)
//    4.7. Contar Hojas de un Árbol (contarHojas)
//    4.8. Contar Nodos de un Nivel (contarNodosNivel)
//
// 5. ALGORITMOS CLÁSICOS (ESTILO LEETCODE)
//    5.1. Diámetro de un Árbol Binario (diametro)
//    5.2. Suma Máxima de un Camino (sumMaximaPath)
//    5.3. Ancestro Común más Bajo (ancestroComun)
//    5.4. Encontrar todos los Caminos con una Suma Objetivo (todosLosPathsSuma)
//    5.5. Encontrar el K-ésimo Elemento Menor/Mayor en un BST (kEsimoMenor, kEsimoMayor)
//    5.6. Distancia entre dos Nodos (distanciaEntreNodos)
//
// 6. SERIALIZACIÓN Y DESERIALIZACIÓN
//    6.1. Serializar un Árbol (convertir a string)
//    6.2. Deserializar un Árbol (reconstruir desde string)
//
// 7. ÁRBOLES DE EXPRESIÓN
//    7.1. Crear desde Notación Postfija (crearArbolExpresion)
//    7.2. Validar Árbol de Expresión (esArbolExpresion)
//    7.3. Evaluar Árbol de Expresión (evaluarExpresion)
//
// 8. UTILIDADES
//    8.1. Clonar un Árbol (clonarArbol)
//    8.2. Comparar si dos Árboles son Idénticos (sonIdenticos)
//    8.3. Funciones de Impresión (imprimirArbolVisual, imprimirInfoCompleta)
//    8.4. Eliminar Árbol Completo (eliminarArbolCompleto)
//
// 9. INTERFAZ DE USUARIO Y PRUEBAS
//    9.1. Menú Interactivo (menu)
//    9.2. Función Principal (main)
//
// =============================================================================

#include <iostream>   // Para entrada/salida (cout, cin)
#include <vector>     // Para usar std::vector
#include <queue>      // Para recorridos por niveles (BFS)
#include <stack>      // Para árboles de expresión y recorridos iterativos (no usados aquí, pero útil)
#include <string>     // Para serialización y nombres
#include <sstream>    // Para procesar strings en deserialización
#include <algorithm>  // Para std::max y std::sort
#include <climits>    // Para LONG_MIN, LONG_MAX, INT_MIN
#include <map>        // Para recorridos vertical y vista desde arriba (ordenado por clave)
#include <cmath>      // Para std::abs y std::pow
#include <functional> // Para usar std::function (lambdas como parámetros)

using namespace std;

// =============================================================================
// 0. CONCEPTOS FUNDAMENTALES
// =============================================================================
//
// - Estructura de datos no lineal y dinámica.
// - Nodos: Contienen un dato y punteros a sus hijos (izquierdo y derecho).
// - Raíz: El nodo superior del árbol.
// - Hoja: Un nodo sin hijos.
// - Padre: Nodo que precede a otro en el camino desde la raíz.
// - Altura de un nodo: Longitud del camino más largo desde ese nodo hasta una hoja.
// - Altura de un árbol: Altura de la raíz. Por convención, un árbol vacío tiene altura -1.
// - Profundidad de un nodo: Longitud del camino desde la raíz hasta ese nodo.
// - Árbol Binario de Búsqueda (BST): Para cada nodo, todos los valores en su subárbol
//   izquierdo son menores, y todos los valores en su subárbol derecho son mayores.

// =============================================================================
// 1. ESTRUCTURA BÁSICA Y OPERACIONES FUNDAMENTALES (BST)
// =============================================================================

// 1.1. Estructura del Nodo
struct Nodo {
    int dato;      // Valor almacenado en el nodo.
    Nodo* izq;     // Puntero al hijo izquierdo.
    Nodo* der;     // Puntero al hijo derecho.
    Nodo* padre;   // Puntero al nodo padre (útil para eliminación y algoritmos complejos).

    // Constructor para inicializar un nodo con un valor y opcionalmente su padre.
    Nodo(int valor = 0, Nodo* p = nullptr) : dato(valor), izq(nullptr), der(nullptr), padre(p) {}
};

// Puntero global a la raíz del árbol principal.
Nodo* arbol = nullptr;

// 1.2. Creación de un Nodo
Nodo* crearNodo(int dato, Nodo* padre) {
    // Reserva memoria para un nuevo nodo y lo inicializa con los valores dados.
    return new Nodo(dato, padre);
}

// 1.3. Inserción en un BST (recursiva)
void insertarNodo(Nodo*& arbol, int dato, Nodo* padre) {
    // Caso base: Si el subárbol actual es nulo, hemos encontrado la posición de inserción.
    if (arbol == nullptr) {
        arbol = crearNodo(dato, padre);
    } else {
        // Decidimos si ir por el subárbol izquierdo o derecho basándonos en la propiedad del BST.
        if (dato < arbol->dato) {
            // Si el dato es menor, debe pertenecer al subárbol izquierdo.
            insertarNodo(arbol->izq, dato, arbol);
        } else if (dato > arbol->dato) {
            // Si el dato es mayor, debe pertenecer al subárbol derecho.
            // Se evita la inserción de duplicados.
            insertarNodo(arbol->der, dato, arbol);
        }
    }
}

// 1.4. Búsqueda en un BST (recursiva) asumiendo que es un árbol ordenado
bool buscarNodo(Nodo* arbol, int dato) {
    // Caso base 1: Si el árbol está vacío, el elemento no se encuentra.
    if (arbol == nullptr) return false;
    // Caso base 2: Si el dato del nodo actual es el que buscamos, lo hemos encontrado.
    if (arbol->dato == dato) return true;
    
    // Decisión recursiva: si el dato es menor, buscamos en el subárbol izquierdo, de lo contrario, en el derecho.
    if (dato < arbol->dato) {
        return buscarNodo(arbol->izq, dato);
    } else {
        return buscarNodo(arbol->der, dato);
    }
}

// 1.5. Eliminación en un BST

// Encuentra el nodo con el valor mínimo en un subárbol (el más a la izquierda).
Nodo* minimo(Nodo* arbol){
    if(arbol == nullptr) return nullptr; // Si el subárbol está vacío.
    if(arbol->izq){
        return minimo(arbol->izq); // La propiedad del BST nos dice que el mínimo siempre está a la izquierda.
    }
    return arbol; // Si no hay más nodos a la izquierda, este es el mínimo.
}

// Reemplaza un nodo por otro, actualizando correctamente el puntero del padre.
void reemplazar(Nodo* nodoAReemplazar, Nodo* nuevoNodo){
    if(nodoAReemplazar->padre){
        // El padre del nodo a reemplazar debe ahora apuntar al nuevo nodo.
        if(nodoAReemplazar == nodoAReemplazar->padre->izq){
            nodoAReemplazar->padre->izq = nuevoNodo;
        } else {
            nodoAReemplazar->padre->der = nuevoNodo;
        }
    }
    if(nuevoNodo){
        // El nuevo nodo debe apuntar al padre del nodo que fue reemplazado.
        nuevoNodo->padre = nodoAReemplazar->padre;
    }
}

// Libera la memoria de un nodo.
void destruirNodo(Nodo* nodoEliminar){
    nodoEliminar->izq = nullptr;
    nodoEliminar->der = nullptr;
    delete nodoEliminar;
}

// Lógica principal para eliminar un nodo según sus hijos.
void eliminarNodo(Nodo* nodoEliminar){
    // Caso 1: El nodo tiene dos hijos.
    if(nodoEliminar->izq && nodoEliminar->der){
        // Se busca el sucesor inorden (el nodo más pequeño del subárbol derecho).
        Nodo* menor = minimo(nodoEliminar->der);
        // Se copia el valor del sucesor al nodo que queremos "eliminar".
        nodoEliminar->dato = menor->dato;
        // Ahora el problema se reduce a eliminar el sucesor, que tiene 0 o 1 hijo.
        eliminarNodo(menor);
    }
    // Caso 2: El nodo tiene solo un hijo (izquierdo).
    else if(nodoEliminar->izq){
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    // Caso 3: El nodo tiene solo un hijo (derecho).
    else if(nodoEliminar->der){
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    // Caso 4: El nodo no tiene hijos (es una hoja).
    else {
        reemplazar(nodoEliminar, nullptr);
        destruirNodo(nodoEliminar);
    }
}

// Función de entrada para iniciar la eliminación.
void eliminar(Nodo*& arbol, int dato){
    if(arbol == nullptr) return; // Si el árbol está vacío, no hay nada que eliminar.

    if(dato < arbol->dato){
        eliminar(arbol->izq, dato); // Buscar el nodo en el subárbol izquierdo.
    } else if(dato > arbol->dato) {
        eliminar(arbol->der, dato); // Buscar el nodo en el subárbol derecho.
    } else {
        eliminarNodo(arbol); // Si encontramos el nodo, procedemos a eliminarlo.
    }
}


// =============================================================================
// 2. MÉTODOS DE CONSTRUCCIÓN DE ÁRBOLES
// =============================================================================

void insertarMultiples(Nodo*& raiz, const vector<int>& valores)
{
    for(int valor : valores)
    {
        insertarNodo(raiz, valor, nullptr);
    }
    cout << "Insertados " << valores.size() << " valores." << endl;
}

// 2.1. Crear desde un Array (Nivel por Nivel)
// Construye un árbol binario a partir de un array que representa el recorrido por niveles.
// Usa INT_MIN como marcador para nodos nulos.
Nodo* crearDesdeArray(const vector<int>& valores){
    if(valores.empty() || valores[0] == INT_MIN) return nullptr;

    Nodo* raiz = new Nodo(valores[0]);
    queue<Nodo*> cola; // Se usa una cola para construir el árbol nivel por nivel.
    cola.push(raiz);
    
    for(size_t i = 1; i < valores.size(); i += 2){
        Nodo* actual = cola.front();
        cola.pop();
        
        // Asignar hijo izquierdo si el valor no es el marcador nulo.
        if(i < valores.size() && valores[i] !=  INT_MIN){
            actual->izq = new Nodo(valores[i], actual);
            cola.push(actual->izq);
        }
        // Asignar hijo derecho si el valor no es el marcador nulo.
        if(i + 1 < valores.size() && valores[i + 1] != INT_MIN){
            actual->der = new Nodo(valores[i + 1], actual);
            cola.push(actual->der);
        }
    }
    return raiz;
}

// 2.2. Crear un BST Balanceado desde un Array Ordenado
// Utiliza una estrategia de "divide y vencerás" para construir un BST con altura mínima.
Nodo* crearBSTBalanceado(const vector<int>& arr, int inicio, int fin, Nodo* padre = nullptr){
    if(inicio > fin) return nullptr; // Caso base: no hay elementos en este sub-array.
    
    // El elemento del medio del array se convierte en la raíz del subárbol.
    int medio = inicio + (fin - inicio) / 2;
    Nodo* raiz = new Nodo(arr[medio], padre);
    
    // Recursivamente, la parte izquierda del array forma el subárbol izquierdo.
    raiz->izq = crearBSTBalanceado(arr, inicio, medio - 1, raiz);
    // Y la parte derecha del array forma el subárbol derecho.
    raiz->der = crearBSTBalanceado(arr, medio + 1, fin, raiz);
    
    return raiz;
}

// 2.3. Crear un Árbol Binario Completo
// Un árbol completo es aquel donde todos los niveles, excepto posiblemente el último,
// están completamente llenos, y todos los nodos en el último nivel están lo más a la izquierda posible.
Nodo* crearArbolCompleto(int altura, int valorInicial = 1, Nodo* padre = nullptr){
    if(altura < 0) return nullptr; // La altura no puede ser negativa.
    
    Nodo* raiz = new Nodo(valorInicial, padre);
    if(altura > 0){
        // Recursivamente se crean los subárboles disminuyendo la altura deseada.
        raiz->izq = crearArbolCompleto(altura - 1, valorInicial * 2, raiz);
        raiz->der = crearArbolCompleto(altura - 1, valorInicial * 2 + 1, raiz);
    }
    return raiz;
}


// =============================================================================
// 3. RECORRIDOS (TRAVERSALS)
// =============================================================================
// Los recorridos son algoritmos para visitar todos los nodos de un árbol.
// - DFS (Depth-First Search): Explora tan profundo como sea posible por cada rama antes de retroceder.
//   (PreOrden, InOrden, PostOrden).
// - BFS (Breadth-First Search): Explora todos los nodos de un nivel antes de pasar al siguiente.
//   (Por Niveles).

// 3.1.1. Pre-Orden (Raíz, Izquierda, Derecha)
void preOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    cout << arbol->dato << " - "; // Visita la raíz.
    preOrden(arbol->izq);         // Recorre el subárbol izquierdo.
    preOrden(arbol->der);         // Recorre el subárbol derecho.
}

// 3.1.2. In-Orden (Izquierda, Raíz, Derecha)
// En un BST, este recorrido visita los nodos en orden ascendente.
void inOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    inOrden(arbol->izq);          // Recorre el subárbol izquierdo.
    cout << arbol->dato << " - "; // Visita la raíz.
    inOrden(arbol->der);          // Recorre el subárbol derecho.
}

// 3.1.3. Post-Orden (Izquierda, Derecha, Raíz)
// Útil para eliminar el árbol, ya que se procesa la raíz después de sus hijos.
void postOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    postOrden(arbol->izq);        // Recorre el subárbol izquierdo.
    postOrden(arbol->der);        // Recorre el subárbol derecho.
    cout << arbol->dato << " - "; // Visita la raíz.
}

// 3.2.1. Recorrido Por Niveles (BFS)
void recorridoPorNiveles(Nodo* raiz){
    if(raiz == nullptr) return;
    
    // Se utiliza una cola (FIFO) para procesar los nodos nivel por nivel.
    queue<Nodo*> cola;
    cola.push(raiz);
    
    cout << "Recorrido por niveles: ";
    while(!cola.empty()){
        Nodo* actual = cola.front();
        cola.pop();
        cout << actual->dato << " - ";
        
        // Se añaden los hijos a la cola para ser procesados en el siguiente nivel.
        if(actual->izq) cola.push(actual->izq);
        if(actual->der) cola.push(actual->der);
    }
    cout << endl;
}

// 3.2.2. Recorrido Zigzag
vector<vector<int>> recorridoZigzag(Nodo* raiz) {
    vector<vector<int>> resultado;
    if (raiz == nullptr) return resultado;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    bool izqADer = true; // Flag para alternar la dirección de inserción.
    
    while (!cola.empty()) {
        int tamanoNivel = cola.size();
        vector<int> nivel(tamanoNivel);
        
        for (int i = 0; i < tamanoNivel; i++) {
            Nodo* nodo = cola.front();
            cola.pop();
            
            // La dirección de inserción en el vector `nivel` depende del flag.
            int indice = izqADer ? i : (tamanoNivel - 1 - i);
            nivel[indice] = nodo->dato;
            
            if (nodo->izq) cola.push(nodo->izq);
            if (nodo->der) cola.push(nodo->der);
        }
        
        izqADer = !izqADer; // Invertir la dirección para el siguiente nivel.
        resultado.push_back(nivel);
    }
    return resultado;
}

// 3.3.1. Recorrido Vertical
map<int, vector<pair<int, int>>> recorridoVertical(Nodo* raiz) {
    // Se usa un mapa para agrupar nodos por su columna. La clave es la columna,
    // el valor es un vector de pares (fila, valor del nodo).
    map<int, vector<pair<int, int>>> mapa;
    
    function<void(Nodo*, int, int)> dfs = [&](Nodo* nodo, int fila, int col) {
        if (!nodo) return;
        mapa[col].push_back({fila, nodo->dato});
        dfs(nodo->izq, fila + 1, col - 1);
        dfs(nodo->der, fila + 1, col + 1);
    };
    
    dfs(raiz, 0, 0);
    // Opcional: ordenar nodos dentro de la misma columna por su fila.
    for(auto& par : mapa) {
        sort(par.second.begin(), par.second.end());
    }
    return mapa;
}

// 3.3.2. Vista desde Arriba
vector<int> vistaDesdeArriba(Nodo* raiz) {
    if (!raiz) return {};
    
    // Un mapa almacena el primer nodo que se ve en cada columna.
    map<int, int> mapa; // Clave: columna, Valor: dato del nodo.
    queue<pair<Nodo*, int>> cola; // {Nodo, columna}
    cola.push({raiz, 0});
    
    while (!cola.empty()) {
        auto [nodo, col] = cola.front();
        cola.pop();
        
        // Si la columna no ha sido visitada, este es el primer nodo visible desde arriba.
        if (mapa.find(col) == mapa.end()) {
            mapa[col] = nodo->dato;
        }
        
        if (nodo->izq) cola.push({nodo->izq, col - 1});
        if (nodo->der) cola.push({nodo->der, col + 1});
    }
    
    vector<int> resultado;
    for (auto& [col, val] : mapa) {
        resultado.push_back(val);
    }
    return resultado;
}

// =============================================================================
// 4. PROPIEDADES Y VALIDACIONES
// =============================================================================

// 4.1. Calcular Altura
int altura(Nodo* nodo){
    // Por convención, la altura de un árbol vacío es -1. Esto simplifica los cálculos,
    // ya que la altura de una hoja (1 + max(-1, -1)) será 0.
    if(nodo == nullptr) return -1;
    // La altura de un nodo es 1 (el propio nodo) más la altura del subárbol más alto (izquierdo o derecho).
    return 1 + max(altura(nodo->izq), altura(nodo->der));
}

// 4.2. Contar Nodos
int contarNodos(Nodo* nodo){
    if(nodo == nullptr) return 0; // Un subárbol nulo no tiene nodos.
    // El total de nodos es 1 (el nodo actual) más la suma de nodos de sus subárboles.
    return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
}

// 4.3. Validar si es un Árbol Binario de Búsqueda (LeetCode 98)
bool esValidoBST(Nodo* raiz, long minimo = LONG_MIN, long maximo = LONG_MAX) {
    if (raiz == nullptr) return true; // Un árbol vacío es un BST válido.
    
    // Se utiliza un rango [minimo, maximo] que se va acotando en cada llamada recursiva
    // para asegurar que cada nodo cumpla la propiedad del BST con respecto a *todos*
    // sus ancestros, no solo su padre directo.
    if (raiz->dato <= minimo || raiz->dato >= maximo) return false;
    
    // Para el subárbol izquierdo, el valor máximo permitido es el valor del nodo actual.
    // Para el subárbol derecho, el valor mínimo permitido es el valor del nodo actual.
    return esValidoBST(raiz->izq, minimo, raiz->dato) && 
           esValidoBST(raiz->der, raiz->dato, maximo);
}

// 4.4. Validar si es un Árbol Balanceado (LeetCode 110)
// Un árbol es balanceado si para cada nodo, la diferencia de altura entre sus subárboles
// izquierdo y derecho es como máximo 1.
bool esBalanceado(Nodo* raiz) {
    // Se usa una función auxiliar que devuelve la altura si el subárbol está balanceado,
    // o -1 si no lo está. Esto evita recalcular alturas.
    // std::function permite definir una función lambda auxiliar dentro de esta función.
    function<int(Nodo*)> checkBalance = [&](Nodo* nodo) -> int {
        if (!nodo) return 0; // Un árbol nulo tiene altura 0 y está balanceado.
        
        int izq = checkBalance(nodo->izq);
        if (izq == -1) return -1; // Propagar el desbalance hacia arriba.
        
        int der = checkBalance(nodo->der);
        if (der == -1) return -1; // Propagar el desbalance hacia arriba.
        
        if (abs(izq - der) > 1) return -1; // Si este nodo está desbalanceado.
        
        return max(izq, der) + 1; // Devuelve la altura del nodo si está balanceado.
    };
    
    return checkBalance(raiz) != -1;
}

// 4.5. Validar si es un Árbol Completo
// Un árbol es completo si todos los niveles están llenos excepto posiblemente el último,
// y en el último nivel, los nodos están lo más a la izquierda posible.
bool esCompleto(Nodo* raiz) {
    if (!raiz) return true;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    bool encontradoNull = false; // Flag para detectar el primer nodo nulo encontrado.
    
    while (!cola.empty()) {
        Nodo* nodo = cola.front();
        cola.pop();
        
        if (!nodo) {
            // Si encontramos un nulo, lo marcamos.
            encontradoNull = true;
        } else {
            // Si ya hemos encontrado un nulo y ahora encontramos un nodo válido,
            // el árbol no es completo.
            if (encontradoNull) return false;
            cola.push(nodo->izq);
            cola.push(nodo->der);
        }
    }
    
    return true;
}

// 4.6. Validar si es un Árbol Simétrico (LeetCode 101)
// Un árbol es simétrico si su subárbol izquierdo es una imagen especular de su subárbol derecho.
bool esSimetrico(Nodo* raiz) {
    if (!raiz) return true;
    
    // Función auxiliar que comprueba si dos subárboles son espejos el uno del otro.
    function<bool(Nodo*, Nodo*)> esEspejo = [&](Nodo* izq, Nodo* der) -> bool {
        if (!izq && !der) return true; // Ambos son nulos, son simétricos.
        if (!izq || !der) return false; // Uno es nulo y el otro no, no son simétricos.
        
        // Para ser espejos, sus valores deben ser iguales, y el subárbol izquierdo de uno
        // debe ser espejo del subárbol derecho del otro.
        return (izq->dato == der->dato) && 
               esEspejo(izq->izq, der->der) && 
               esEspejo(izq->der, der->izq);
    };
    
    return esEspejo(raiz->izq, raiz->der);
}

// 4.7. Contar Hojas de un Árbol
int contarHojas(Nodo* raiz) {
    if (!raiz) return 0; // Un árbol nulo no tiene hojas.
    if (!raiz->izq && !raiz->der) return 1; // Un nodo hoja cuenta como 1.
    return contarHojas(raiz->izq) + contarHojas(raiz->der);
}

// 4.8 Contar nodos de un nivel 
int contarNodosNivel(Nodo* raiz, int nivel) {
    if (!raiz) return 0; // Un árbol nulo no tiene nodos.
    if (nivel == 0) return 1; // Si estamos en el nivel 0, contamos este nodo.
    // Contamos los nodos en el nivel deseado en ambos subárboles.
    return contarNodosNivel(raiz->izq, nivel - 1) + contarNodosNivel(raiz->der, nivel - 1);
}


// =============================================================================
// 5. ALGORITMOS CLÁSICOS (ESTILO LEETCODE)
// =============================================================================

// 5.1. Diámetro de un Árbol Binario (LeetCode 543)
// El diámetro es la longitud del camino más largo entre dos nodos cualesquiera en un árbol.
// Este camino puede o no pasar por la raíz.
int diametro(Nodo* raiz) {
    int maxDiametro = 0;
    
    function<int(Nodo*)> profundidad = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        int prof_izq = profundidad(nodo->izq);
        int prof_der = profundidad(nodo->der);
        
        // El diámetro que pasa por el nodo actual es la suma de las profundidades de sus hijos.
        // Se actualiza el máximo global si este diámetro es mayor.
        maxDiametro = max(maxDiametro, prof_izq + prof_der);
        
        // La función devuelve la profundidad del nodo actual para los cálculos de niveles superiores.
        return max(prof_izq, prof_der) + 1;
    };
    
    profundidad(raiz);
    return maxDiametro;
}

// 5.2. Suma Máxima de un Camino (LeetCode 124)
// Encuentra la suma máxima de un camino "de nodo a nodo". El camino puede empezar y terminar
// en cualquier nodo del árbol.
int sumMaximaPath(Nodo* raiz) {
    int maxSuma = INT_MIN;
    
    function<int(Nodo*)> maxPathDown = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        // Calcula la ganancia máxima de los caminos que descienden por la izquierda y la derecha.
        // Si la ganancia es negativa, la consideramos 0 (no tomamos ese camino).
        int ganancia_izq = max(0, maxPathDown(nodo->izq));
        int ganancia_der = max(0, maxPathDown(nodo->der));
        
        // La suma máxima de un camino que "pasa" por el nodo actual es su valor más las ganancias de ambos lados.
        maxSuma = max(maxSuma, nodo->dato + ganancia_izq + ganancia_der);
        
        // Para la recursión, devolvemos la suma máxima de un camino que *termina* en el nodo actual
        // y desciende desde arriba.
        return nodo->dato + max(ganancia_izq, ganancia_der);
    };
    
    maxPathDown(raiz);
    return maxSuma;
}

// 5.3. Ancestro Común más Bajo (LCA) (LeetCode 236)
// Encuentra el nodo más profundo que es ancestro de dos nodos dados, p y q.
Nodo* ancestroComun(Nodo* raiz, Nodo* p, Nodo* q) {
    // Casos base:
    // 1. Si la raíz es nula, no hay ancestro.
    // 2. Si la raíz es uno de los nodos buscados (p o q), entonces la raíz es el LCA.
    if (!raiz || raiz == p || raiz == q) return raiz;
    
    // Busca p y q en los subárboles izquierdo y derecho.
    Nodo* izq = ancestroComun(raiz->izq, p, q);
    Nodo* der = ancestroComun(raiz->der, p, q);
    
    // Si se encontró un nodo en cada subárbol, entonces la raíz actual es el LCA.
    if (izq && der) return raiz;
    
    // Si ambos se encontraron en un solo subárbol, el resultado de ese subárbol es el LCA.
    return izq ? izq : der;
}

// 5.4. Encontrar todos los Caminos con una Suma Objetivo (Path Sum II - LeetCode 113)
vector<vector<int>> todosLosPathsSuma(Nodo* raiz, int sumaObjetivo) {
    vector<vector<int>> resultado;
    vector<int> pathActual;
    
    // Se usa DFS para explorar todos los caminos de la raíz a las hojas.
    function<void(Nodo*, int)> dfs = [&](Nodo* nodo, int sumaRestante) {
        if (!nodo) return;
        
        pathActual.push_back(nodo->dato);
        sumaRestante -= nodo->dato;
        
        // Si es una hoja y la suma es la correcta, hemos encontrado un camino válido.
        if (!nodo->izq && !nodo->der && sumaRestante == 0) {
            resultado.push_back(pathActual);
        } else {
            dfs(nodo->izq, sumaRestante);
            dfs(nodo->der, sumaRestante);
        }
        
        // Backtracking: al volver de la recursión, se elimina el nodo actual del camino
        // para explorar otras ramas.
        pathActual.pop_back();
    };
    
    dfs(raiz, sumaObjetivo);
    return resultado;
}

// 5.5. Encontrar el K-ésimo Elemento Menor/Mayor en un BST (LeetCode 230)
int kEsimoMenor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    
    // Un recorrido In-Orden en un BST visita los nodos en orden ascendente.
    // Simplemente detenemos el recorrido cuando hemos visitado k nodos.
    function<void(Nodo*)> inorder = [&](Nodo* nodo) {
        if (!nodo || contador >= k) return;
        
        inorder(nodo->izq);
        
        contador++;
        if (contador == k) {
            resultado = nodo->dato;
            return;
        }
        
        inorder(nodo->der);
    };
    
    inorder(raiz);
    return resultado;
}

int kEsimoMayor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    
    // Para el k-ésimo mayor, hacemos un recorrido In-Orden inverso (Derecha, Raíz, Izquierda).
    function<void(Nodo*)> inorderInverso = [&](Nodo* nodo) {
        if (!nodo || contador >= k) return;
        
        inorderInverso(nodo->der);
        
        contador++;
        if (contador == k) {
            resultado = nodo->dato;
            return;
        }
        
        inorderInverso(nodo->izq);
    };
    
    inorderInverso(raiz);
    return resultado;
}

// Función auxiliar para buscar un nodo por su valor (necesaria para `distanciaEntreNodos`). 
// sin asumir que está ordenado, funciona para cualquiert tipo de árbol
Nodo* buscarNodoPorValor(Nodo* raiz, int valor) {
    if (!raiz) return nullptr;
    if (raiz->dato == valor) return raiz;
    
    Nodo* izq = buscarNodoPorValor(raiz->izq, valor);
    if (izq) return izq;
    
    return buscarNodoPorValor(raiz->der, valor);
}

// 5.6. Distancia entre dos Nodos
int distanciaEntreNodos(Nodo* raiz, int a, int b) {
    // 1. Encontrar el Ancestro Común más Bajo (LCA).
    Nodo* lca = ancestroComun(raiz, buscarNodoPorValor(raiz, a), buscarNodoPorValor(raiz, b));
    if (!lca) return -1; // Si no hay LCA, los nodos no están en el mismo árbol.
    
    // 2. Calcular la distancia desde el LCA a cada nodo.
    function<int(Nodo*, int)> distanciaDesdeLCA = [&](Nodo* nodo, int valor) -> int {
        if (!nodo) return -1;
        if (nodo->dato == valor) return 0;
        
        int dist_izq = distanciaDesdeLCA(nodo->izq, valor);
        int dist_der = distanciaDesdeLCA(nodo->der, valor);
        
        if (dist_izq == -1 && dist_der == -1) return -1;
        return (dist_izq != -1 ? dist_izq : dist_der) + 1;
    };
    
    int distA = distanciaDesdeLCA(lca, a);
    int distB = distanciaDesdeLCA(lca, b);
    
    // 3. La distancia total es la suma de ambas distancias.
    return distA + distB;
}

// =============================================================================
// 6. SERIALIZACIÓN Y DESERIALIZACIÓN (LeetCode 297)
// =============================================================================
// La serialización convierte una estructura de datos en un formato (como string)
// que puede ser almacenado o transmitido, para luego ser reconstruido (deserializado).

// 6.1. Serializar un Árbol (usando Pre-Orden)
string serializar(Nodo* raiz) {
    if (!raiz) return "null,"; // Representa un nodo nulo.
    
    // Se usa un recorrido Pre-Orden para asegurar una reconstrucción única.
    return to_string(raiz->dato) + "," + 
           serializar(raiz->izq) + 
           serializar(raiz->der);
}

// 6.2. Deserializar un Árbol
// Es importante pasar el string por referencia para que se consuma en cada llamada.
Nodo* deserializar(string& data) {
    if (data.substr(0, 4) == "null") {
        data = data.substr(5); // Consumir "null,"
        return nullptr;
    }
    
    size_t pos = data.find(',');
    int val = stoi(data.substr(0, pos));
    data = data.substr(pos + 1); // Consumir "valor,"
    
    Nodo* nodo = new Nodo(val);
    nodo->izq = deserializar(data); // Reconstruir subárbol izquierdo.
    nodo->der = deserializar(data); // Reconstruir subárbol derecho.
    
    return nodo;
}

// =============================================================================
// 7. ÁRBOLES DE EXPRESIÓN
// =============================================================================
// Un árbol de expresión representa una expresión aritmética. Las hojas son operandos
// (números) y los nodos internos son operadores.

// 7.1. Crear Árbol de Expresión desde Notación Postfija
Nodo* crearArbolExpresion(const string& postfija) {
    if (postfija.empty()) {
        cout << "Error: Expresión vacía" << endl;
        return nullptr;
    }
    
    stack<Nodo*> pila;
    
    for (char c : postfija) {
        if (c == ' ') continue; // Ignorar espacios.
        
        if (isdigit(c)) {
            // Si es un operando, se crea un nodo hoja y se apila.
            pila.push(new Nodo(c));
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // Si es un operador, se desapilan dos operandos.
            if (pila.size() < 2) {
                cout << "Error: Expresión postfija inválida - faltan operandos para '" << c << "'" << endl;
                while (!pila.empty()) { delete pila.top(); pila.pop(); }
                return nullptr;
            }
            
            Nodo* der = pila.top(); pila.pop();
            Nodo* izq = pila.top(); pila.pop();
            
            // Se crea un nodo operador con los operandos como hijos.
            Nodo* operador = new Nodo(c);
            operador->izq = izq;
            operador->der = der;
            izq->padre = operador;
            der->padre = operador;
            
            pila.push(operador);
        } else {
            cout << "Error: Carácter inválido '" << c << "'" << endl;
            while (!pila.empty()) { delete pila.top(); pila.pop(); }
            return nullptr;
        }
    }
    
    if (pila.size() != 1) {
        cout << "Error: Expresión postfija inválida - mal formada." << endl;
        while (!pila.empty()) { delete pila.top(); pila.pop(); }
        return nullptr;
    }
    
    return pila.top();
}


// 7.2. Validar si es un Árbol de Expresión
bool esArbolExpresion(Nodo* raiz) {
    if (!raiz) return false;
    
    // Si es una hoja, debe ser un operando (dígito o letra).
    if (!raiz->izq && !raiz->der) {
        return isdigit(raiz->dato);
    }
    
    // Si es un nodo interno, debe ser un operador y tener dos hijos.
    if (raiz->izq && raiz->der) {
        char op = raiz->dato;
        return (op == '+' || op == '-' || op == '*' || op == '/') &&
               esArbolExpresion(raiz->izq) && esArbolExpresion(raiz->der);
    }
    
    return false; // Caso inválido (nodo con un solo hijo).
}

// 7.3. Evaluar Árbol de Expresión
double evaluarExpresion(Nodo* raiz) {
    if (!esArbolExpresion(raiz)) {
        cout << "Error: El árbol proporcionado no es un árbol de expresión válido." << endl;
        return 0.0;
    }

    // Caso base: si es una hoja (operando), devuelve su valor numérico.
    if (!raiz->izq && !raiz->der) {
        return static_cast<double>(raiz->dato - '0');
    }
    
    // Recursivamente, evalúa los subárboles izquierdo y derecho.
    double val_izq = evaluarExpresion(raiz->izq);
    double val_der = evaluarExpresion(raiz->der);
    
    // Aplica el operador del nodo actual a los resultados de los subárboles.
    switch (raiz->dato) {
        case '+': return val_izq + val_der;
        case '-': return val_izq - val_der;
        case '*': return val_izq * val_der;
        case '/': 
            if (val_der == 0) {
                cout << "Error: División por cero." << endl;
                return 0.0;
            }
            return val_izq / val_der;
    }
    return 0.0; // No debería llegar aquí si el árbol es válido.
}


// =============================================================================
// 8. UTILIDADES
// =============================================================================

// 8.1. Clonar un Árbol
Nodo* clonarArbol(Nodo* original, Nodo* padre = nullptr){
    if(original == nullptr) return nullptr;
    
    Nodo* copia = new Nodo(original->dato, padre);
    copia->izq = clonarArbol(original->izq, copia);
    copia->der = clonarArbol(original->der, copia);
    
    return copia;
}

// 8.2. Comparar si dos Árboles son Idénticos
bool sonIdenticos(Nodo* a, Nodo* b){
    if(a == nullptr && b == nullptr) return true; // Ambos son nulos, son idénticos.
    if(a == nullptr || b == nullptr) return false; // Uno es nulo y el otro no.
    
    // Deben tener el mismo valor y sus subárboles deben ser idénticos.
    return (a->dato == b->dato) && 
           sonIdenticos(a->izq, b->izq) && 
           sonIdenticos(a->der, b->der);
}

// 8.3. Funciones de Impresión
// Versión simple que imprime de forma rotada.
void imprimirArbolSimple(Nodo* arbol, int contador) {
    if (arbol == nullptr) return;
    imprimirArbolSimple(arbol->der, contador + 1);
    for (int i = 0; i < contador; ++i) {
        cout << "   ";
    }
    cout << arbol->dato << endl;
    imprimirArbolSimple(arbol->izq, contador + 1);
}

// Versión mejorada que dibuja líneas para una mejor visualización.
void imprimirArbolVisual(Nodo* raiz, string prefijo = "", bool esIzquierdo = true) {
    if (!raiz) return;

    cout << prefijo;
    cout << (esIzquierdo ? "└──" : "├──" );
    cout << raiz->dato << endl;

    imprimirArbolVisual(raiz->der, prefijo + (esIzquierdo ? "│   " : "    "), false);
    imprimirArbolVisual(raiz->izq, prefijo + (esIzquierdo ? "│   " : "    "), true);
}


void imprimirInfoCompleta(Nodo* raiz) {
    if (!raiz) {
        cout << "Árbol vacío" << endl;
        return;
    }
    
    cout << "\n=== INFORMACIÓN COMPLETA DEL ÁRBOL ===\n";
    cout << "Altura: " << altura(raiz) << endl;
    cout << "Número de nodos: " << contarNodos(raiz) << endl;
    cout << "Número de hojas: " << contarHojas(raiz) << endl;
    cout << "Número de nodos en nivel 2: " << contarNodosNivel(raiz, 2) << endl;
    cout << "Es válido BST: " << (esValidoBST(raiz) ? "Sí" : "No") << endl;
    cout << "Es balanceado: " << (esBalanceado(raiz) ? "Sí" : "No") << endl;
    cout << "Es completo: " << (esCompleto(raiz) ? "Sí" : "No") << endl;
    cout << "Es simétrico: " << (esSimetrico(raiz) ? "Sí" : "No") << endl;
    cout << "Diámetro: " << diametro(raiz) << endl;
    
    cout << "\nVista desde arriba: ";
    vector<int> vista = vistaDesdeArriba(raiz);
    for (int val : vista) cout << val << " ";
    cout << endl;
    
    cout << "\nRecorrido zigzag:" << endl;
    auto zigzag = recorridoZigzag(raiz);
    for (const auto& nivel : zigzag) {
        for (int val : nivel) cout << val << " ";
        cout << endl;
    }
    
    cout << "\nÁrbol visualizado:" << endl;
    imprimirArbolVisual(raiz);
    cout << "=====================================\n" << endl;
}

// 8.4. Eliminar Árbol Completo
// Libera toda la memoria utilizada por el árbol. Usa Post-Orden para la eliminación segura.
void eliminarArbolCompleto(Nodo*& raiz){
    if(raiz == nullptr) return;
    
    eliminarArbolCompleto(raiz->izq);
    eliminarArbolCompleto(raiz->der);
    delete raiz;
    raiz = nullptr; // Importante para evitar punteros colgantes.
}

// =============================================================================
// 9. INTERFAZ DE USUARIO Y PRUEBAS
// =============================================================================

void menu() {
    int dato, opcion;
    do {
        cout << "\t.:MENÚ ÁRBOLES AVANZADO:." << endl;
        cout << "=== OPERACIONES BÁSICAS ===" << endl;
        cout << "0. Insertar nodo individual" << endl;
        cout << "1. Insertar múltiples nodos" << endl;
        cout << "2. Mostrar árbol (simple)" << endl;
        cout << "3. Mostrar árbol (visual)" << endl;
        cout << "4. Existe nodo" << endl;
        cout << "5. Buscar nodo" << endl;
        cout << "6. Distancia entre nodos" << endl;
        cout << "7. Eliminar nodo" << endl;
        cout << "8. Eliminar árbol completo" << endl;

        cout << "\n=== RECORRIDOS ===" << endl;
        cout << "9. PreOrden" << endl;
        cout << "10. InOrden" << endl;
        cout << "11. PostOrden" << endl;
        cout << "12. Por niveles (BFS)" << endl;
        cout << "13. Zigzag" << endl;

        cout << "\n=== CONSTRUCCIÓN RÁPIDA ===" << endl;
        cout << "14. Crear desde array" << endl;
        cout << "15. Crear BST balanceado" << endl;
        cout << "16. Crear árbol completo" << endl;
        cout << "17. Crear árbol de expresión" << endl;
        
        cout << "\n=== ANÁLISIS Y VALIDACIÓN ===" << endl;
        cout << "18. Información completa" << endl;
        cout << "19. Encontrar k-ésimo menor" << endl;
        cout << "20. Buscar paths con suma" << endl;
        
        cout << "\n=== OPERACIONES AVANZADAS ===" << endl;
        cout << "21. Clonar árbol" << endl;
        cout << "22. Comparar con un clon" << endl;
        cout << "23. Serializar/Deserializar" << endl;
        cout << "24. Evaluar expresión (si es un árbol de expresión)" << endl;

        cout << "25. SALIR" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 0: {
                cout << "Ingrese número: "; cin >> dato;
                insertarNodo(arbol, dato, nullptr);
                break;
            }
            case 1: {
                cout << "Ingrese números separados por espacios (0 para terminar): ";
                vector<int> valores; int val;
                while (cin >> val && val != 0) valores.push_back(val);
                insertarMultiples(arbol, valores);
                break;
            }
            case 2: {
                int contador = 0;
                cout << "\nÁrbol completo:\n"; imprimirArbolSimple(arbol, contador); break;
            }
            case 3: {
                cout << "\nÁrbol completo:\n"; imprimirArbolVisual(arbol); break;
            }
            case 4: {
                cout << "Elemento a buscar: "; cin >> dato;
                cout << "Resultado: " << (buscarNodo(arbol, dato) ? "Encontrado" : "No encontrado") << endl;
                break;
            }
            case 5: {
                cout << "Elemento a buscar: "; cin >> dato;
                cout << "Resultado: " << (buscarNodoPorValor(arbol, dato) ? "Encontrado" : "No encontrado") << endl;
                break;
            }
            case 6: {
                cout << "Distancia entre nodos (ingrese dos valores): ";
                int val1, val2;
                cin >> val1 >> val2;
                int distancia = distanciaEntreNodos(arbol, val1, val2);
                cout << "Distancia: " << distancia << endl;
                break;
            }
            case 7: {
                cout << "Elemento a eliminar: "; cin >> dato;
                eliminar(arbol, dato); break;
            }
            case 8: {
                eliminarArbolCompleto(arbol); cout << "Árbol eliminado." << endl; break;
            }
            case 9: {
                cout << "PreOrden: "; preOrden(arbol); cout << endl; break;
            }
            case 10: {
                cout << "InOrden: "; inOrden(arbol); cout << endl; break;
            }
            case 11: {
                cout << "PostOrden: "; postOrden(arbol); cout << endl; break;
            }
            case 12: {
                recorridoPorNiveles(arbol); break;
            }
            case 13: {
                cout << "Recorrido Zigzag:" << endl;
                auto zigzag = recorridoZigzag(arbol);
                for (const auto& nivel : zigzag) {
                    for (int val : nivel) cout << val << " ";
                    cout << endl;
                }
                break;
            }
            case 14: {
                cout << "Ingrese valores (usar " << INT_MIN << " para null, 0 para terminar): ";
                vector<int> valores; int val;
                while (cin >> val && val != 0) valores.push_back(val);
                eliminarArbolCompleto(arbol); arbol = crearDesdeArray(valores);
                cout << "Árbol creado desde array." << endl;
                break;
            }
            case 15: {
                cout << "Ingrese valores ordenados (0 para terminar): ";
                vector<int> valores; int val;
                while (cin >> val && val != 0) valores.push_back(val);
                sort(valores.begin(), valores.end());
                eliminarArbolCompleto(arbol); arbol = crearBSTBalanceado(valores, 0, valores.size() - 1);
                cout << "BST balanceado creado." << endl;
                break;
            }
            case 16: {
                int h; cout << "Ingrese altura: "; cin >> h;
                eliminarArbolCompleto(arbol); arbol = crearArbolCompleto(h);
                cout << "Árbol completo creado." << endl;
                break;
            }
            case 17: {
                string postfija; cout << "Ingrese expresión postfija (sin espacios): "; cin >> postfija;
                eliminarArbolCompleto(arbol);
                arbol = crearArbolExpresion(postfija);
                if (arbol) cout << "Árbol de expresión creado." << endl;
                break;
            }
            case 18: {
                imprimirInfoCompleta(arbol); break;
            }
            case 19: {
                int k; cout << "Ingrese k: "; cin >> k;
                int res = kEsimoMenor(arbol, k);
                cout << "K-ésimo menor: " << (res == -1 ? "No encontrado" : to_string(res)) << endl;
                break;
            }
            case 20: {
                int suma; cout << "Ingrese suma objetivo: "; cin >> suma;
                auto paths = todosLosPathsSuma(arbol, suma);
                cout << "Paths con suma " << suma << ":" << endl;
                for (const auto& path : paths) {
                    for (int val : path) cout << val << " ";
                    cout << endl;
                }
                break;
            }
            case 21: {
                Nodo* clon = clonarArbol(arbol);
                cout << "Árbol clonado. Mostrando clon:" << endl;
                imprimirArbolVisual(clon);
                eliminarArbolCompleto(clon);
                break;
            }
            case 22: {
                Nodo* clon = clonarArbol(arbol);
                cout << "Comparando con clon: " << (sonIdenticos(arbol, clon) ? "Idénticos" : "Diferentes") << endl;
                eliminarArbolCompleto(clon);
                break;
            }
            case 23: {
                string serializado = serializar(arbol);
                cout << "Serializado: " << serializado << endl;
                Nodo* deserializado = deserializar(serializado);
                cout << "Verificación: " << (sonIdenticos(arbol, deserializado) ? "Exitosa" : "Fallida") << endl;
                eliminarArbolCompleto(deserializado);
                break;
            }
            case 24: {
                if (esArbolExpresion(arbol)) {
                    cout << "Resultado de la expresión: " << evaluarExpresion(arbol) << endl;
                } else {
                    cout << "El árbol actual no es un árbol de expresión válido." << endl;
                }
                break;
            }
        }
        
        if (opcion != 25) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        // En Linux/macOS usar "clear", en Windows usar "cls"
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (opcion != 25);

    eliminarArbolCompleto(arbol);
    cout << "Programa terminado. Memoria liberada." << endl;
}

int main(){
    menu();
    return 0;
}