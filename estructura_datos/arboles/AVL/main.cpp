#include <iostream>

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
            else
                return node; // Valores duplicados no se permiten

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


    public:
        AVLTree() : root(nullptr) {} // Constructor con inicialización de la raíz

        void insert(int value) {
            root = insertRec(root, value);
        }

        void printTree() {
            cout << "Estructura del árbol AVL:" << endl;
            if (root == nullptr) {
                cout << "Árbol vacío" << endl;
            } else {
                printTreeRec(root);
            }
        }
};

int main(){
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    avl.printTree();

    return 0;
}