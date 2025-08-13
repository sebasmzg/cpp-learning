/*
======================================================================================
    📚 GUÍA EDUCATIVA: ÁRBOLES BINARIOS DE BÚSQUEDA (BST) PARA ENTREVISTAS
======================================================================================

ÍNDICE DE CONTENIDO:
════════════════════

📖 FUNDAMENTOS TEÓRICOS
    1. Definición y Propiedades del BST
    2. Complejidades Temporales
    3. Casos de Uso en Entrevistas

🏗️ ESTRUCTURA BASE Y CONSTRUCTORES  
    1. Definición del Nodo
    2. Constructores y Utilidades Básicas
    3. Creación desde Arrays y Balanceados

🔍 OPERACIONES FUNDAMENTALES
    1. Inserción (LeetCode patrón básico)
    2. Búsqueda (Base para optimizaciones)
    3. Eliminación (Problema clásico de entrevistas)

🌊 RECORRIDOS Y TRAVERSALS
    1. DFS: PreOrder, InOrder, PostOrder
    2. BFS: Level Order y Zigzag
    3. Vistas Especiales (Top View, Vertical)

✅ VALIDACIONES CRÍTICAS
    1. Validar BST (LeetCode 98 - Pregunta frecuente)
    2. Árbol Balanceado (LeetCode 110)
    3. Árbol Completo y Simétrico

🧠 ALGORITMOS AVANZADOS PARA ENTREVISTAS
    1. Diámetro del Árbol (LeetCode 543)
    2. Suma Máxima de Path (LeetCode 124)
    3. Ancestor Común Más Bajo (LeetCode 236)
    4. K-ésimo Elemento (Patrón de inorder)

💾 SERIALIZACIÓN Y MANIPULACIÓN
    1. Serialize/Deserialize (LeetCode 297)
    2. Clonación y Comparación
    3. Path Finding y Distancias

🌳 ÁRBOLES DE EXPRESIÓN
    1. Construcción desde Postfix
    2. Evaluación de Expresiones
    3. Validación de Expresiones

🎯 UTILIDADES DE DEBUGGING
    1. Visualización Pretty Print
    2. Información Completa del Árbol
    3. Sistema de Pruebas

*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <functional>
#include <algorithm>
#include <climits>
#include <cmath>
#include <string>

using namespace std;

/*
======================================================================================
📖 FUNDAMENTOS TEÓRICOS
======================================================================================

¿POR QUÉ BST ES IMPORTANTE EN ENTREVISTAS?
- Combina eficiencia de búsqueda con flexibilidad de inserción/eliminación
- Base para estructuras más complejas (AVL, Red-Black, B-Trees)
- Aparece en problemas de validación, recorridos y optimización

COMPLEJIDADES CLAVE PARA RECORDAR:
- Búsqueda/Inserción/Eliminación: O(log n) promedio, O(n) peor caso
- Recorridos: O(n) siempre
- Espacio: O(h) para recursión, donde h es la altura

PROPIEDADES CRÍTICAS DEL BST:
- Subárbol izquierdo: todos los valores < raíz
- Subárbol derecho: todos los valores > raíz  
- Recorrido inorder produce secuencia ordenada

*/

//======================================================================================
//🏗️ ESTRUCTURA BASE Y CONSTRUCTORES
//======================================================================================

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;  // Útil para operaciones de eliminación y navegación

    // Constructor principal - inicializa completamente el nodo
    Nodo(int valor, Nodo* p = nullptr) : dato(valor), izq(nullptr), der(nullptr), padre(p) {}
};

// Variable global para demostración (en entrevistas, usa parámetros)
Nodo* arbol = nullptr;

// ¿POR QUÉ crear nodos así? Encapsula la inicialización y reduce errores
Nodo* crearNodo(int dato, Nodo* padre = nullptr) {
    return new Nodo(dato, padre);
}

// ¿POR QUÉ calcular altura? Base para determinar balanceado, complejidad visual
int altura(Nodo* arbol) {
    if (arbol == nullptr) return -1;  // Convención: árbol vacío tiene altura -1
    return max(altura(arbol->izq), altura(arbol->der)) + 1;
}

// ¿POR QUÉ contar nodos? Útil para validaciones y análisis de performance
int contarNodos(Nodo* arbol) {
    if (arbol == nullptr) return 0;
    return 1 + contarNodos(arbol->izq) + contarNodos(arbol->der);
}

// ¿POR QUÉ buscar min/max? Crítico para eliminación y validación de BST
Nodo* minimo(Nodo* arbol) {
    if (arbol == nullptr) return nullptr;
    // En BST, el mínimo está siempre en el extremo izquierdo
    while (arbol->izq != nullptr) {
        arbol = arbol->izq;
    }
    return arbol;
}

Nodo* maximo(Nodo* arbol) {
    if (arbol == nullptr) return nullptr;
    // En BST, el máximo está siempre en el extremo derecho
    while (arbol->der != nullptr) {
        arbol = arbol->der;
    }
    return arbol;
}

// ¿POR QUÉ clonar? Útil para backup, testing, y problemas de comparación
Nodo* clonarArbol(Nodo* original, Nodo* padre = nullptr) {
    if (original == nullptr) return nullptr;
    
    Nodo* copia = new Nodo(original->dato, padre);
    // Recursión mantiene la estructura exacta del árbol original
    copia->izq = clonarArbol(original->izq, copia);
    copia->der = clonarArbol(original->der, copia);
    return copia;
}

// ¿POR QUÉ comparar árboles? Validación de operaciones, testing
bool sonIdenticos(Nodo* a, Nodo* b) {
    // Caso base: ambos nulos
    if (a == nullptr && b == nullptr) return true;
    
    // Un nulo, otro no - definitivamente diferentes
    if (a == nullptr || b == nullptr) return false;
    
    // Deben coincidir valor y estructura recursivamente
    return (a->dato == b->dato) && 
           sonIdenticos(a->izq, b->izq) && 
           sonIdenticos(a->der, b->der);
}

// ¿POR QUÉ crear desde array? Construcción rápida para testing, LeetCode input format
Nodo* crearDesdeArray(const vector<int>& valores) {
    if (valores.empty() || valores[0] == INT_MIN) return nullptr;
    
    Nodo* raiz = new Nodo(valores[0]);
    queue<Nodo*> cola;
    cola.push(raiz);
    
    // Construcción level-order: cada nodo toma dos siguientes valores como hijos
    for (size_t i = 1; i < valores.size(); i += 2) {
        Nodo* actual = cola.front();
        cola.pop();
        
        // Hijo izquierdo
        if (i < valores.size() && valores[i] != INT_MIN) {
            actual->izq = new Nodo(valores[i], actual);
            cola.push(actual->izq);
        }
        
        // Hijo derecho
        if (i + 1 < valores.size() && valores[i + 1] != INT_MIN) {
            actual->der = new Nodo(valores[i + 1], actual);
            cola.push(actual->der);
        }
    }
    return raiz;
}

// ¿POR QUÉ crear BST balanceado? Performance óptima O(log n), evita degeneración
Nodo* crearBSTBalanceado(const vector<int>& arr, int inicio, int fin, Nodo* padre = nullptr) {
    if (inicio > fin) return nullptr;
    
    // Divide y vencerás: raíz en el medio mantiene balance
    int medio = inicio + (fin - inicio) / 2;
    Nodo* raiz = new Nodo(arr[medio], padre);
    
    // Recursión construye subárboles balanceados
    raiz->izq = crearBSTBalanceado(arr, inicio, medio - 1, raiz);
    raiz->der = crearBSTBalanceado(arr, medio + 1, fin, raiz);
    return raiz;
}

//======================================================================================
//🔍 OPERACIONES FUNDAMENTALES
//======================================================================================

// ¿POR QUÉ inserción recursiva? Mantiene propiedades BST automáticamente
void insertarNodo(Nodo*& arbol, int dato, Nodo* padre = nullptr) {
    // Caso base: posición encontrada para insertar
    if (arbol == nullptr) {
        arbol = crearNodo(dato, padre);
        return;
    }
    
    // Navegación basada en propiedad BST: menores a la izquierda
    if (dato < arbol->dato) {
        insertarNodo(arbol->izq, dato, arbol);
    } 
    // Mayores a la derecha (evitamos duplicados)
    else if (dato > arbol->dato) {
        insertarNodo(arbol->der, dato, arbol);
    }
    // Si dato == arbol->dato, no insertamos (evitar duplicados)
}

// ¿POR QUÉ inserción múltiple? Construcción rápida de casos de prueba
void insertarMultiples(Nodo*& raiz, const vector<int>& valores) {
    for (int valor : valores) {
        insertarNodo(raiz, valor, nullptr);
    }
    cout << "✅ Insertados " << valores.size() << " valores." << endl;
}

// ¿POR QUÉ búsqueda recursiva? Aprovecha estructura BST para eficiencia O(log n)
bool buscarNodo(Nodo* arbol, int dato) {
    // Caso base: no encontrado
    if (arbol == nullptr) return false;
    
    // Encontrado
    if (arbol->dato == dato) return true;
    
    // Navegación inteligente: solo explora subárbol relevante
    if (dato < arbol->dato) {
        return buscarNodo(arbol->izq, dato);
    } else {
        return buscarNodo(arbol->der, dato);
    }
}

// ELIMINACIÓN: Caso más complejo, 3 escenarios diferentes
// ¿POR QUÉ estas funciones auxiliares? Eliminación segura requiere múltiples pasos

void reemplazar(Nodo* reemplazar, Nodo* nuevoNodo) {
    // Actualizar referencia del padre al nuevo nodo
    if (reemplazar->padre) {
        if (reemplazar->dato == reemplazar->padre->izq->dato) {
            reemplazar->padre->izq = nuevoNodo;
        } else {
            reemplazar->padre->der = nuevoNodo;
        }
    }
    
    // Actualizar referencia del nuevo nodo al padre
    if (nuevoNodo) {
        nuevoNodo->padre = reemplazar->padre;
    }
}

void destruirNodo(Nodo* nodoEliminar) {
    // Desconectar antes de eliminar para evitar problemas de memoria
    nodoEliminar->izq = nullptr;
    nodoEliminar->der = nullptr;
    delete nodoEliminar;
}

// ¿POR QUÉ tres casos? BST debe mantener propiedades después de eliminación
void eliminarNodo(Nodo* nodoEliminar) {
    // CASO 1: Nodo con dos hijos - el más complejo
    if (nodoEliminar->izq && nodoEliminar->der) {
        // Encuentra sucesor inorder (mínimo del subárbol derecho)
        Nodo* sucesor = minimo(nodoEliminar->der);
        
        // Reemplaza valor (mantiene estructura, cambia contenido)
        nodoEliminar->dato = sucesor->dato;
        
        // Elimina sucesor (que tendrá 0 o 1 hijo)
        eliminarNodo(sucesor);
    }
    // CASO 2: Nodo con un hijo - reemplazar directamente
    else if (nodoEliminar->izq) {
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    else if (nodoEliminar->der) {
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    // CASO 3: Nodo hoja - eliminar directamente
    else {
        reemplazar(nodoEliminar, nullptr);
        destruirNodo(nodoEliminar);
    }
}

void eliminar(Nodo*& arbol, int dato) {
    if (arbol == nullptr) return;
    
    // Navegación BST para encontrar nodo a eliminar
    if (dato < arbol->dato) {
        eliminar(arbol->izq, dato);
    } else if (dato > arbol->dato) {
        eliminar(arbol->der, dato);
    } else {
        // Nodo encontrado - proceder con eliminación
        eliminarNodo(arbol);
    }
}

void eliminarArbolCompleto(Nodo*& raiz) {
    if (raiz == nullptr) return;
    
    // Post-order: eliminar hijos antes que padre
    eliminarArbolCompleto(raiz->izq);
    eliminarArbolCompleto(raiz->der);
    delete raiz;
    raiz = nullptr;
}

//======================================================================================
//🌊 RECORRIDOS Y TRAVERSALS
//======================================================================================

// ¿POR QUÉ recorridos DFS? Base para muchos algoritmos, cada uno útil en diferentes contextos

// PRE-ORDER: Útil para copiar estructura, serialización
void preOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    
    cout << arbol->dato << " ";  // Procesar raíz primero
    preOrden(arbol->izq);        // Luego subárbol izquierdo
    preOrden(arbol->der);        // Finalmente subárbol derecho
}

// IN-ORDER: ¡CRÍTICO! En BST produce secuencia ordenada
void inOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    
    inOrden(arbol->izq);         // Subárbol izquierdo (menores)
    cout << arbol->dato << " ";  // Raíz (valor medio)
    inOrden(arbol->der);         // Subárbol derecho (mayores)
}

// POST-ORDER: Útil para liberación de memoria, cálculos bottom-up
void postOrden(Nodo* arbol) {
    if (arbol == nullptr) return;
    
    postOrden(arbol->izq);       // Procesar hijos primero
    postOrden(arbol->der);
    cout << arbol->dato << " ";  // Raíz al final
}

// ¿POR QUÉ BFS level-order? Exploración por niveles, útil para construcción e impresión
void recorridoPorNiveles(Nodo* raiz) {
    if (raiz == nullptr) return;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    
    cout << "📊 Level-order: ";
    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();
        
        cout << actual->dato << " ";
        
        // Agregar hijos para procesar en siguientes niveles
        if (actual->izq) cola.push(actual->izq);
        if (actual->der) cola.push(actual->der);
    }
    cout << endl;
}

// ¿POR QUÉ zigzag? Problema común en entrevistas, muestra dominio de BFS modificado
vector<vector<int>> recorridoZigzag(Nodo* raiz) {
    vector<vector<int>> resultado;
    if (raiz == nullptr) return resultado;
    
    queue<Nodo*> cola;
    cola.push(raiz);
    bool izqADer = true;  // Alterna dirección cada nivel
    
    while (!cola.empty()) {
        int tamaño = cola.size();
        vector<int> nivel(tamaño);
        
        for (int i = 0; i < tamaño; i++) {
            Nodo* nodo = cola.front();
            cola.pop();
            
            // Índice depende de dirección actual
            int indice = izqADer ? i : (tamaño - 1 - i);
            nivel[indice] = nodo->dato;
            
            // Siempre agregamos en orden normal
            if (nodo->izq) cola.push(nodo->izq);
            if (nodo->der) cola.push(nodo->der);
        }
        
        izqADer = !izqADer;  // Alterna para siguiente nivel
        resultado.push_back(nivel);
    }
    
    return resultado;
}

// ¿POR QUÉ vista desde arriba? Demuestra comprensión de coordenadas y mapas
vector<int> vistaDesdeArriba(Nodo* raiz) {
    if (!raiz) return {};
    
    map<int, int> columnas;  // columna -> primer valor visto
    queue<pair<Nodo*, int>> cola;
    cola.push({raiz, 0});
    
    while (!cola.empty()) {
        auto [nodo, col] = cola.front();
        cola.pop();
        
        // Solo registrar primer nodo visto en cada columna
        if (columnas.find(col) == columnas.end()) {
            columnas[col] = nodo->dato;
        }
        
        // Izquierdo: col-1, Derecho: col+1
        if (nodo->izq) cola.push({nodo->izq, col - 1});
        if (nodo->der) cola.push({nodo->der, col + 1});
    }
    
    vector<int> resultado;
    for (auto& [col, val] : columnas) {
        resultado.push_back(val);
    }
    return resultado;
}

//======================================================================================
//✅ VALIDACIONES CRÍTICAS (PREGUNTAS FRECUENTES EN ENTREVISTAS)
//======================================================================================

// 🎯 LeetCode 98: Validate BST - ¡MUY COMÚN EN ENTREVISTAS!
// ¿POR QUÉ límites min/max? Validación local (padre-hijo) no es suficiente
bool esValidoBST(Nodo* raiz, long minimo = LONG_MIN, long maximo = LONG_MAX) {
    if (raiz == nullptr) return true;
    
    // El nodo debe estar dentro de los límites establecidos por ancestros
    if (raiz->dato <= minimo || raiz->dato >= maximo) return false;
    
    // Recursión actualiza límites: izquierdo tiene nuevo máximo, derecho nuevo mínimo
    return esValidoBST(raiz->izq, minimo, raiz->dato) && 
           esValidoBST(raiz->der, raiz->dato, maximo);
}

// 🎯 LeetCode 110: Balanced Binary Tree
// ¿POR QUÉ retornar -1? Técnica elegante: valor especial indica desbalanceado
bool esBalanceado(Nodo* raiz) {
    function<int(Nodo*)> checkBalance = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        // Verificar subárbol izquierdo
        int izq = checkBalance(nodo->izq);
        if (izq == -1) return -1;  // Propagación inmediata de error
        
        // Verificar subárbol derecho
        int der = checkBalance(nodo->der);
        if (der == -1) return -1;
        
        // Verificar balance en nodo actual
        if (abs(izq - der) > 1) return -1;
        
        return max(izq, der) + 1;  // Altura del subárbol actual
    };
    
    return checkBalance(raiz) != -1;
}

// ¿POR QUÉ verificar completitud? Relacionado con heaps, árboles perfectos
bool esCompleto(Nodo* raiz) {
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
            // Si ya encontramos null, no debería haber más nodos
            if (encontradoNull) return false;
            
            cola.push(nodo->izq);   // null también se agrega
            cola.push(nodo->der);
        }
    }
    
    return true;
}

// 🎯 LeetCode 101: Symmetric Tree
// ¿POR QUÉ función auxiliar? Comparar izquierda con derecha requiere dos punteros
bool esSimetrico(Nodo* raiz) {
    if (!raiz) return true;
    
    function<bool(Nodo*, Nodo*)> esEspejo = [&](Nodo* izq, Nodo* der) -> bool {
        if (!izq && !der) return true;
        if (!izq || !der) return false;
        
        // Simetría: valor igual, pero estructura cruzada
        return (izq->dato == der->dato) && 
               esEspejo(izq->izq, der->der) &&   // Exteriores
               esEspejo(izq->der, der->izq);     // Interiores
    };
    
    return esEspejo(raiz->izq, raiz->der);
}

//======================================================================================
//🧠 ALGORITMOS AVANZADOS PARA ENTREVISTAS
//======================================================================================

// 🎯 LeetCode 543: Diameter of Binary Tree
// ¿POR QUÉ variable externa? El diámetro puede no pasar por la raíz
int diametro(Nodo* raiz) {
    int maxDiametro = 0;
    
    function<int(Nodo*)> profundidad = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        int izq = profundidad(nodo->izq);
        int der = profundidad(nodo->der);
        
        // Diámetro pasando por este nodo
        maxDiametro = max(maxDiametro, izq + der);
        
        // Retorna altura para padre
        return max(izq, der) + 1;
    };
    
    profundidad(raiz);
    return maxDiametro;
}

// 🎯 LeetCode 124: Binary Tree Maximum Path Sum
// ¿POR QUÉ max(0, ...)? Ignorar paths negativos es mejor que incluirlos
int sumMaximaPath(Nodo* raiz) {
    int maxSuma = INT_MIN;
    
    function<int(Nodo*)> maxPathDown = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        
        // Solo considerar paths positivos
        int izq = max(0, maxPathDown(nodo->izq));
        int der = max(0, maxPathDown(nodo->der));
        
        // Path que pasa por este nodo (no retornamos esto)
        maxSuma = max(maxSuma, nodo->dato + izq + der);
        
        // Retorna mejor path hacia arriba
        return nodo->dato + max(izq, der);
    };
    
    maxPathDown(raiz);
    return maxSuma;
}

// 🎯 LeetCode 236: Lowest Common Ancestor
// ¿POR QUÉ retornar nodo inmediatamente? Optimización: first match is LCA candidate
Nodo* ancestroComun(Nodo* raiz, Nodo* p, Nodo* q) {
    // Base: encontramos objetivo o llegamos a null
    if (!raiz || raiz == p || raiz == q) return raiz;
    
    // Buscar en ambos subárboles
    Nodo* izq = ancestroComun(raiz->izq, p, q);
    Nodo* der = ancestroComun(raiz->der, p, q);
    
    // Si ambos retornan algo, este nodo es LCA
    if (izq && der) return raiz;
    
    // Retornar el que encontró algo
    return izq ? izq : der;
}

// PATRÓN K-ÉSIMO: Aprovecha inorder ordenado en BST
// ¿POR QUÉ inorder? En BST produce secuencia ordenada automáticamente
int kEsimoMenor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    
    function<void(Nodo*)> inorder = [&](Nodo* nodo) {
        if (!nodo || contador >= k) return;  // Early termination
        
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

// ¿POR QUÉ mayor es inorder reverso? Derecha antes que izquierda = mayor a menor
int kEsimoMayor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    
    function<void(Nodo*)> inorderReverso = [&](Nodo* nodo) {
        if (!nodo || contador >= k) return;
        
        inorderReverso(nodo->der);   // Derecha primero = mayor
        
        contador++;
        if (contador == k) {
            resultado = nodo->dato;
            return;
        }
        
        inorderReverso(nodo->izq);
    };
    
    inorderReverso(raiz);
    return resultado;
}

// BÚSQUEDA DE PATHS CON SUMA OBJETIVO
// ¿POR QUÉ backtracking? Necesitamos explorar todos los paths posibles
vector<vector<int>> todosLosPathsSuma(Nodo* raiz, int sumaObjetivo) {
    vector<vector<int>> resultado;
    vector<int> pathActual;
    
    function<void(Nodo*, int)> dfs = [&](Nodo* nodo, int sumaRestante) {
        if (!nodo) return;
        
        // Agregar nodo actual al path
        pathActual.push_back(nodo->dato);
        sumaRestante -= nodo->dato;
        
        // Si es hoja y suma es 0, encontramos path válido
        if (!nodo->izq && !nodo->der && sumaRestante == 0) {
            resultado.push_back(pathActual);
        } else {
            // Continuar búsqueda en hijos
            dfs(nodo->izq, sumaRestante);
            dfs(nodo->der, sumaRestante);
        }
        
        // BACKTRACK: remover nodo antes de regresar
        pathActual.pop_back();
    };
    
    dfs(raiz, sumaObjetivo);
    return resultado;
}

//======================================================================================
//💾 SERIALIZACIÓN Y MANIPULACIÓN (LeetCode 297)
//======================================================================================

// ¿POR QUÉ serialización? Persistencia, transmisión, debugging
string serializar(Nodo* raiz) {
    if (!raiz) return "null,";
    
    // Preorder: raíz, izquierda, derecha
    return to_string(raiz->dato) + "," + 
           serializar(raiz->izq) + 
           serializar(raiz->der);
}

// ¿POR QUÉ referencia a string? Simula stream processing, modifica entrada
Nodo* deserializar(string& data) {
    if (data.substr(0, 4) == "null") {
        data = data.substr(5);  // Consume "null,"
        return nullptr;
    }
    
    // Extraer primer valor
    int pos = data.find(',');
    int val = stoi(data.substr(0, pos));
    data = data.substr(pos + 1);  // Consume valor
    
    // Reconstruir en preorder
    Nodo* nodo = new Nodo(val);
    nodo->izq = deserializar(data);
    nodo->der = deserializar(data);
    
    return nodo;
}

//======================================================================================
//🌳 ÁRBOLES DE EXPRESIÓN (APLICACIÓN ESPECIALIZADA)
//======================================================================================

// ¿POR QUÉ árboles de expresión? Evaluación eficiente, parsing, compiladores

bool esArbolExpresion(Nodo* raiz) {
    if (!raiz) return false;
    
    // Hoja = operando
    if (!raiz->izq && !raiz->der) {
        return isdigit(raiz->dato) || (raiz->dato >= 'a' && raiz->dato <= 'z');
    }
    
    // Nodo interno = operador con exactamente 2 hijos
    if (raiz->izq && raiz->der) {
        char op = raiz->dato;
        return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') &&
               esArbolExpresion(raiz->izq) && esArbolExpresion(raiz->der);
    }
    
    return false;  // Un hijo nulo, otro no = inválido
}

// ¿POR QUÉ postorder para evaluación? Necesitamos operandos antes que operadores
double evaluarExpresion(Nodo* raiz) {
    if (!raiz) return 0;
    
    // Hoja: retornar valor numérico
    if (!raiz->izq && !raiz->der) {
        if (isdigit(raiz->dato)) {
            return static_cast<double>(raiz->dato - '0');
        }
        return 0;  // Error case
    }
    
    // Evaluar operandos recursivamente
    double izq = evaluarExpresion(raiz->izq);
    double der = evaluarExpresion(raiz->der);
    
    // Aplicar operador
    switch (raiz->dato) {
        case '+': return izq + der;
        case '-': return izq - der;
        case '*': return izq * der;
        case '/': return (der != 0) ? izq / der : 0;
        case '^': return pow(izq, der);
        default: return 0;
    }
}

// ¿POR QUÉ usar stack? Postfix evaluation es naturalmente basado en stack
Nodo* crearArbolExpresion(const string& postfija) {
    if (postfija.empty()) return nullptr;
    
    stack<Nodo*> pila;
    
    for (char c : postfija) {
        if (c == ' ') continue;
        
        if (isdigit(c)) {
            pila.push(new Nodo(c));
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (pila.size() < 2) return nullptr;  // Error: insuficientes operandos
            
            Nodo* der = pila.top(); pila.pop();
            Nodo* izq = pila.top(); pila.pop();
            
            Nodo* operador = new Nodo(c);
            operador->izq = izq;
            operador->der = der;
            izq->padre = operador;
            der->padre = operador;
            
            pila.push(operador);
        }
    }
    
    return (pila.size() == 1) ? pila.top() : nullptr;
}

//======================================================================================
//🎯 UTILIDADES DE DEBUGGING Y VISUALIZACIÓN
//======================================================================================

// ¿POR QUÉ visualización bonita? Debugging visual, presentación en entrevistas
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

// ¿POR QUÉ mostrar simple rotado? Visualización rápida de estructura
void mostrarArbol(Nodo* arbol, int espaciado = 0) {
    if (arbol == nullptr) return;
    
    // Derecha primero (aparece arriba)
    mostrarArbol(arbol->der, espaciado + 4);
    
    // Espaciado proporcional al nivel
    for (int i = 0; i < espaciado; ++i) {
        cout << " ";
    }
    cout << arbol->dato << endl;
    
    // Izquierda después (aparece abajo)
    mostrarArbol(arbol->izq, espaciado + 4);
}

// ¿POR QUÉ análisis completo? Resumen rápido de todas las propiedades importantes
void imprimirInfoCompleta(Nodo* raiz) {
    if (!raiz) {
        cout << "🌳 Árbol vacío" << endl;
        return;
    }
    
    cout << "\n🔍 ANÁLISIS COMPLETO DEL ÁRBOL" << endl;
    cout << "══════════════════════════════" << endl;
    cout << "📊 Altura: " << altura(raiz) << endl;
    cout << "📊 Nodos: " << contarNodos(raiz) << endl;
    cout << "✅ BST válido: " << (esValidoBST(raiz) ? "Sí" : "No") << endl;
    cout << "⚖️  Balanceado: " << (esBalanceado(raiz) ? "Sí" : "No") << endl;
    cout << "🔲 Completo: " << (esCompleto(raiz) ? "Sí" : "No") << endl;
    cout << "🪞 Simétrico: " << (esSimetrico(raiz) ? "Sí" : "No") << endl;
    cout << "📏 Diámetro: " << diametro(raiz) << endl;
    
    cout << "\n👁️  Vista superior: ";
    vector<int> vista = vistaDesdeArriba(raiz);
    for (int val : vista) cout << val << " ";
    cout << endl;
    
    cout << "\n🌳 Visualización:" << endl;
    imprimirArbolBonito(raiz);
    cout << "══════════════════════════════\n" << endl;
}

//======================================================================================
//🧪 SISTEMA DE PRUEBAS Y EJEMPLOS
//======================================================================================

void demostrarOperacionesBasicas() {
    cout << "\n🚀 DEMO: Operaciones Básicas" << endl;
    cout << "═══════════════════════════" << endl;
    
    Nodo* demo = nullptr;
    vector<int> valores = {50, 30, 70, 20, 40, 60, 80};
    
    cout << "📝 Insertando: ";
    for (int val : valores) {
        cout << val << " ";
        insertarNodo(demo, val);
    }
    cout << endl;
    
    cout << "\n🌳 Árbol resultante:" << endl;
    imprimirArbolBonito(demo);
    
    cout << "\n🔍 Recorridos:" << endl;
    cout << "Pre-order: "; preOrden(demo); cout << endl;
    cout << "In-order:  "; inOrden(demo); cout << endl;
    cout << "Post-order: "; postOrden(demo); cout << endl;
    
    eliminarArbolCompleto(demo);
}

void demostrarAlgoritmosAvanzados() {
    cout << "\n🧠 DEMO: Algoritmos Avanzados" << endl;
    cout << "═══════════════════════════" << endl;
    
    vector<int> valores = {1, 2, 3, 4, 5, 6, 7};
    Nodo* balanceado = crearBSTBalanceado(valores, 0, valores.size() - 1);
    
    cout << "🌳 BST Balanceado creado:" << endl;
    imprimirArbolBonito(balanceado);
    
    cout << "\n📊 Análisis:" << endl;
    cout << "Diámetro: " << diametro(balanceado) << endl;
    cout << "2do menor: " << kEsimoMenor(balanceado, 2) << endl;
    cout << "2do mayor: " << kEsimoMayor(balanceado, 2) << endl;
    
    eliminarArbolCompleto(balanceado);
}

//======================================================================================
//📖 MENÚ EDUCATIVO INTERACTIVO
//======================================================================================

void menuEducativo() {
    int opcion;
    
    do {
        cout << "\n🎓 GUÍA EDUCATIVA BST - MENÚ INTERACTIVO" << endl;
        cout << "═══════════════════════════════════════" << endl;
        cout << "🏗️  CONSTRUCCIÓN" << endl;
        cout << "  1. Insertar nodo individual" << endl;
        cout << "  2. Crear BST balanceado" << endl;
        cout << "  3. Crear desde array" << endl;
        
        cout << "\n🔍 ANÁLISIS" << endl;
        cout << "  4. Mostrar información completa" << endl;
        cout << "  5. Verificar propiedades BST" << endl;
        cout << "  6. Buscar nodo" << endl;
        
        cout << "\n🌊 RECORRIDOS" << endl;
        cout << "  7. Todos los recorridos DFS" << endl;
        cout << "  8. Recorrido zigzag" << endl;
        cout << "  9. Vista desde arriba" << endl;
        
        cout << "\n🧠 ALGORITMOS AVANZADOS" << endl;
        cout << "  10. K-ésimo menor/mayor" << endl;
        cout << "  11. Paths con suma objetivo" << endl;
        cout << "  12. Diámetro y suma máxima" << endl;
        
        cout << "\n🧪 DEMOS EDUCATIVOS" << endl;
        cout << "  13. Demo operaciones básicas" << endl;
        cout << "  14. Demo algoritmos avanzados" << endl;
        
        cout << "  0. Salir" << endl;
        cout << "\n👉 Seleccione opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int valor;
                cout << "📝 Ingrese valor: ";
                cin >> valor;
                insertarNodo(arbol, valor);
                cout << "✅ Insertado: " << valor << endl;
                break;
            }
            
            case 2: {
                cout << "📝 Ingrese valores ordenados (0 para terminar): ";
                vector<int> valores;
                int val;
                while (cin >> val && val != 0) {
                    valores.push_back(val);
                }
                eliminarArbolCompleto(arbol);
                arbol = crearBSTBalanceado(valores, 0, valores.size() - 1);
                cout << "✅ BST balanceado creado" << endl;
                break;
            }
            
            case 4: {
                imprimirInfoCompleta(arbol);
                break;
            }
            
            case 5: {
                cout << "\n🔍 PROPIEDADES DEL ÁRBOL:" << endl;
                cout << "BST válido: " << (esValidoBST(arbol) ? "✅ Sí" : "❌ No") << endl;
                cout << "Balanceado: " << (esBalanceado(arbol) ? "✅ Sí" : "❌ No") << endl;
                cout << "Completo: " << (esCompleto(arbol) ? "✅ Sí" : "❌ No") << endl;
                break;
            }
            
            case 7: {
                cout << "\n🌊 RECORRIDOS DFS:" << endl;
                cout << "Pre-order:  "; preOrden(arbol); cout << endl;
                cout << "In-order:   "; inOrden(arbol); cout << endl;
                cout << "Post-order: "; postOrden(arbol); cout << endl;
                break;
            }
            
            case 10: {
                int k;
                cout << "📝 Ingrese k: ";
                cin >> k;
                cout << k << "-ésimo menor: " << kEsimoMenor(arbol, k) << endl;
                cout << k << "-ésimo mayor: " << kEsimoMayor(arbol, k) << endl;
                break;
            }
            
            case 13: {
                demostrarOperacionesBasicas();
                break;
            }
            
            case 14: {
                demostrarAlgoritmosAvanzados();
                break;
            }
        }
        
        if (opcion != 0) {
            cout << "\n⏳ Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 0);
    
    eliminarArbolCompleto(arbol);
    cout << "\n🎓 ¡Gracias por usar la Guía Educativa BST!" << endl;
    cout << "💡 Recuerda: Practica estos algoritmos hasta que sean automáticos." << endl;
}

//======================================================================================
//🎯 FUNCIÓN PRINCIPAL
//======================================================================================

int main() {
    cout << "🌳 BIENVENIDO A LA GUÍA EDUCATIVA DE BST" << endl;
    cout << "══════════════════════════════════════" << endl;
    cout << "📚 Esta guía está optimizada para preparación de entrevistas" << endl;
    cout << "🎯 Incluye algoritmos frecuentes de LeetCode y técnicas esenciales" << endl;
    cout << "💡 Cada función explica el 'POR QUÉ', no solo el 'QUÉ'" << endl;
    
    menuEducativo();
    
    return 0;
}

/*
======================================================================================
📝 RESUMEN DE PATRONES CLAVE PARA ENTREVISTAS
======================================================================================

🎯 PATRONES MÁS COMUNES:
1. Validación BST (min/max bounds)
2. Recorrido inorder para aprovechar orden
3. Recursión con estado global (diámetro, suma máxima)
4. BFS modificado (level order, zigzag)
5. Backtracking para paths (suma objetivo)

⚡ OPTIMIZACIONES IMPORTANTES:
- Early termination en búsquedas
- Una sola pasada para múltiples cálculos
- Aprovechas propiedades BST para O(log n)
- Técnicas de memoria eficiente

🧠 TÉCNICAS DE PENSAMIENTO:
- Identificar casos base recursivos
- Distinguir entre información local vs global
- Usar función auxiliar cuando necesites múltiples parámetros
- Combinar algoritmos (ej: validación + cálculo altura)

💡 CONSEJOS PARA ENTREVISTAS:
- Siempre pregunta sobre duplicados
- Considera casos edge (árbol vacío, un nodo)
- Explica complejidad temporal y espacial
- Demuestra entendimiento de trade-offs
- Practica explicación while coding

¡PRACTICA ESTOS PATRONES HASTA QUE SEAN AUTOMÁTICOS! 🚀
======================================================================================
*/
