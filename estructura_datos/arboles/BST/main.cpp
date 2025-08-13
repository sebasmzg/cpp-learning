// Estructura de datos no lineales
// dinámicas
// Longitud de camino es el número de nodos - 1
// altura: desde la hoja hacia arriba

// preorden: raiz, izquierdo, derecho
// inorden: izquierdo, raiz, derecho
// postOrden: izquierdo, derecho, raiz

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <map>
#include <unordered_map>
#include <cmath>
#include <functional>

using namespace std;

struct Nodo
{
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(int valor = 0, Nodo* p = nullptr) : dato(valor), izq(nullptr), der(nullptr), padre(p) {}
};

Nodo* arbol = nullptr;

Nodo* crearNodo(int dato, Nodo* padre)
{
    return new Nodo(dato, padre);
}

int altura(Nodo* nodo){ // encontrar altura del árbol
    if(nodo == nullptr) return -1; // altura de un nodo nulo es -1
    return 1 + max(altura(nodo->izq), altura(nodo->der));
}

int contarNodos(Nodo* nodo){
    if(nodo == nullptr) return 0; // si el nodo es nulo, retornar 0
    return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
}

Nodo* maximo(Nodo* arbol){ // encontrar el nodo con valor máximo
    if(arbol == nullptr) return nullptr; // si el arbol está vacío, retornar nullptr
    while(arbol->der != nullptr){
        arbol = arbol->der; // avanzar al nodo derecho hasta llegar al máximo
    }
    return arbol;
}

Nodo* clonarArbol(Nodo* original, Nodo* padre = nullptr){
    if(original == nullptr) return nullptr; // si el árbol original es nulo, retornar nulo
    Nodo* copia = new Nodo(original->dato, padre); // crear un nuevo nodo con el mismo dato
    copia->izq = clonarArbol(original->izq, copia); // clonar subárbol izquierdo
    copia->der = clonarArbol(original->der, copia); // clonar subárbol derecho
    return copia; // retornar la copia del árbol
}

bool sonIdenticos(Nodo* a, Nodo* b){
    if(a == nullptr && b == nullptr) return true; // ambos son nulos
    if(a == nullptr || b == nullptr) return false; // uno es nulo y el otro no
    if(a->dato != b->dato) return false; // los datos son diferentes
    // verificar recursivamente los hijos
    return (a->dato == b->dato) && 
           sonIdenticos(a->izq, b->izq) && 
           sonIdenticos(a->der, b->der); // verificar recursivamente los hijos
}

Nodo* crearDesdeArray(const vector<int>& valores){
    if(valores.empty() || valores[0] == INT_MIN) return nullptr; // si el array está vacío o el primer valor es INT_MIN, retornar nullptr
    Nodo* raiz = new Nodo(valores[0]); // crear la raíz con el primer valor
    queue<Nodo*> cola;
    cola.push(raiz);
    for(size_t i = 1; i < valores.size(); i += 2){
        Nodo* actual = cola.front();
        cola.pop();
        // Hijo izquierdo
        if(i < valores.size() && valores[i] !=  INT_MIN){
            actual->izq = new Nodo(valores[i], actual);
            cola.push(actual->izq);
        }
        // Hijo derecho
        if(i + 1 < valores.size() && valores[i + 1] != INT_MIN){
            actual->der = new Nodo(valores[i + 1], actual);
            cola.push(actual->der);
        }
    }
    return raiz;
}

// un arbol binario balanceado es un arbol en el que la diferencia de altura entre el subarbol izquierdo y el subarbol derecho de cualquier nodo es como maximo 1
Nodo* crearBSTBalanceado(const vector<int>& arr, int inicio, int fin, Nodo* padre = nullptr){
    if(inicio > fin) return nullptr;
    int medio = inicio + (fin - inicio) / 2; // encontrar el punto medio
    Nodo* raiz = new Nodo(arr[medio], padre); // crear el nodo raíz
    raiz->izq = crearBSTBalanceado(arr, inicio, medio - 1, raiz); // crear subárbol izquierdo
    raiz->der = crearBSTBalanceado(arr, medio + 1, fin, raiz); // crear subárbol derecho
    return raiz;
}

Nodo* crearArbolCompleto(int altura, int valorInicial = 1, Nodo* padre = nullptr){
    if(altura < 0) return nullptr; // si la altura es negativa, retornar nullptr
    Nodo* raiz = new Nodo(valorInicial, padre); // crear el nodo raíz
    if(altura > 0){
        raiz->izq = crearArbolCompleto(altura - 1, valorInicial * 2, raiz); // crear subárbol izquierdo
        raiz->der = crearArbolCompleto(altura - 1, valorInicial * 2 + 1, raiz); // crear subárbol derecho
    }
    return raiz;
}

void insertarNodo(Nodo*& arbol, int dato, Nodo* padre)
{
    if (arbol == nullptr) // si el arbol está vacío
    {
        arbol = crearNodo(dato, padre); // crear nodo raiz
    } else
    {  // si tiene un nodo o más
        if (dato < arbol->dato) {
            insertarNodo(arbol->izq, dato, arbol);
        } else if (dato > arbol->dato) { // Evitar duplicados
            insertarNodo(arbol->der, dato, arbol);
        }
    }
}

void insertarMultiples(Nodo*& raiz, const vector<int>& valores)
{
    for(int valor : valores)
    {
        insertarNodo(raiz, valor, nullptr);
    }
    cout << "Insertados " << valores.size() << " valores." << endl;
}

void mostrarArbol(Nodo* arbol, int contador) // contador para separar un no de otro
{
    if (arbol == nullptr) // si está vacío, no hacer nada
    {
        return;
    }
    mostrarArbol(arbol->der, contador+1); // mostrar nodos del lado derecho
    for (int i = 0; i < contador; ++i)
    {
        cout << "   "; // añadir espacios entre nodos
    }
    cout << arbol->dato << endl;
    mostrarArbol(arbol->izq, contador+1); // luego imprimir lado izquierdo
}

bool buscarNodo(Nodo* arbol, int dato)
{
    if (arbol == nullptr) return false; // si está vacío, false
    if (arbol->dato == dato) return true;
    if (dato < arbol->dato) // si es menor
    {
        return buscarNodo(arbol->izq, dato); // buscar izquierda
    } else
    {
        return buscarNodo(arbol->der, dato); // si es mayor, buscar por la derecha
    }
}

// ======================= RECORRIDOS =======================

void preOrden(Nodo* arbol) // recorrido profundidad preorden raiz, izquierda, derecha
{
    if (arbol == nullptr) return;
    cout << arbol->dato << " - "; // raiz
    preOrden(arbol->izq); // izquierdo
    preOrden(arbol->der); // derecho
}

void inOrden(Nodo* arbol) // recorrido inOrden izquierda, raiz, derecha
{
    if (arbol == nullptr) return;
    inOrden(arbol->izq); // izquierda
    cout << arbol->dato << " - "; // raiz
    inOrden(arbol->der); // derecha

}

void postOrden(Nodo* arbol) // recorrido postOrden izquierda, derecha, raiz
{
    if (arbol == nullptr) return;
    postOrden(arbol->izq);
    postOrden(arbol->der);
    cout << arbol->dato << " - ";
}

void recorridoPorNiveles(Nodo* raiz){
    if(raiz == nullptr) return; // si el árbol está vacío, no hacer nada
    queue<Nodo*> cola;
    cola.push(raiz); // Agregar la raíz a la cola
    cout << "Recorrido por niveles: ";
    while(!cola.empty()){ // mientras la cola no esté vacía
        Nodo* actual = cola.front(); // Obtener el nodo actual
        cola.pop(); // Eliminar el nodo de la cola
        cout << actual->dato << " - "; // Mostrar el valor del nodo
        if(actual->izq) cola.push(actual->izq); // Agregar el hijo izquierdo a la cola
        if(actual->der) cola.push(actual->der); // Agregar el hijo derecho a la cola
    }
    cout << endl;
}

vector<vector<int>> recorridoZigzag(Nodo* raiz) { 
    vector<vector<int>> resultado;
    if (raiz == nullptr) return resultado;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    bool izqADer = true;
    
    while (!cola.empty()) {
        int tamaño = cola.size();
        vector<int> nivel(tamaño);
        
        for (int i = 0; i < tamaño; i++) {
            Nodo* nodo = cola.front();
            cola.pop();
            
            int indice = izqADer ? i : (tamaño - 1 - i);
            nivel[indice] = nodo->dato;
            
            if (nodo->izq) cola.push(nodo->izq);
            if (nodo->der) cola.push(nodo->der);
        }
        
        izqADer = !izqADer;
        resultado.push_back(nivel);
    }
    
    return resultado;
}

map<int, vector<pair<int, int>>> recorridoVertical(Nodo* raiz) { 
    map<int, vector<pair<int, int>>> mapa; // columna -> (fila, valor)
    
    function<void(Nodo*, int, int)> dfs = [&](Nodo* nodo, int fila, int col) {
        if (!nodo) return;
        mapa[col].push_back({fila, nodo->dato});
        dfs(nodo->izq, fila + 1, col - 1);
        dfs(nodo->der, fila + 1, col + 1);
    };
    
    dfs(raiz, 0, 0);
    return mapa;
}

vector<int> vistaDesdeArriba(Nodo* raiz) {
    if (!raiz) return {};
    
    map<int, int> mapa; // columna -> valor
    queue<pair<Nodo*, int>> cola;
    cola.push({raiz, 0});
    
    while (!cola.empty()) {
        auto [nodo, col] = cola.front();
        cola.pop();
        
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

// ======================= VALIDACIONES Y PROPIEDADES =======================

// **VALIDAR BST** (LeetCode 98)
bool esValidoBST(Nodo* raiz, long minimo = LONG_MIN, long maximo = LONG_MAX) { // es valido si todos los nodos en el subárbol izquierdo son menores que la raíz y todos los nodos en el subárbol derecho son mayores
    if (raiz == nullptr) return true;
    
    if (raiz->dato <= minimo || raiz->dato >= maximo) return false;
    
    return esValidoBST(raiz->izq, minimo, raiz->dato) && 
           esValidoBST(raiz->der, raiz->dato, maximo);
}

// **VERIFICAR BALANCEADO** (LeetCode 110)
bool esBalanceado(Nodo* raiz) { // balanceado si la diferencia de alturas entre subárboles es como máximo 1
    function<int(Nodo*)> checkBalance = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        int izq = checkBalance(nodo->izq);
        if (izq == -1) return -1;
        
        int der = checkBalance(nodo->der);
        if (der == -1) return -1;
        
        if (abs(izq - der) > 1) return -1;
        
        return max(izq, der) + 1;
    };
    
    return checkBalance(raiz) != -1;
}

// **VERIFICAR ÁRBOL COMPLETO**
bool esCompleto(Nodo* raiz) { // completo si todos los niveles están llenos excepto posiblemente el último
    if (!raiz) return true;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    bool encontradoNull = false;
    
    while (!cola.empty()) {
        Nodo* nodo = cola.front();
        cola.pop();
        
        if (!nodo) {
            encontradoNull = true;
        } else {
            if (encontradoNull) return false;
            cola.push(nodo->izq);
            cola.push(nodo->der);
        }
    }
    
    return true;
}

// **VERIFICAR ÁRBOL SIMÉTRICO** (LeetCode 101)
bool esSimetrico(Nodo* raiz) { // es simétrico cuando el subárbol izquierdo es espejo del subárbol derecho
    if (!raiz) return true;
    
    function<bool(Nodo*, Nodo*)> esEspejo = [&](Nodo* izq, Nodo* der) -> bool {
        if (!izq && !der) return true;
        if (!izq || !der) return false;
        
        return (izq->dato == der->dato) && 
               esEspejo(izq->izq, der->der) && 
               esEspejo(izq->der, der->izq);
    };
    
    return esEspejo(raiz->izq, raiz->der);
}

// ======================= ALGORITMOS AVANZADOS =======================

// **DIÁMETRO DEL ÁRBOL** (LeetCode 543)
int diametro(Nodo* raiz) { // el diametro es la longitud del camino más largo entre dos nodos
    int maxDiametro = 0;
    
    function<int(Nodo*)> profundidad = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        int izq = profundidad(nodo->izq);
        int der = profundidad(nodo->der);
        
        maxDiametro = max(maxDiametro, izq + der);
        
        return max(izq, der) + 1;
    };
    
    profundidad(raiz);
    return maxDiametro;
}

// **SUMA MÁXIMA DE PATH** (LeetCode 124)
int sumMaximaPath(Nodo* raiz) {
    int maxSuma = INT_MIN;
    
    function<int(Nodo*)> maxPathDown = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        int izq = max(0, maxPathDown(nodo->izq));
        int der = max(0, maxPathDown(nodo->der));
        
        maxSuma = max(maxSuma, nodo->dato + izq + der);
        
        return nodo->dato + max(izq, der);
    };
    
    maxPathDown(raiz);
    return maxSuma;
}

// **ANCESTRO COMÚN MÁS BAJO** (LeetCode 236)
Nodo* ancestroComun(Nodo* raiz, Nodo* p, Nodo* q) {
    if (!raiz || raiz == p || raiz == q) return raiz;
    
    Nodo* izq = ancestroComun(raiz->izq, p, q);
    Nodo* der = ancestroComun(raiz->der, p, q);
    
    if (izq && der) return raiz;
    return izq ? izq : der;
}

// **ENCONTRAR TODOS LOS PATHS** (Suma objetivo)
vector<vector<int>> todosLosPathsSuma(Nodo* raiz, int sumaObjetivo) {
    vector<vector<int>> resultado;
    vector<int> pathActual;
    
    function<void(Nodo*, int)> dfs = [&](Nodo* nodo, int suma) {
        if (!nodo) return;
        
        pathActual.push_back(nodo->dato);
        suma -= nodo->dato;
        
        if (!nodo->izq && !nodo->der && suma == 0) {
            resultado.push_back(pathActual);
        } else {
            dfs(nodo->izq, suma);
            dfs(nodo->der, suma);
        }
        
        pathActual.pop_back();
    };
    
    dfs(raiz, sumaObjetivo);
    return resultado;
}

// ======================= SERIALIZACIÓN Y DESERIALIZACIÓN =======================

// **SERIALIZAR ÁRBOL** (LeetCode 297)
string serializar(Nodo* raiz) {
    if (!raiz) return "null,";
    
    return to_string(raiz->dato) + "," + 
           serializar(raiz->izq) + 
           serializar(raiz->der);
}

// **DESERIALIZAR ÁRBOL**
Nodo* deserializar(string& data) {
    if (data.substr(0, 4) == "null") {
        data = data.substr(5);
        return nullptr;
    }
    
    int pos = data.find(',');
    int val = stoi(data.substr(0, pos));
    data = data.substr(pos + 1);
    
    Nodo* nodo = new Nodo(val);
    nodo->izq = deserializar(data);
    nodo->der = deserializar(data);
    
    return nodo;
}

// ======================= ELIMINACION =======================

//funcion para determinar nodo más ixquierdo posible
Nodo* minimo(Nodo* arbol){
    if(arbol == nullptr) return nullptr; // si el arbol está vacío, retornar nullptr
    if(arbol->izq){
        return minimo(arbol->izq); // si tiene hijo izquierdo, buscar ahí
    }
    return arbol; // si no tiene hijo izquierdo, retornar el nodo actual
}

void reemplazar(Nodo* reemplazar, Nodo* nuevoNodo){
    if(reemplazar->padre){ // al padre hay que asignarle el nuevo hijo
        if(reemplazar->dato == reemplazar->padre->izq->dato){
            reemplazar->padre->izq = nuevoNodo; // si es hijo izquierdo, asignar nuevo hijo izquierdo
        } else if(reemplazar->dato == reemplazar->padre->der->dato) {
            reemplazar->padre->der = nuevoNodo; // si es hijo derecho, asignar nuevo hijo derecho
        }
    }
    if(nuevoNodo){ // al hijo, asignarle el nuevo padre
        nuevoNodo->padre = reemplazar->padre; // asignar el padre del nodo a reemplazar
    }
}

void destruirNodo(Nodo* nodoEliminar){
    nodoEliminar->izq = nullptr;
    nodoEliminar->der = nullptr;
    delete nodoEliminar;
}

void eliminarNodo(Nodo* nodoEliminar){
    // verificar si dos tiene hijos
    if(nodoEliminar->izq && nodoEliminar->der){
        Nodo* menor = minimo(nodoEliminar->der);
        nodoEliminar->dato = menor->dato; // reemplazar el valor del nodo a eliminar con el del nodo más pequeño
        eliminarNodo(menor); // eliminar el nodo más pequeño
    }
    // si tiene solo un hijo
    else if(nodoEliminar->izq){ // si tiene hijo izquierdo
        reemplazar(nodoEliminar, nodoEliminar->izq); // reemplazar el nodo a eliminar con su hijo izquierdo
        destruirNodo(nodoEliminar);
    } else if(nodoEliminar->der){ // si tiene hijo derecho
        reemplazar(nodoEliminar, nodoEliminar->der); // reemplazar el nodo a eliminar con su hijo derecho
        destruirNodo(nodoEliminar);
    } else { // si no tiene hijos
        reemplazar(nodoEliminar, nullptr); // reemplazar el nodo a eliminar con nullptr
        destruirNodo(nodoEliminar);
    }
}

void eliminar(Nodo*& arbol, int dato){
    if(arbol == nullptr) return; // si el arbol está vacío, no hacer nada
    if(dato < arbol->dato){
        eliminar(arbol->izq, dato); // si el elemento es menor, buscar por izquierda
    } else if(dato > arbol->dato) {
        eliminar(arbol->der, dato); // si es mayor, buscar por derecha
    } else { // si el elemento es igual al nodo actual
        eliminarNodo(arbol);
    }
}

void eliminarArbolCompleto(Nodo*& raiz){
    if(raiz == nullptr) return; // si el árbol está vacío, no hacer nada
    eliminarArbolCompleto(raiz->izq); // eliminar subárbol izquierdo
    eliminarArbolCompleto(raiz->der); // eliminar subárbol derecho
    delete raiz; // eliminar nodo raíz
    raiz = nullptr; // asignar nullptr a la raíz
    cout << "Árbol eliminado completamente.\n";
}

// ======================= ÁRBOLES DE EXPRESIÓN =======================

// **VERIFICAR SI ES ÁRBOL DE EXPRESIÓN**
bool esArbolExpresion(Nodo* raiz) {
    if (!raiz) return false;
    
    // Si es hoja, debe ser operando
    if (!raiz->izq && !raiz->der) {
        return isdigit(raiz->dato) || (raiz->dato >= 'a' && raiz->dato <= 'z');
    }
    
    // Si no es hoja, debe ser operador y tener exactamente 2 hijos
    if (raiz->izq && raiz->der) {
        char op = raiz->dato;
        return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') &&
               esArbolExpresion(raiz->izq) && esArbolExpresion(raiz->der);
    }
    
    return false; // Un hijo es nulo y el otro no
}

void limpiarNodo(Nodo* nodo) {
    if (!nodo) return;
    delete nodo;
}

// **EVALUAR ÁRBOL DE EXPRESIÓN**
double evaluarExpresion(Nodo* raiz) {
    if (!raiz) {
        cout << "Error: Árbol vacío" << endl;
        return 0;
    }
    
    // Si es hoja (operando)
    if (!raiz->izq && !raiz->der) {
        if (isdigit(raiz->dato)) {
            return static_cast<double>(raiz->dato - '0');
        } else {
            cout << "Error: Operando inválido '" << static_cast<char>(raiz->dato) << "'" << endl;
            return 0;
        }
    }
    
    // Verificar que tenga ambos hijos para operadores
    if (!raiz->izq || !raiz->der) {
        cout << "Error: Operador '" << static_cast<char>(raiz->dato) << "' sin operandos suficientes" << endl;
        return 0;
    }
    
    // Evaluar subárboles
    double izq = evaluarExpresion(raiz->izq);
    double der = evaluarExpresion(raiz->der);
    
    // Aplicar operador
    switch (raiz->dato) {
        case '+': return izq + der;
        case '-': return izq - der;
        case '*': return izq * der;
        case '/': 
            if (der == 0) {
                cout << "Error: División por cero" << endl;
                return 0;
            }
            return izq / der;
        case '^': return pow(izq, der);
        default: 
            cout << "Error: Operador desconocido '" << static_cast<char>(raiz->dato) << "'" << endl;
            return 0;
    }
}

// **CREAR ÁRBOL DE EXPRESIÓN DESDE POSTFIJA**
Nodo* crearArbolExpresion(const string& postfija) {
    if (postfija.empty()) {
        cout << "Error: Expresión vacía" << endl;
        return nullptr;
    }
    
    stack<Nodo*> pila;
    
    for (char c : postfija) {
        // Ignorar espacios
        if (c == ' ') continue;
        
        if (isdigit(c)) {
            pila.push(new Nodo(c));
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (pila.size() < 2) {
                cout << "Error: Expresión postfija inválida - faltan operandos para '" << c << "'" << endl;
                // Limpiar pila antes de retornar
                while (!pila.empty()) {
                    delete pila.top();
                    pila.pop();
                }
                return nullptr;
            }
            
            Nodo* der = pila.top(); pila.pop();
            Nodo* izq = pila.top(); pila.pop();
            
            Nodo* operador = new Nodo(c);
            operador->izq = izq;
            operador->der = der;
            izq->padre = operador;
            der->padre = operador;
            
            pila.push(operador);
        } else {
            cout << "Error: Carácter inválido '" << c << "' en la expresión" << endl;
            // Limpiar pila antes de retornar
            while (!pila.empty()) {
                eliminarArbolCompleto(pila.top());
                pila.pop();
            }
            return nullptr;
        }
    }
    
    if (pila.size() != 1) {
        cout << "Error: Expresión postfija inválida - debe quedar exactamente un elemento" << endl;
        // Limpiar todos los árboles en la pila
        while (!pila.empty()) {
            eliminarArbolCompleto(pila.top());
            pila.pop();
        }
        return nullptr;
    }
    
    return pila.top();
}

bool validarExpresionPostfija(const string& postfija) {
    int operandos = 0;
    int operadores = 0;
    
    for (char c : postfija) {
        if (c == ' ') continue;
        
        if (isdigit(c)) {
            operandos++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            operadores++;
            // En cualquier punto, debe haber al menos tantos operandos como operadores + 1
            if (operandos < operadores + 1) {
                return false;
            }
        } else {
            return false; // Carácter inválido
        }
    }
    
    // Al final debe haber exactamente un operando más que operadores
    return operandos == operadores + 1;
}

Nodo* crearArbolExpresionSeguro(const string& postfija) {
    cout << "Validando expresión postfija: '" << postfija << "'" << endl;
    
    if (!validarExpresionPostfija(postfija)) {
        cout << "Error: Expresión postfija inválida" << endl;
        cout << "Formato correcto: operandos seguidos de operadores (ej: '23+' para 2+3)" << endl;
        return nullptr;
    }
    
    cout << "Expresión válida, creando árbol..." << endl;
    return crearArbolExpresion(postfija);
}

// ======================= BÚSQUEDAS AVANZADAS =======================

// **BUSCAR POR NIVEL**
vector<Nodo*> buscarEnNivel(Nodo* raiz, int nivel) {
    vector<Nodo*> resultado;
    
    function<void(Nodo*, int)> buscar = [&](Nodo* nodo, int nivelActual) {
        if (!nodo) return;
        
        if (nivelActual == nivel) {
            resultado.push_back(nodo);
        } else if (nivelActual < nivel) {
            buscar(nodo->izq, nivelActual + 1);
            buscar(nodo->der, nivelActual + 1);
        }
    };
    
    buscar(raiz, 0);
    return resultado;
}

// **ENCONTRAR K-ÉSIMO MENOR ELEMENTO** (BST)
int kEsimoMenor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    
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
    
    function<void(Nodo*)> inorder = [&](Nodo* nodo) {
        if (!nodo || contador >= k) return;
        
        inorder(nodo->der); // Invertir el orden para mayor
        
        contador++;
        if (contador == k) {
            resultado = nodo->dato;
            return;
        }
        
        inorder(nodo->izq);
    };
    
    inorder(raiz);
    return resultado;
}

// Función auxiliar para buscar nodo por valor
Nodo* buscarNodoPorValor(Nodo* raiz, int valor) {
    if (!raiz) return nullptr;
    if (raiz->dato == valor) return raiz;
    
    Nodo* izq = buscarNodoPorValor(raiz->izq, valor);
    if (izq) return izq;
    
    return buscarNodoPorValor(raiz->der, valor);
}

// **DISTANCIA ENTRE DOS NODOS**
int distanciaEntreNodos(Nodo* raiz, int a, int b) {
    Nodo* lca = ancestroComun(raiz, buscarNodoPorValor(raiz, a), buscarNodoPorValor(raiz, b));
    if (!lca) return -1;
    
    function<int(Nodo*, int)> distanciaALCA = [&](Nodo* nodo, int valor) -> int {
        if (!nodo) return -1;
        if (nodo->dato == valor) return 0;
        
        int izq = distanciaALCA(nodo->izq, valor);
        int der = distanciaALCA(nodo->der, valor);
        
        if (izq == -1 && der == -1) return -1;
        return (izq == -1 ? der : izq) + 1;
    };
    
    int distA = distanciaALCA(lca, a);
    int distB = distanciaALCA(lca, b);
    
    return distA + distB;
}

// ======================= UTILIDADES DE IMPRESIÓN =======================

// **IMPRIMIR ÁRBOL BONITO** (Versión mejorada)
void imprimirArbolBonito(Nodo* raiz, string prefijo = "", bool esUltimo = true) {
    if (!raiz) return;
    
    cout << prefijo;
    cout << (esUltimo ? "└── " : "├── ");
    cout << raiz->dato << endl;
    
    if (raiz->izq || raiz->der) {
        if (raiz->der) {
            imprimirArbolBonito(raiz->der, prefijo + (esUltimo ? "    " : "│   "), !raiz->izq);
        }
        if (raiz->izq) {
            imprimirArbolBonito(raiz->izq, prefijo + (esUltimo ? "    " : "│   "), true);
        }
    }
}

// **IMPRIMIR INFORMACIÓN COMPLETA DEL ÁRBOL**
void imprimirInfoCompleta(Nodo* raiz) {
    if (!raiz) {
        cout << "Árbol vacío" << endl;
        return;
    }
    
    cout << "\n=== INFORMACIÓN COMPLETA DEL ÁRBOL ===\n";
    cout << "Altura: " << altura(raiz) << endl;
    cout << "Número de nodos: " << contarNodos(raiz) << endl;
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
    imprimirArbolBonito(raiz);
    cout << "=====================================\n" << endl;
}


// ======================= MENÚ EXTENDIDO =======================

void menu() {
    int dato, opcion;
    do {
        cout << "\t.:MENÚ ÁRBOLES AVANZADO:." << endl;
        cout << "=== OPERACIONES BÁSICAS ===" << endl;
        cout << "1. Insertar nodo individual" << endl;
        cout << "2. Insertar múltiples nodos" << endl;
        cout << "3. Mostrar árbol completo" << endl;
        cout << "4. Buscar nodo" << endl;
        cout << "5. Eliminar nodo" << endl;
        cout << "6. Eliminar árbol completo" << endl;
        
        cout << "\n=== RECORRIDOS ===" << endl;
        cout << "7. PreOrden" << endl;
        cout << "8. InOrden" << endl;
        cout << "9. PostOrden" << endl;
        cout << "10. Por niveles (BFS)" << endl;
        cout << "11. Zigzag" << endl;
        
        cout << "\n=== CONSTRUCCIÓN RÁPIDA ===" << endl;
        cout << "12. Crear desde array" << endl;
        cout << "13. Crear BST balanceado" << endl;
        cout << "14. Crear árbol completo" << endl;
        cout << "15. Crear árbol de expresión" << endl;
        
        cout << "\n=== ANÁLISIS Y VALIDACIÓN ===" << endl;
        cout << "16. Información completa" << endl;
        cout << "17. Verificar propiedades" << endl;
        cout << "18. Encontrar k-ésimo menor" << endl;
        cout << "19. Buscar paths con suma" << endl;
        
        cout << "\n=== OPERACIONES AVANZADAS ===" << endl;
        cout << "20. Clonar árbol" << endl;
        cout << "21. Comparar árboles" << endl;
        cout << "22. Serializar/Deserializar" << endl;
        cout << "23. Evaluar expresión" << endl;
        
        cout << "24. SALIR" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Ingrese número: ";
                cin >> dato;
                insertarNodo(arbol, dato, nullptr);
                break;
            }
            case 2: {
                cout << "Ingrese números separados por espacios (0 para terminar): ";
                vector<int> valores;
                int val;
                while (cin >> val && val != 0) {
                    valores.push_back(val);
                }
                insertarMultiples(arbol, valores);
                break;
            }
            case 3: {
                cout << "\nÁrbol completo:\n";
                mostrarArbol(arbol, 0);
                break;
            }
            case 4: {
                cout << "Elemento a buscar: ";
                cin >> dato;
                cout << "Resultado: " << (buscarNodo(arbol, dato) ? "Encontrado" : "No encontrado") << endl;
                break;
            }
            case 5: {
                cout << "Elemento a eliminar: ";
                cin >> dato;
                eliminar(arbol, dato);
                break;
            }
            case 6: {
                eliminarArbolCompleto(arbol);
                break;
            }
            case 7: {
                cout << "PreOrden: ";
                preOrden(arbol);
                cout << endl;
                break;
            }
            case 8: {
                cout << "InOrden: ";
                inOrden(arbol);
                cout << endl;
                break;
            }
            case 9: {
                cout << "PostOrden: ";
                postOrden(arbol);
                cout << endl;
                break;
            }
            case 10: {
                recorridoPorNiveles(arbol);
                break;
            }
            case 11: {
                cout << "Recorrido Zigzag:" << endl;
                auto zigzag = recorridoZigzag(arbol);
                for (const auto& nivel : zigzag) {
                    for (int val : nivel) cout << val << " ";
                    cout << endl;
                }
                break;
            }
            case 12: {
                cout << "Ingrese valores para array (usar " << INT_MIN << " para null, 0 para terminar): ";
                vector<int> valores;
                int val;
                while (cin >> val && val != 0) {
                    valores.push_back(val);
                }
                eliminarArbolCompleto(arbol);
                arbol = crearDesdeArray(valores);
                cout << "Árbol creado desde array." << endl;
                break;
            }
            case 13: {
                cout << "Ingrese valores ordenados (0 para terminar): ";
                vector<int> valores;
                int val;
                while (cin >> val && val != 0) {
                    valores.push_back(val);
                }
                sort(valores.begin(), valores.end());
                eliminarArbolCompleto(arbol);
                arbol = crearBSTBalanceado(valores, 0, valores.size() - 1);
                cout << "BST balanceado creado." << endl;
                break;
            }
            case 14: {
                int altura_deseada;
                cout << "Ingrese altura del árbol completo: ";
                cin >> altura_deseada;
                eliminarArbolCompleto(arbol);
                arbol = crearArbolCompleto(altura_deseada);
                cout << "Árbol completo creado." << endl;
                break;
            }
            case 15: {
                string postfija;
                cout << "\nIngrese expresión postfija (sin espacios): ";
                cin >> postfija;
                
                eliminarArbolCompleto(arbol);
                arbol = crearArbolExpresionSeguro(postfija);
                
                if (arbol) {
                    cout << "Árbol de expresión creado exitosamente." << endl;
                    cout << "Visualización del árbol:" << endl;
                    imprimirArbolBonito(arbol);
                    
                    if (esArbolExpresion(arbol)) {
                        double resultado = evaluarExpresion(arbol);
                        cout << "Resultado de la expresión: " << resultado << endl;
                    } else {
                        cout << "Advertencia: El árbol no es una expresión válida" << endl;
                    }
                } else {
                    cout << "No se pudo crear el árbol de expresión." << endl;
                    arbol = nullptr;
                }
                break;
            }
            case 16: {
                imprimirInfoCompleta(arbol);
                break;
            }
            case 17: {
                cout << "\n=== PROPIEDADES DEL ÁRBOL ===" << endl;
                cout << "Es válido BST: " << (esValidoBST(arbol) ? "Sí" : "No") << endl;
                cout << "Es balanceado: " << (esBalanceado(arbol) ? "Sí" : "No") << endl;
                cout << "Es completo: " << (esCompleto(arbol) ? "Sí" : "No") << endl;
                cout << "Es simétrico: " << (esSimetrico(arbol) ? "Sí" : "No") << endl;
                break;
            }
            case 18: {
                int k;
                cout << "Ingrese k para el k-ésimo menor: ";
                cin >> k;
                int resultado = kEsimoMenor(arbol, k);
                cout << "K-ésimo menor: " << (resultado == -1 ? "No encontrado" : to_string(resultado)) << endl;
                break;
            }
            case 19: {
                int suma;
                cout << "Ingrese suma objetivo: ";
                cin >> suma;
                auto paths = todosLosPathsSuma(arbol, suma);
                cout << "Paths con suma " << suma << ":" << endl;
                for (const auto& path : paths) {
                    for (int val : path) cout << val << " ";
                    cout << endl;
                }
                break;
            }
            case 20: {
                Nodo* clon = clonarArbol(arbol);
                cout << "Árbol clonado. Mostrando clon:" << endl;
                imprimirArbolBonito(clon);
                eliminarArbolCompleto(clon);
                break;
            }
            case 21: {
                Nodo* clon = clonarArbol(arbol);
                cout << "Comparando árbol original con su clon: " << (sonIdenticos(arbol, clon) ? "Idénticos" : "Diferentes") << endl;
                eliminarArbolCompleto(clon);
                break;
            }
            case 22: {
                string serializado = serializar(arbol);
                cout << "Árbol serializado: " << serializado << endl;
                
                Nodo* deserializado = deserializar(serializado);
                cout << "Verificando deserialización: " << (sonIdenticos(arbol, deserializado) ? "Exitosa" : "Fallida") << endl;
                eliminarArbolCompleto(deserializado);
                break;
            }
            case 23: {
                if (esArbolExpresion(arbol)) {
                    cout << "Resultado de la expresión: " << evaluarExpresion(arbol) << endl;
                } else {
                    cout << "El árbol actual no es un árbol de expresión válido." << endl;
                }
                break;
            }
        }
        
        if (opcion != 24) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        system("clear"); // o system("cls") en Windows
        
    } while (opcion != 24);
    
    eliminarArbolCompleto(arbol);
    cout << "Programa terminado. Memoria liberada." << endl;
}

void probarExpresionesPostfijas() {
    vector<string> pruebas = {
        "23+",      // Válida: 2+3=5
        "234*+",    // Válida: 2+(3*4)=14
        "23+4*",    // Válida: (2+3)*4=20
        "23",       // Inválida: faltan operadores
        "23++",     // Inválida: muchos operadores
        "2+3",      // Inválida: notación infija
        "",         // Inválida: vacía
        "abc",      // Inválida: caracteres no válidos
        "12+34+*"   // Válida: (1+2)*(3+4)=21
    };
    
    cout << "\n=== PRUEBAS DE EXPRESIONES POSTFIJAS ===" << endl;
    
    for (const string& expr : pruebas) {
        cout << "\nProbando: '" << expr << "'" << endl;
        Nodo* arbolPrueba = crearArbolExpresionSeguro(expr);
        
        if (arbolPrueba) {
            cout << "✓ Árbol creado exitosamente" << endl;
            double resultado = evaluarExpresion(arbolPrueba);
            cout << "  Resultado: " << resultado << endl;
            eliminarArbolCompleto(arbolPrueba);
        } else {
            cout << "✗ Error al crear árbol" << endl;
        }
    }
    
    cout << "\n=== FIN DE PRUEBAS ===" << endl;
}

int main(){
    menu();
    //probarExpresionesPostfijas();
    return 0;
}