#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <climits>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// =============================================================================
// ÁRBOL AVL
// =============================================================================
//
// - Estructura de datos no lineal y dinámica
// - Balanceo automático: Los árboles AVL se autoajustan para mantener su altura balanceada.
// - Rotaciones: Se utilizan rotaciones simples y dobles para restaurar el equilibrio.
// - Factor de equilibrio: La diferencia de altura entre el subárbol izquierdo y derecho de un nodo.
// - A diferencia de los árboles binarios de búsqueda (BST), los árboles AVL garantizan una búsqueda, inserción y eliminación en tiempo O(log n).
// - Aplicaciones: Los árboles AVL son útiles en situaciones donde se requiere un acceso rápido a los datos y se realizan muchas inserciones y eliminaciones.

// =============================================================================
// 1. ESTRUCTURA BÁSICA Y OPERACIONES FUNDAMENTALES (AVL)
// =============================================================================

class AVLTree {
    private:
        struct Node {
            int data, height;   // Datos del nodo y su altura
            int frequency;      // Contador para duplicados
            Node *left, *right; // Punteros a los hijos izquierdo y derecho
            
            // Constructor para inicializar el nodo con datos y punteros nulos
            Node(int d) : data(d), height(1), frequency(1), left(nullptr), right(nullptr) {}
        };

        Node* root; // Raíz del árbol AVL

        int height(Node* node) {
            // Devuelve la altura de un nodo o 0 si es nulo
            return node ? node->height : 0;
        }

        int getBalance(Node* node) {
            // Devuelve el factor de equilibrio de un nodo
            // Si es nulo, el balance es 0
            return node ? height(node->left) - height(node->right) : 0;
        }

        // Al actualizar las alturas se suma 1, ya que se está subiendo un nivel en el árbol
        Node* rightRotate(Node* y){
            Node* x = y->left; // Hijo izquierdo de y
            Node* T2 = x->right; // Hijo derecho de x
            // Realiza la rotación
            x->right = y;
            y->left = T2;
            // Actualiza las alturas
            y->height = 1 + max(height(y->left), height(y->right));
            x->height = 1 + max(height(x->left), height(x->right));
            // Devuelve el nuevo nodo raíz
            return x;
        }

        Node* leftRotate(Node* x){
            Node* y = x->right; // Hijo derecho de x
            Node* T2 = y->left; // Hijo izquierdo de y
            // Realiza la rotación
            y->left = x;
            x->right = T2;
            // Actualiza las alturas
            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));
            // Devuelve el nuevo nodo raíz
            return y;
        }

        Node* insertRec(Node* node, int value){
            // 1. Realiza la inserción normal en el árbol BST
            if (!node) return new Node(value);
            
            if (value < node->data)
                node->left = insertRec(node->left, value);
            else if(value > node->data)
                node->right = insertRec(node->right, value);
            else {
                // ¿POR QUÉ incrementar frecuencia? Permite manejar duplicados eficientemente
                node->frequency++;
                return node; // No necesita rebalanceo para duplicados
            }

            // 2. Actualiza la altura del nodo ancestro
            node->height = 1 + max(height(node->left), height(node->right));

            // 3. Obtiene el factor de equilibrio
            int balance = getBalance(node);

            // 4. Si el nodo se desbalancea, hay 4 casos
            // Caso Izquierda Izquierda
            if (balance > 1 && value < node->left->data)
                return rightRotate(node);

            // Caso Derecha Derecha
            if (balance < -1 && value > node->right->data)
                return leftRotate(node);

            // Caso Izquierda Derecha
            if (balance > 1 && value > node->left->data) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // Caso Derecha Izquierda
            if (balance < -1 && value < node->right->data) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            // Retorna el puntero del nodo (sin cambios)
            return node;
        }

        // ¿POR QUÉ minValueNode? Necesario para eliminación con dos hijos
        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current->left != nullptr)
                current = current->left;
            return current;
        }

        // ELIMINACIÓN CON REBALANCEO AVL
        Node* deleteRec(Node* root, int value) {
            // 1. ELIMINACIÓN BST ESTÁNDAR
            if (root == nullptr) return root;
            
            if (value < root->data)
                root->left = deleteRec(root->left, value);
            else if (value > root->data)
                root->right = deleteRec(root->right, value);
            else {
                // Nodo encontrado
                if (root->frequency > 1) {
                    // ¿POR QUÉ decrementar? Eliminar una instancia pero mantener nodo
                    root->frequency--;
                    return root;
                }
                
                // Última instancia - eliminar nodo
                if ((root->left == nullptr) || (root->right == nullptr)) {
                    Node* temp = root->left ? root->left : root->right;
                    
                    if (temp == nullptr) {
                        temp = root;
                        root = nullptr;
                    } else
                        *root = *temp;
                    delete temp;
                } else {
                    Node* temp = minValueNode(root->right);
                    root->data = temp->data;
                    root->frequency = temp->frequency;
                    temp->frequency = 1; // Para eliminar solo esta instancia
                    root->right = deleteRec(root->right, temp->data);
                }
            }
            
            if (root == nullptr) return root;
            
            // 2. ACTUALIZAR ALTURA
            root->height = 1 + max(height(root->left), height(root->right));
            
            // 3. OBTENER BALANCE
            int balance = getBalance(root);
            
            // 4. REBALANCEAR SI ES NECESARIO
            // Izquierda Izquierda
            if (balance > 1 && getBalance(root->left) >= 0)
                return rightRotate(root);
                
            // Izquierda Derecha
            if (balance > 1 && getBalance(root->left) < 0) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            
            // Derecha Derecha
            if (balance < -1 && getBalance(root->right) <= 0)
                return leftRotate(root);
                
            // Derecha Izquierda
            if (balance < -1 && getBalance(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
            
            return root;
        }

        // BÚSQUEDA CON INFORMACIÓN DE FRECUENCIA
        Node* searchRec(Node* node, int value) {
            if (node == nullptr || node->data == value)
                return node;
            
            if (value < node->data)
                return searchRec(node->left, value);
            else
                return searchRec(node->right, value);
        }

        // RECORRIDOS ÚTILES PARA DEBUGGING Y ANÁLISIS
        void inorderRec(Node* node) {
            if (node != nullptr) {
                inorderRec(node->left);
                cout << node->data;
                if (node->frequency > 1) cout << "(" << node->frequency << ")";
                cout << " ";
                inorderRec(node->right);
            }
        }

        void preorderRec(Node* node) {
            if (node != nullptr) {
                cout << node->data;
                if (node->frequency > 1) cout << "(" << node->frequency << ")";
                cout << " ";
                preorderRec(node->left);
                preorderRec(node->right);
            }
        }

        // ¿POR QUÉ nivel por nivel? Útil para visualizar estructura balanceada
        void printLevelOrder(Node* root) {
            if (!root) return;
            
            queue<Node*> q;
            q.push(root);
            
            while (!q.empty()) {
                int levelSize = q.size();
                for (int i = 0; i < levelSize; i++) {
                    Node* current = q.front();
                    q.pop();
                    
                    cout << current->data;
                    if (current->frequency > 1) cout << "(" << current->frequency << ")";
                    cout << " ";
                    
                    if (current->left) q.push(current->left);
                    if (current->right) q.push(current->right);
                }
                cout << endl;
            }
        }

        // VALIDACIÓN DE PROPIEDADES AVL
        bool isBalancedRec(Node* node) {
            if (node == nullptr) return true;
            
            int balance = getBalance(node);
            return (abs(balance) <= 1) && 
                   isBalancedRec(node->left) && 
                   isBalancedRec(node->right);
        }

        // ANÁLISIS ESTADÍSTICO DEL ÁRBOL
        int totalNodesRec(Node* node) {
            if (node == nullptr) return 0;
            return 1 + totalNodesRec(node->left) + totalNodesRec(node->right);
        }

        int totalElementsRec(Node* node) {
            if (node == nullptr) return 0;
            return node->frequency + 
                   totalElementsRec(node->left) + 
                   totalElementsRec(node->right);
        }

        // FUNCIÓN PARA OBTENER K-ÉSIMO MENOR (ÚTIL EN ENTREVISTAS)
        void kthSmallestRec(Node* node, int& k, int& result) {
            if (node == nullptr || k <= 0) return;
            
            kthSmallestRec(node->left, k, result);
            
            if (k > 0) {
                if (k <= node->frequency) {
                    result = node->data;
                    k = 0; // Encontrado
                } else {
                    k -= node->frequency;
                }
            }
            
            if (k > 0) kthSmallestRec(node->right, k, result);
        }

        // RANGO DE BÚSQUEDA (ÚTIL PARA CONSULTAS DE RANGO)
        void rangeSearchRec(Node* node, int min, int max, vector<int>& result) {
            if (node == nullptr) return;
            
            if (node->data > min)
                rangeSearchRec(node->left, min, max, result);
            
            if (node->data >= min && node->data <= max) {
                for (int i = 0; i < node->frequency; i++) {
                    result.push_back(node->data);
                }
            }
            
            if (node->data < max)
                rangeSearchRec(node->right, min, max, result);
        }

        // VISUALIZACIÓN DEL ÁRBOL (DEBUGGING)
        void printTreeRec(Node* node, string prefix = "", bool isLast = true) {
            if (node == nullptr) return;
            
            cout << prefix;
            cout << (isLast ? "└── " : "├── ");
            cout << node->data;
            if (node->frequency > 1) cout << "(" << node->frequency << ")";
            cout << " [h:" << node->height << ", b:" << getBalance(node) << "]" << endl;
            
            if (node->left || node->right) {
                if (node->right) {
                    printTreeRec(node->right, prefix + (isLast ? "    " : "│   "), !node->left);
                }
                if (node->left) {
                    printTreeRec(node->left, prefix + (isLast ? "    " : "│   "), true);
                }
            }
        }

        // CONVERSIÓN A ARRAY ORDENADO
        void toSortedArrayRec(Node* node, vector<pair<int, int>>& result) {
            if (node == nullptr) return;
            
            toSortedArrayRec(node->left, result);
            result.push_back({node->data, node->frequency});
            toSortedArrayRec(node->right, result);
        }

        // LIMPIEZA DE MEMORIA
        void destroyTree(Node* node) {
            if (node == nullptr) return;
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    public:
        AVLTree() : root(nullptr) {} // Constructor con inicialización de la raíz
        
        // Destructor para liberar memoria
        ~AVLTree() {
            destroyTree(root);
        }

        // =============================================================================
        // 2. OPERACIONES BÁSICAS DE INSERCIÓN, ELIMINACIÓN Y BÚSQUEDA
        // =============================================================================

        void insert(int value) {
            root = insertRec(root, value);
        }

        void remove(int value) {
            root = deleteRec(root, value);
        }

        bool search(int value) {
            return searchRec(root, value) != nullptr;
        }

        int getFrequency(int value) {
            Node* node = searchRec(root, value);
            return node ? node->frequency : 0;
        }

        // =============================================================================
        // 3. RECORRIDOS Y VISUALIZACIÓN
        // =============================================================================

        void inorder() {
            cout << "Inorder: ";
            inorderRec(root);
            cout << endl;
        }

        void preorder() {
            cout << "Preorder: ";
            preorderRec(root);
            cout << endl;
        }

        void levelOrder() {
            cout << "Level order:" << endl;
            printLevelOrder(root);
        }

        void printTree() {
            cout << "Estructura del árbol AVL:" << endl;
            if (root == nullptr) {
                cout << "Árbol vacío" << endl;
            } else {
                printTreeRec(root);
            }
        }

        // =============================================================================
        // 4. ANÁLISIS Y PROPIEDADES DEL ÁRBOL
        // =============================================================================

        int getHeight() {
            return height(root);
        }

        bool isBalanced() {
            return isBalancedRec(root);
        }

        int totalNodes() {
            return totalNodesRec(root);
        }

        int totalElements() {
            return totalElementsRec(root);
        }

        // =============================================================================
        // 5. OPERACIONES AVANZADAS ÚTILES EN ENTREVISTAS
        // =============================================================================

        // ¿POR QUÉ k-ésimo menor? Pregunta común: encontrar el k-ésimo elemento más pequeño
        int kthSmallest(int k) {
            int result = -1;
            int kCopy = k;
            kthSmallestRec(root, kCopy, result);
            return result;
        }

        // ¿POR QUÉ búsqueda por rango? Útil para consultas de bases de datos y filtros
        vector<int> rangeSearch(int min, int max) {
            vector<int> result;
            rangeSearchRec(root, min, max, result);
            return result;
        }

        // ¿POR QUÉ conversión a array? Facilita ordenamiento y análisis
        vector<pair<int, int>> toSortedArray() {
            vector<pair<int, int>> result;
            toSortedArrayRec(root, result);
            return result;
        }

        // ¿POR QUÉ encontrar predecesores/sucesores? Útil para navegación secuencial
        int findPredecessor(int value) {
            Node* current = root;
            int predecessor = -1;
            
            while (current != nullptr) {
                if (current->data < value) {
                    predecessor = current->data;
                    current = current->right;
                } else {
                    current = current->left;
                }
            }
            return predecessor;
        }

        int findSuccessor(int value) {
            Node* current = root;
            int successor = -1;
            
            while (current != nullptr) {
                if (current->data > value) {
                    successor = current->data;
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return successor;
        }

        // =============================================================================
        // 6. ESTADÍSTICAS Y MÉTRICAS DEL ÁRBOL
        // =============================================================================

        void printStatistics() {
            cout << "\n=== ESTADÍSTICAS DEL ÁRBOL AVL ===" << endl;
            cout << "Altura: " << getHeight() << endl;
            cout << "Nodos únicos: " << totalNodes() << endl;
            cout << "Total elementos: " << totalElements() << endl;
            cout << "¿Está balanceado?: " << (isBalanced() ? "Sí" : "No") << endl;
            
            if (root) {
                cout << "Factor de balance de la raíz: " << getBalance(root) << endl;
                cout << "Valor raíz: " << root->data;
                if (root->frequency > 1) cout << " (frecuencia: " << root->frequency << ")";
                cout << endl;
            }
        }

        // =============================================================================
        // 7. OPERACIONES DE CONJUNTO (ÚTILES PARA PROBLEMAS ALGORÍTMICOS)
        // =============================================================================

        // ¿POR QUÉ fusión de árboles? Combinar datasets manteniendo balance
        void merge(AVLTree& other) {
            vector<pair<int, int>> otherElements = other.toSortedArray();
            for (auto& pair : otherElements) {
                for (int i = 0; i < pair.second; i++) {
                    insert(pair.first);
                }
            }
        }

        // ¿POR QUÉ intersección? Encontrar elementos comunes entre datasets
        AVLTree intersection(AVLTree& other) {
            AVLTree result;
            vector<pair<int, int>> thisElements = toSortedArray();
            
            for (auto& pair : thisElements) {
                int otherFreq = other.getFrequency(pair.first);
                if (otherFreq > 0) {
                    int commonFreq = min(pair.second, otherFreq);
                    for (int i = 0; i < commonFreq; i++) {
                        result.insert(pair.first);
                    }
                }
            }
            return result;
        }

        // =============================================================================
        // 8. VALIDACIÓN Y TESTING
        // =============================================================================

        bool isEmpty() {
            return root == nullptr;
        }

        // ¿POR QUÉ validar BST? Verificar que las propiedades se mantienen después de operaciones
        bool isValidBST() {
            return isValidBSTRec(root, LLONG_MIN, LLONG_MAX);
        }

    private:
        bool isValidBSTRec(Node* node, long long minVal, long long maxVal) {
            if (node == nullptr) return true;
            
            if (node->data <= minVal || node->data >= maxVal) return false;
            
            return isValidBSTRec(node->left, minVal, node->data) &&
                   isValidBSTRec(node->right, node->data, maxVal);
        }
};

// =============================================================================
// 9. FUNCIONES DE DEMOSTRACIÓN Y CASOS DE USO PRÁCTICOS
// =============================================================================

void demoBasicOperations() {
    cout << "\n🌳 DEMO: Operaciones Básicas AVL" << endl;
    cout << "================================" << endl;
    
    AVLTree avl;
    
    // Inserción de datos que causarían desbalance en BST normal
    vector<int> values = {10, 20, 30, 40, 50, 25, 35, 45};
    cout << "Insertando secuencia que causaría desbalance: ";
    for (int val : values) {
        cout << val << " ";
        avl.insert(val);
    }
    cout << endl;
    
    cout << "\n📊 Estado después de inserciones:" << endl;
    avl.printStatistics();
    
    cout << "\n🔍 Recorridos:" << endl;
    avl.inorder();
    avl.preorder();
    
    cout << "\n🏗️ Estructura visual:" << endl;
    avl.printTree();
}

void demoDuplicates() {
    cout << "\n🔄 DEMO: Manejo de Duplicados" << endl;
    cout << "=============================" << endl;
    
    AVLTree avl;
    vector<int> valuesWithDups = {50, 30, 70, 30, 50, 80, 30, 20, 50};
    
    cout << "Insertando con duplicados: ";
    for (int val : valuesWithDups) {
        cout << val << " ";
        avl.insert(val);
    }
    cout << endl;
    
    cout << "\n📈 Frecuencias:" << endl;
    for (int val : {20, 30, 50, 70, 80}) {
        int freq = avl.getFrequency(val);
        if (freq > 0) {
            cout << "  " << val << ": " << freq << " veces" << endl;
        }
    }
    
    cout << "\n📊 Comparación de conteos:" << endl;
    cout << "Nodos únicos: " << avl.totalNodes() << endl;
    cout << "Total elementos: " << avl.totalElements() << endl;
    
    avl.inorder();
}

void demoAdvancedQueries() {
    cout << "\n🔍 DEMO: Consultas Avanzadas" << endl;
    cout << "============================" << endl;
    
    AVLTree avl;
    vector<int> data = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    for (int val : data) {
        avl.insert(val);
    }
    
    cout << "Datos insertados: ";
    for (int val : data) cout << val << " ";
    cout << endl;
    
    avl.inorder();
    
    cout << "\n🎯 Consultas k-ésimo elemento:" << endl;
    for (int k = 1; k <= 5; k++) {
        cout << k << "-ésimo menor: " << avl.kthSmallest(k) << endl;
    }
    
    cout << "\n📊 Búsquedas por rango:" << endl;
    vector<int> range25_65 = avl.rangeSearch(25, 65);
    cout << "Elementos entre 25 y 65: ";
    for (int val : range25_65) cout << val << " ";
    cout << endl;
    
    cout << "\n🔄 Predecesores y sucesores:" << endl;
    int target = 45;
    cout << "Predecesor de " << target << ": " << avl.findPredecessor(target) << endl;
    cout << "Sucesor de " << target << ": " << avl.findSuccessor(target) << endl;
}

void demoSetOperations() {
    cout << "\n🔗 DEMO: Operaciones de Conjunto" << endl;
    cout << "================================" << endl;
    
    AVLTree avl1, avl2;
    
    // Primer conjunto
    vector<int> set1 = {10, 20, 30, 40, 50};
    cout << "Conjunto 1: ";
    for (int val : set1) {
        cout << val << " ";
        avl1.insert(val);
    }
    cout << endl;
    
    // Segundo conjunto con algunos elementos comunes
    vector<int> set2 = {30, 40, 50, 60, 70};
    cout << "Conjunto 2: ";
    for (int val : set2) {
        cout << val << " ";
        avl2.insert(val);
    }
    cout << endl;
    
    // Intersección
    AVLTree intersection = avl1.intersection(avl2);
    cout << "\nIntersección: ";
    intersection.inorder();
    
    // Fusión
    avl1.merge(avl2);
    cout << "Unión (avl1 después de merge): ";
    avl1.inorder();
}

void demoPerformanceComparison() {
    cout << "\n⚡ DEMO: Comparación de Performance" << endl;
    cout << "===================================" << endl;
    
    AVLTree avl;
    
    cout << "Insertando secuencia ordenada (peor caso para BST normal):" << endl;
    for (int i = 1; i <= 15; i++) {
        avl.insert(i);
    }
    
    cout << "Altura resultante: " << avl.getHeight() << endl;
    cout << "¿Permanece balanceado?: " << (avl.isBalanced() ? "Sí" : "No") << endl;
    cout << "Altura teórica mínima: " << (int)log2(15) + 1 << endl;
    cout << "Eficiencia mantenida: O(log n) garantizado" << endl;
    
    cout << "\n🏗️ Estructura final:" << endl;
    avl.printTree();
}

void interactiveMenu() {
    AVLTree avl;
    int choice, value;
    
    do {
        cout << "\n🌳 MENÚ INTERACTIVO AVL" << endl;
        cout << "======================" << endl;
        cout << "1. Insertar elemento" << endl;
        cout << "2. Eliminar elemento" << endl;
        cout << "3. Buscar elemento" << endl;
        cout << "4. Mostrar recorridos" << endl;
        cout << "5. Mostrar estructura" << endl;
        cout << "6. Estadísticas" << endl;
        cout << "7. K-ésimo menor" << endl;
        cout << "8. Búsqueda por rango" << endl;
        cout << "9. Demos automáticos" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Valor a insertar: ";
                cin >> value;
                avl.insert(value);
                cout << "✅ Insertado: " << value << endl;
                break;
                
            case 2:
                cout << "Valor a eliminar: ";
                cin >> value;
                if (avl.search(value)) {
                    avl.remove(value);
                    cout << "✅ Eliminado: " << value << endl;
                } else {
                    cout << "❌ Elemento no encontrado" << endl;
                }
                break;
                
            case 3:
                cout << "Valor a buscar: ";
                cin >> value;
                if (avl.search(value)) {
                    cout << "✅ Encontrado con frecuencia: " << avl.getFrequency(value) << endl;
                } else {
                    cout << "❌ No encontrado" << endl;
                }
                break;
                
            case 4:
                avl.inorder();
                avl.preorder();
                avl.levelOrder();
                break;
                
            case 5:
                avl.printTree();
                break;
                
            case 6:
                avl.printStatistics();
                break;
                
            case 7:
                cout << "Ingrese k: ";
                cin >> value;
                {
                    int result = avl.kthSmallest(value);
                    if (result != -1) {
                        cout << value << "-ésimo menor: " << result << endl;
                    } else {
                        cout << "❌ No existe el " << value << "-ésimo elemento" << endl;
                    }
                }
                break;
                
            case 8:
                {
                    int min, max;
                    cout << "Rango mínimo: ";
                    cin >> min;
                    cout << "Rango máximo: ";
                    cin >> max;
                    vector<int> range = avl.rangeSearch(min, max);
                    cout << "Elementos en rango [" << min << ", " << max << "]: ";
                    for (int val : range) cout << val << " ";
                    cout << endl;
                }
                break;
                
            case 9:
                demoBasicOperations();
                demoDuplicates();
                demoAdvancedQueries();
                demoSetOperations();
                demoPerformanceComparison();
                break;
        }
        
    } while (choice != 0);
}

// =============================================================================
// 10. FUNCIÓN PRINCIPAL Y CASOS DE PRUEBA
// =============================================================================

int main() {
    // Ejecutar demos automáticos
    demoBasicOperations();
    demoDuplicates();
    demoAdvancedQueries();
    demoSetOperations();
    demoPerformanceComparison();
    
    // Menú interactivo
    char continuar;
    cout << "\n¿Desea usar el menú interactivo? (s/n): ";
    cin >> continuar;
    
    if (continuar == 's' || continuar == 'S') {
        interactiveMenu();
    }
    
    return 0;
}