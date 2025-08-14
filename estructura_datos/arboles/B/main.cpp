// =============================================================================
// ÁRBOL B
// =============================================================================
// - Estructura de datos no lineal y dinámica.
// - Balanceo automático: Los árboles B se autoajustan para mantener su altura balanceada.
// - El balanceo NO se hace mediante rotaciones, sino mediante divisiones (split) y fusiones (merge) de nodos.
// - Todos los nodos internos pueden tener múltiples claves y múltiples hijos.
// - Garantizan búsqueda, inserción y eliminación en tiempo O(log n).
// - Muy usados en bases de datos y sistemas de archivos, donde el acceso a disco debe minimizarse.

#include <vector>
using namespace std;

class BTree {
    private:
        struct Node {
            vector<int> keys;        // Claves del nodo
            vector<Node*> children;  // Punteros a los hijos
            bool leaf;
            Node(bool isLeaf) : leaf(isLeaf) {}
        };

        Node *root; // Raíz del árbol
        int t;     // Grado mínimo

    void splitChild(Node * parent, int index, Node* child) {
        Node* newNode = new Node(child->leaf); // Crear nuevo nodo con la propiedad "leaf" del hijo
        
        // Mover las t-1 claves más grandes al nuevo nodo
        for(int j = 0; j < t-1; ++j){
            newNode->keys.push_back(child->keys[j+t]);
        }

        // Si no es hoja, mover los hijos correspondientes
        if(!child->leaf){
            for(int j = 0; j < t; ++j){
                newNode->children.push_back(child->children[j+t]);
            }
        }

        // Insertar nueva clave en el padre
        parent->keys.insert(parent->keys.begin() + index, child->keys[t-1]);
        parent->children.insert(parent->children.begin() + index + 1, newNode);
    }
    void insertNonFull(Node* node, int key) {
        int i = node->keys.size() - 1;
        if (node->leaf) {
            // Insert key into the correct position in the node
            node->keys.push_back(0); // Add space for new key
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            // Find the child to recurse into
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }
            i++;
            // If the child is full, split it
            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    public:
        BTree(int degree) : t(degree), root(nullptr) {}
        void insert(int key) {
            if (!root) {
                root = new Node(true);
                root->keys.push_back(key);
                return;
            } 
            if (root->keys.size() == 2 * t - 1) {
                Node* newRoot = new Node(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0, root);
                root = newRoot;
            }
            insertNonFull(root, key);
            
        }
};
