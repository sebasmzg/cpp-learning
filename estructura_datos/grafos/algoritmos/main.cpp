#include <iostream>
#include <vector>
using namespace std;

// DFS
struct Nodo {
    int valor;
    vector<Nodo*> hijos;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(int v) : valor(v), izquierda(nullptr), derecha(nullptr) {}
};
/*
*@param raiz: nodo raíz desde donde se inicia la búsqueda
*@param valor: valor a buscar en el grafo
*/
Nodo* dfs(Nodo* raiz, int value){
    if(raiz == nullptr) return nullptr; // Caso base: si el nodo es nulo, retornar nulo

    
    if(raiz->valor == value){
        cout << "Valor " << value << " encontrado." << endl;
        return raiz;
    }
    
    // SI ES BINARIO:
    /*
    Nodo* resultadoIzq = nullptr;
    Nodo* izquierda = resultadoIzq = dfs(raiz->izquierda, value);
    if(izquierda != nullptr) return resultadoIzq;

    Nodo* resultadoDer = nullptr;
    Nodo* derecha = resultadoDer = dfs(raiz->derecha, value);
    if(derecha != nullptr) return resultadoDer;

    return nullptr;
    */
   // Con lista de nodos que son sus hijos
   
    for(size_t i = 0; i < raiz->hijos.size(); ++i){
        Nodo* resultado = dfs(raiz->hijos[i], value);
        if(resultado != nullptr){
            cout << "Valor " << value << " encontrado en hijo " << raiz->hijos[i]->valor << endl;
            return resultado;
        } else {
            cout << "Valor " << value << " no encontrado en hijo " << raiz->hijos[i]->valor << endl;
        }
    }
    return nullptr; // Si no se encuentra el valor
    
}

int main(){
    // grafo binario 
    // Nodo* raizBinaria = new Nodo(1);
    // raizBinaria->izquierda = new Nodo(2);
    // raizBinaria->derecha = new Nodo(3);
    // raizBinaria->izquierda->izquierda = new Nodo(4);
    // raizBinaria->izquierda->derecha = new Nodo(5);
    // raizBinaria->derecha->izquierda = new Nodo(6);
    // raizBinaria->derecha->derecha = new Nodo(7);

    // grafo con hijos
    Nodo* raiz = new Nodo(1);
    raiz->hijos.push_back(new Nodo(2));
    raiz->hijos.push_back(new Nodo(3));
    raiz->hijos[0]->hijos.push_back(new Nodo(4));
    raiz->hijos[0]->hijos.push_back(new Nodo(5));
    raiz->hijos[1]->hijos.push_back(new Nodo(6));
    raiz->hijos[1]->hijos.push_back(new Nodo(7));

    // Realizar búsqueda DFS
    int valorBuscado = 5;
    // Nodo* resultadoBinario = dfs(raizBinaria, valorBuscado);
    Nodo* resultadoHijos = dfs(raiz, valorBuscado);

    if(resultadoHijos != nullptr){
        cout << "Resultado de la búsqueda en grafo con hijos: " << resultadoHijos->valor << endl;
    } else {
        cout << "Valor " << valorBuscado << " no encontrado en el grafo con hijos." << endl;
    }

    // if(resultadoBinario != nullptr){
    //     cout << "Resultado de la búsqueda en grafo binario: " << resultadoBinario->valor << endl;
    // } else {
    //     cout << "Valor " << valorBuscado << " no encontrado en el grafo binario." << endl;
    // }

    return 0;
}