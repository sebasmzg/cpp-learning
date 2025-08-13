// Estructura de datos no lineales
// dinámicas
// Longitud de camino es el número de nodos - 1
// altura: desde la hoja hacia arriba

// preorden: raiz, izquierdo, derecho
// inorden: izquierdo, raiz, derecho
// postOrden: izquierdo, derecho, raiz

#include <iostream>
using namespace std;

struct Nodo
{
    int dato;
    Nodo* der;
    Nodo* izq;
};

Nodo* arbol = nullptr;

void menu();
Nodo* crearNodo(int);
void insertarNodo(Nodo*&, int);
void mostrarArbol(Nodo*, int);
bool buscarNodo(Nodo*, int);
void preOrden(Nodo*);
void inOrden(Nodo*);
void postOrden(Nodo*);

void menu()
{
    int dato, opcion, contador = 0;
    do
    {
        cout<< "\t.:MENU:." << endl;
        cout << "1. Insertar un nuevo nodo." << endl;
        cout << "2. Mostrar arbol completo." << endl;
        cout << "3. Buscar nodo en arbol." << endl;
        cout << "4. Recorrer arbol en preOrden." << endl;
        cout << "5. Recorrer arbol en inOrden." << endl;
        cout << "6. Recorrer arbol en postOrden." << endl;
        cout << "7. Salir." << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: cout << "Ingrese un numero: ";
            cin >> dato;
            insertarNodo(arbol, dato);
            cout << "\n";
            system("pause");
            break;
        case 2: cout << "\nMostrando arbol completo.\n\n" << endl;
            mostrarArbol(arbol, contador);
            cout << "\n";
            system("pause");
            break;
        case 3: cout << "\nDigite elemento a buscar en arbol." << endl;
            cin >> dato;
            if (buscarNodo(arbol, dato) == true)
            {
                cout << "\nEl elemento "<< dato <<" ha sido encontradoen el arbol." << endl;
            } else
            {
                cout << "\nElemento " << dato << " no encontrado." << endl;
            }
            cout << "\n";
            system("pause");
            break;
        case 4: cout << "\nRecorrido en preOrden: " << endl;
            preOrden(arbol);
            cout << "\n\n";
            system("pause");
            break;
        case 5: cout << "\nRecorrido inOrden." << endl;
            inOrden(arbol);
            cout << "\n\n";
            system("pause");
            break;
        case 6: cout << "\nRecorrido postOrden." << endl;
            postOrden(arbol);
            cout << "\n\n";
            system("pause");
            break;
        }
        system("cls");
    } while (opcion != 7);
}

// Insertar nodo en un árbol binario de búsqueda

// 1. creaer nodo
Nodo* crearNodo(int dato)
{
    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->der = nullptr;
    return nuevo_nodo;
}
// 2. insertar
void insertarNodo(Nodo*& arbol, int dato)
{
    if (arbol == nullptr) // si el arbol está vacío
    {
        Nodo* nuevo_nodo = crearNodo(dato); // crear nodo raiz
        arbol = nuevo_nodo;
    } else
    {  // si tiene un nodo o más
        int valorRaiz = arbol->dato; // obtener valor de raiz
        if (dato < valorRaiz)
        { // si el dato es menor que la raiz
            insertarNodo(arbol->izq, dato); // insertar a la izquierda
        } else
        { // si es mayor
            insertarNodo(arbol->der, dato); // insertar a la derecha
        }
    }
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

// recorrido profundidad preorden raiz, izquierda, derecha
void preOrden(Nodo* arbol)
{
    if (arbol == nullptr) return;
    cout << arbol->dato << " - "; // raiz
    preOrden(arbol->izq); // izquierdo
    preOrden(arbol->der); // derecho
}

// recorrido inOrden izquierda, raiz, derecha
void inOrden(Nodo* arbol)
{
    if (arbol == nullptr) return;
    inOrden(arbol->izq); // izquierda
    cout << arbol->dato << " - "; // raiz
    inOrden(arbol->der); // derecha

}

void postOrden(Nodo* arbol)
{
    if (arbol == nullptr) return;
    postOrden(arbol->izq);
    postOrden(arbol->der);
    cout << arbol->dato << " - ";
}

int main(){
    menu();
    return 0;
}