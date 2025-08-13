#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> 

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(int v) : dato(v), siguiente(nullptr), anterior(nullptr) {}
};
// ======================= INSERCIÓN =======================
Nodo* insertarInicio(Nodo* cabeza, int dato){
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
    if (cabeza) cabeza->anterior = nuevo; // Si la lista no está vacía, actualizar el anterior de la cabeza
    nuevo->anterior = nullptr; // El nuevo nodo no tiene anterior
    return nuevo; // Devolver la nueva cabeza de la lista
}

Nodo* insertarFinal(Nodo* cabeza, int dato){
    Nodo* nuevo = new Nodo(dato);
    if (!cabeza) {
        nuevo->anterior = nullptr; // Si la lista está vacía, el nuevo nodo es la cabeza
        return nuevo; // Devolver el nuevo nodo como cabeza
    }
    Nodo* temp = cabeza;     // Si la lista no está vacía, buscar el final
    while (temp->siguiente) { temp = temp->siguiente; }
    temp->siguiente = nuevo; // Enlazar el último nodo con el nuevo
    nuevo->anterior = temp;  // Enlazar el nuevo nodo con el anterior
    return cabeza; // Devolver la cabeza de la lista
}

Nodo* insertarPosicion(Nodo*& cabeza, int dato, int posicion){ //*& significa que cabeza es una referencia
    if(posicion < 0) return cabeza; // Si la posición es negativa, no hacer nada
    if(posicion == 0) return insertarInicio(cabeza, dato); // Si la posición es 0, insertar al inicio
    if(!cabeza) return insertarInicio(cabeza, dato); // Si la lista está vacía, insertar al inicio
    Nodo* nuevo = new Nodo(dato);
    Nodo* temp = cabeza;
    for(int i = 0; i < posicion -1 && temp; ++i){
        temp = temp->siguiente; // Avanzar al nodo anterior a la posición deseada
    }
    if(!temp || !temp->siguiente) {
        return insertarFinal(cabeza, dato); // Si llegamos al final, insertar al final
    }
    nuevo->siguiente = temp->siguiente; // Enlazar el nuevo nodo con el siguiente
    nuevo->anterior = temp; // Enlazar el nuevo nodo con el anterior
    temp->siguiente->anterior = nuevo; // Actualizar el anterior del siguiente nodo
    temp->siguiente = nuevo; // Enlazar el nodo anterior con el nuevo nodo
    return cabeza; // Devolver la cabeza de la lista
}

void insertarDespuesDe(Nodo* nodo, int dato) {
    if(!nodo) return; // Si el nodo es nulo, no hacer nada
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo->siguiente; // Enlazar el nuevo nodo con el siguiente
    nuevo->anterior = nodo; // Enlazar el nuevo nodo con el nodo actual
    if(nodo->siguiente){
        nodo->siguiente->anterior = nuevo; // Actualizar el anterior del siguiente nodo
    }
    nodo->siguiente = nuevo; // Enlazar el nodo actual con el nuevo nodo
}

void insertarAntesDe(Nodo* cabeza,Nodo* nodo, int dato) {
    if(!cabeza || !nodo) return; // Si el nodo es nulo, no hacer nada
    if(nodo == cabeza) { // Si el nodo es la cabeza, insertar al inicio
        cabeza = insertarInicio(cabeza, dato);
        return;
    }
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo; // Enlazar el nuevo nodo con el nodo actual
    nuevo->anterior = nodo->anterior; // Enlazar el nuevo nodo con el anterior
    if(nodo->anterior){
        nodo->anterior->siguiente = nuevo; // Actualizar el siguiente del anterior nodo
    }
    nodo->anterior = nuevo; // Enlazar el nodo actual con el nuevo nodo
}

// inserta un nodo en orden ascendente
Nodo* insertarOrdenado(Nodo* cabeza, int dato){ // suponiendo que la lista está ordenada
    Nodo* nuevo = new Nodo(dato);
    if(!cabeza || cabeza->dato >= dato){
        if(cabeza){
            cabeza->anterior = nuevo; // Si la lista no está vacía, actualizar el anterior de la cabeza
        }
        nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
        return nuevo; // Devolver el nuevo nodo como cabeza
    }
    Nodo* temp = cabeza;
    while(temp->siguiente && temp->siguiente->dato < dato){
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    nuevo->siguiente = temp->siguiente; // Enlazar el nuevo nodo con el siguiente
    nuevo->anterior = temp; // Enlazar el nuevo nodo con el nodo actual
    if(temp->siguiente){
        temp->siguiente->anterior = nuevo; // Actualizar el anterior del siguiente nodo
    }
    temp->siguiente = nuevo; // Enlazar el nodo actual con el nuevo nodo
    return cabeza; // Devolver la cabeza de la lista
}

Nodo* buscar(Nodo* cabeza, int valor) { // retorna un nodo con el dato dado, si no lo encuentra retorna nullptr
    Nodo* temp = cabeza;
    while (temp && temp->dato != valor) {
        temp = temp->siguiente;
    }
    return temp;
}

Nodo* buscarDesdeElFinal(Nodo* cabeza, int valor) {
    if (!cabeza) return nullptr;
    Nodo* temp = cabeza;
    while (temp->siguiente) {
        temp = temp->siguiente;
    }
    while (temp && temp->dato != valor) { // Buscar hacia atrás
        temp = temp->anterior;
    }
    return temp;
}

//retorna index del nodo con el dato dado, si no lo encuentra retorna -1
int obtenerPosicion(Nodo* cabeza, int valor) {
    int posicion = 0;
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->dato == valor) return posicion;
        temp = temp->siguiente; // Avanzar al siguiente nodo
        posicion++; // Incrementar la posición
    }
    return -1; // Si no se encuentra, retornar -1
}

// retorna un vector con todos los nodos que tienen el dato dado
std::vector<Nodo*> buscarTodos(Nodo* cabeza, int valor) {
    std::vector<Nodo*> resultados; // Vector para almacenar todos los nodos encontrados
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->dato == valor) {
            resultados.push_back(temp); // Agregar el nodo encontrado al vector
        }
        temp = temp->siguiente;
    }
    return resultados;
}

Nodo* buscarMinimo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* minimo = cabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp) {
        if (temp->dato < minimo->dato) { // Comparar el dato del nodo actual con el mínimo encontrado
            minimo = temp; // Actualizar el mínimo
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return minimo;
}

Nodo* buscarMaximo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    Nodo* maximo = cabeza;
    Nodo* temp = cabeza->siguiente;
    while (temp) {
        if (temp->dato > maximo->dato) {
            maximo = temp;
        }
        temp = temp->siguiente;
    }
    return maximo;
}
// ======================= ELIMINACIÓN =======================
void eliminarInicio(Nodo*& cabeza) {
    if (!cabeza) return;
    Nodo* temp = cabeza; // Guardar la cabeza actual
    cabeza = cabeza->siguiente; // Actualizar la cabeza a la siguiente
    if (cabeza) {
        cabeza->anterior = nullptr;  // ENLACE BIDIRECCIONAL
    }
    delete temp; // Liberar memoria del nodo eliminado
}

void eliminarFinal(Nodo*& cabeza) {
    if (!cabeza) return;
    if (!cabeza->siguiente) { // Si solo hay un nodo
        delete cabeza;
        cabeza = nullptr;
        return;
    }
    Nodo* temp = cabeza;
    while (temp->siguiente) {
        temp = temp->siguiente;
    }
    // El penúltimo nodo ahora es el último
    temp->anterior->siguiente = nullptr;  // ENLACE BIDIRECCIONAL 
    delete temp;
}

void eliminarValor(Nodo*& cabeza, int valor) {
    if (!cabeza) return;
    Nodo* temp = cabeza;
    while (temp && temp->dato != valor) { // Buscar hasta encontrar el valor
        temp = temp->siguiente; 
    }
    if (!temp) return;  // No encontrado
    if (temp->anterior) {    // Actualizar enlaces
        temp->anterior->siguiente = temp->siguiente; // Si no es la cabeza, actualizar el siguiente del anterior
    } else {
        cabeza = temp->siguiente;  // Era la cabeza
    }
    if (temp->siguiente) {
        temp->siguiente->anterior = temp->anterior;  // ENLACE BIDIRECCIONAL
    }
    delete temp;
}

void eliminarPosicion(Nodo*& cabeza, int posicion) {
    if (!cabeza || posicion < 0) return; 
    if (posicion == 0) {
        eliminarInicio(cabeza); // Si es la cabeza, eliminar el inicio
        return;
    }
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion && temp; ++i) { // Avanzar al nodo en la posición deseada
        temp = temp->siguiente; 
    }
    if (!temp) return;  // Posición inválida
    if (temp->anterior) { // Actualizar enlaces
        temp->anterior->siguiente = temp->siguiente; 
    }
    if (temp->siguiente) {
        temp->siguiente->anterior = temp->anterior;  // ENLACE BIDIRECCIONAL
    }
    delete temp;
}

void eliminarDuplicados(Nodo*& cabeza) {
    if (!cabeza) return;
    std::unordered_set<int> vistos; 
    Nodo* actual = cabeza;
    while (actual) {
        if (vistos.count(actual->dato)) { // si el valor ya fue visto
            // Es duplicado, eliminarlo
            Nodo* temp = actual;
            actual = actual->siguiente; // Avanzar al siguiente nodo
            if (temp->anterior) { // si no es la cabeza, actualizar el anterior del siguiente
                temp->anterior->siguiente = temp->siguiente;
            } else {
                cabeza = temp->siguiente; // Si es la cabeza, actualizar la cabeza
            }           
            if (temp->siguiente) {
                temp->siguiente->anterior = temp->anterior;  // ⭐ ENLACE BIDIRECCIONAL
            }
            delete temp; // Liberar memoria del nodo eliminado
        } else {
            vistos.insert(actual->dato); // Agregar el valor a los vistos
            actual = actual->siguiente; // Avanzar al siguiente nodo
        }
    }
}

void eliminarLista(Nodo*& cabeza) {
    while (cabeza) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    cabeza = nullptr;
}
// ======================= MANIPULACIÓN =======================
Nodo* invertirLista(Nodo*& cabeza) {
    if (!cabeza) return nullptr;   
    Nodo* actual = cabeza;
    Nodo* temp = nullptr;   
    while (actual) {       
        temp = actual->anterior;  // Intercambiar siguiente y anterior
        actual->anterior = actual->siguiente;
        actual->siguiente = temp;                
        temp = actual; // Mover al siguiente nodo (que ahora es el anterior)
        actual = actual->anterior;
    }   
    if (temp) {
        cabeza = temp; // temp apunta al nuevo primer nodo
    }   
    return cabeza;
}

void intercambiarNodos(Nodo*& cabeza, int x, int y) {
    if (x == y) return;  
    Nodo* nodoX = buscar(cabeza, x); 
    Nodo* nodoY = buscar(cabeza, y);  
    if (!nodoX || !nodoY) return;   
    std::swap(nodoX->dato, nodoY->dato); // Intercambiar solo los datos (más simple para listas dobles)
}

int contarNodos(Nodo* cabeza) {
    int contador = 0;
    Nodo* temp = cabeza;
    while (temp) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

Nodo* obtenerNodo(Nodo* cabeza, int posicion) { // Retorna el nodo en la posición dada (0-indexed)
    if (posicion < 0) return nullptr;    
    Nodo* temp = cabeza;
    for (int i = 0; i < posicion && temp; ++i) {
        temp = temp->siguiente; 
    }
    return temp;
}

Nodo* obtenerUltimoNodo(Nodo* cabeza) {
    if (!cabeza) return nullptr;
    while (cabeza->siguiente) {
        cabeza = cabeza->siguiente;
    }
    return cabeza;
}

Nodo* clonarLista(Nodo* cabeza) {
    if (!cabeza) return nullptr;   
    Nodo* nuevaCabeza = new Nodo(cabeza->dato); // Crear el primer nodo de la nueva lista
    Nodo* actualOriginal = cabeza->siguiente; // Nodo actual de la lista original
    Nodo* actualNueva = nuevaCabeza; // Nodo actual de la nueva lista   
    while (actualOriginal) { // mientras haya nodos en la original
        Nodo* nuevoNodo = new Nodo(actualOriginal->dato); // Crear un nuevo nodo con el dato del original
        actualNueva->siguiente = nuevoNodo; // Enlazar el nuevo nodo al final de la nueva lista
        nuevoNodo->anterior = actualNueva;  // ENLACE BIDIRECCIONAL       
        actualNueva = nuevoNodo; // Mover al siguiente nodo de la nueva lista
        actualOriginal = actualOriginal->siguiente; // Mover al siguiente nodo de la lista original
    }    
    return nuevaCabeza;
}
// ======================= ALGORITMOS =======================
// Insertar en lista ordenada desde cualquier dirección
Nodo* insertarOrdenadoBidireccional(Nodo*& cabeza, int dato) {
    if (!cabeza) {
        cabeza = new Nodo(dato);
        return cabeza;
    }    
    Nodo* ultimo = obtenerUltimoNodo(cabeza); // Decidir si buscar desde el inicio o el final  
    if (dato <= cabeza->dato) {        
        return insertarInicio(cabeza, dato); // Insertar al inicio
    } else if (dato >= ultimo->dato) {
        return insertarFinal(cabeza, dato); // Insertar al final
    } else {
        // Decidir dirección de búsqueda
        int longitud = contarNodos(cabeza);
        int posicion = obtenerPosicion(cabeza, dato);   
        if (posicion < longitud / 2) {           
            return insertarOrdenado(cabeza, dato); // Buscar desde el inicio
        } else {   
            Nodo* nuevo = new Nodo(dato);  // Buscar desde el final
            Nodo* temp = ultimo;
            while (temp && temp->dato > dato) { // mientras el dato es menor que el nodo actual
                temp = temp->anterior;
            }
            // Insertar después de temp
            nuevo->siguiente = temp->siguiente; // Enlazar el nuevo nodo con el siguiente
            nuevo->anterior = temp; // Enlazar el nuevo nodo con el nodo actual
            temp->siguiente->anterior = nuevo; // Actualizar el anterior del siguiente nodo
            temp->siguiente = nuevo; // Enlazar el nodo actual con el nuevo nodo           
            return cabeza;
        }
    }
}

void eliminarNodo(Nodo*& cabeza, Nodo* nodo) {
    if (!nodo) return;    
    if (nodo->anterior) {
        nodo->anterior->siguiente = nodo->siguiente; // Si no es la cabeza, actualizar el siguiente del anterior
    } else {
        cabeza = nodo->siguiente; // Si es la cabeza, actualizar la cabeza
    }    
    if (nodo->siguiente) { // Si no es el último, actualizar el anterior del siguiente
        nodo->siguiente->anterior = nodo->anterior; 
    }   
    delete nodo;
}

void eliminarDesdeCualquierDireccion(Nodo*& cabeza, int valor) {
    if (!cabeza) return;   
    Nodo* inicio = cabeza; // Buscar desde ambos extremos
    Nodo* final = obtenerUltimoNodo(cabeza);
    while (inicio && final && inicio != final && inicio->anterior != final) {
        if (inicio->dato == valor) {
            eliminarNodo(cabeza, inicio);
            return;
        }
        if (final->dato == valor) {
            eliminarNodo(cabeza, final);
            return;
        } 
        inicio = inicio->siguiente;
        final = final->anterior;
    }
    if (inicio && inicio->dato == valor) { // Verificar el nodo del medio si existe
        eliminarNodo(cabeza, inicio);
    }
}
// ======================= IMPRIMIR =======================
void printList(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp) {
        std::cout << temp->dato << "<->";
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    std::cout << "nullptr\n\n"; // Nueva línea al final
}

void printListReverse(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    Nodo* temp = cabeza;
    while (temp->siguiente) {
        temp = temp->siguiente;
    }
    std::cout << "Atrás: ";
    while (temp) {
        std::cout << temp->dato << " <-> ";
        temp = temp->anterior;
    }
    std::cout << "nullptr\n";
}

void printListBidirectional(Nodo* cabeza) {
    printList(cabeza);
    printListReverse(cabeza);
    std::cout << std::endl;
}

bool validarIntegridad(Nodo* cabeza) {
    if (!cabeza) return true;
    Nodo* temp = cabeza;
    if (temp->anterior != nullptr) { // Verificar que el primer nodo no tenga anterior
        std::cout << "Error: La cabeza tiene nodo anterior\n";
        return false;
    } 
    while (temp->siguiente) { // Verificar enlaces bidireccionales
        if (temp->siguiente->anterior != temp) {
            std::cout << "Error: Enlaces bidireccionales rotos en nodo " << temp->dato << "\n";
            return false;
        }
        temp = temp->siguiente;
    }
    std::cout << "Integridad de la lista: OK\n";
    return true;
}
// ======================= ALGORITMOS =======================
void moverAlFrente(Nodo*& cabeza, int valor) {
    Nodo* nodo = buscar(cabeza, valor);
    if (!nodo || nodo == cabeza) return; // Si no se encuentra o ya es la cabeza, no hacer nada    
    if (nodo->anterior) { // Desconectar el nodo
        nodo->anterior->siguiente = nodo->siguiente; // Actualizar el siguiente del anterior
    }
    if (nodo->siguiente) {
        nodo->siguiente->anterior = nodo->anterior; // Actualizar el anterior del siguiente
    } // Insertar al inicio
    nodo->siguiente = cabeza;  // El nodo ahora apunta a la antigua cabeza 
    nodo->anterior = nullptr; // No tiene anterior porque es la nueva cabeza
    if (cabeza) cabeza->anterior = nodo; // Actualizar el anterior de la antigua cabeza
    cabeza = nodo; // Actualizar la cabeza de la lista
}

void moverAlFinal(Nodo*& cabeza, int valor) {
    Nodo* nodo = buscar(cabeza, valor);
    if (!nodo || !cabeza || nodo->siguiente == nullptr) return; // Si no se encuentra, ya es el último o la lista está vacía, no hacer nada
    if (nodo->anterior) { // Desconectar el nodo
        nodo->anterior->siguiente = nodo->siguiente; // Actualizar el siguiente del anterior
    } else {
        cabeza = nodo->siguiente; // Si es la cabeza, actualizar la cabeza
    }
    if (nodo->siguiente) {
        nodo->siguiente->anterior = nodo->anterior; // Actualizar el anterior del siguiente
    }  // Insertar al final
    Nodo* ultimo = obtenerUltimoNodo(cabeza); // Obtener el último nodo
    nodo->siguiente = nullptr; // El nuevo último nodo no tiene siguiente
    nodo->anterior = ultimo; // El nuevo último nodo apunta al antiguo último nodo
    if (ultimo) {
        ultimo->siguiente = nodo; // Actualizar el siguiente del antiguo último nodo
    } else {
        cabeza = nodo; // Si la lista estaba vacía, actualizar la cabeza
    }
}

void moverAlMedio(Nodo*& cabeza, int valor) {
    Nodo* nodo = buscar(cabeza, valor);
    if (!nodo || !cabeza || nodo == cabeza) return; // Si no se encuentra, ya es la cabeza o la lista está vacía, no hacer nada  
    if (nodo->anterior) { // Desconectar el nodo
        nodo->anterior->siguiente = nodo->siguiente; // Actualizar el siguiente del anterior
    }
    if (nodo->siguiente) {
        nodo->siguiente->anterior = nodo->anterior; // Actualizar el anterior del siguiente
    }
    Nodo* temp = cabeza; // Insertar al medio
    int longitud = contarNodos(cabeza);
    int posicionMedio = longitud / 2;
    for (int i = 0; i < posicionMedio - 1 && temp; ++i) {
        temp = temp->siguiente; // Avanzar al nodo en la posición media
    }
    nodo->siguiente = temp ? temp->siguiente : nullptr; // Enlazar el nuevo nodo con el siguiente
    nodo->anterior = temp; // Enlazar el nuevo nodo con el nodo actual
    if (temp) {
        if (temp->siguiente) {
            temp->siguiente->anterior = nodo; // Actualizar el anterior del siguiente nodo
        }
        temp->siguiente = nodo; // Enlazar el nodo actual con el nuevo nodo
    } else {
        cabeza = nodo; // Si la lista estaba vacía, actualizar la cabeza
    }
}

void sumarNumeros(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    int suma = 0;
    Nodo* temp = cabeza;
    while (temp) {
        suma += temp->dato; // Sumar el dato del nodo actual
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    std::cout << "Suma de los números en la lista: " << suma << "\n";
}

void contarParesEImpares(Nodo* cabeza) {
    if (!cabeza) {
        std::cout << "Lista vacía\n";
        return;
    }
    int pares = 0;
    int impares = 0;
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->dato % 2 == 0) {
            pares++;
        } else {
            impares++;
        }
        temp = temp->siguiente;
    }
    std::cout << "Números pares: " << pares << "\n";
    std::cout << "Números impares: " << impares << "\n";
}

Nodo* multiplicarListaPorNumero(Nodo* cabeza, int num) { // Multiplica un número representado como lista por un entero, ej: (3 -> 4 -> 2) * 3 = (1 -> 0 -> 2 -> 6) 
    if (!cabeza || num == 0) {
        Nodo* cero = new Nodo(0);
        return cero;
    }
    Nodo* fin = obtenerUltimoNodo(cabeza);
    Nodo* resultado = nullptr;
    int carry = 0;
    while (fin || carry) {
        int producto = carry;
        if (fin) {
            producto += fin->dato * num;
            fin = fin->anterior;
        }      
        carry = producto / 10; // Calcular el carry para la siguiente iteración 
        Nodo* nuevo = new Nodo(producto % 10); // Insertar al inicio
        nuevo->siguiente = resultado;
        if (resultado) resultado->anterior = nuevo;
        resultado = nuevo;
    }
    return resultado;
}

int compararNumeros(Nodo* num1, Nodo* num2) { // Retorna 1 si num1 > num2, -1 si num1 < num2, 0 si son iguales
    int len1 = contarNodos(num1);
    int len2 = contarNodos(num2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    while (num1) { // Misma longitud, comparar dígito por dígito
        if (num1->dato > num2->dato) return 1;
        if (num1->dato < num2->dato) return -1;
        num1 = num1->siguiente;
        num2 = num2->siguiente;
    }
    return 0; // Son iguales
}
// ======================= PATRONES =======================

std::vector<std::pair<Nodo*, Nodo*>> encontrarPalindromos(Nodo* cabeza) { // Retorna un vector de pares de nodos que representan los inicios y finales de los palíndromos encontrados
    std::vector<std::pair<Nodo*, Nodo*>> palindromos;
    Nodo* centro = cabeza;
    while (centro) {
        // Palindromos de longitud impar
        Nodo* izq = centro;
        Nodo* der = centro;
        while (izq && der && izq->dato == der->dato) {
            palindromos.push_back({izq, der});
            izq = izq->anterior;
            der = der->siguiente;
        }
        // Palindromos de longitud par
        izq = centro;
        der = centro->siguiente;
        while (izq && der && izq->dato == der->dato) {
            palindromos.push_back({izq, der});
            izq = izq->anterior;
            der = der->siguiente;
        }
        centro = centro->siguiente;
    }
    
    return palindromos;
}

Nodo* subsecuenciaCrecienteMasLarga(Nodo* cabeza) { // subsecuencia es una secuencia de nodos contiguos, ejemplo 1<->2<->3<->1<->2<->3<->4 retorna el nodo con 1 (inicio de la secuencia más larga)
    if (!cabeza) return nullptr;
    Nodo* mejorInicio = cabeza;
    Nodo* mejorFin = cabeza;
    int mejorLongitud = 1;
    Nodo* inicioActual = cabeza;
    Nodo* actual = cabeza;
    int longitudActual = 1;
    while (actual->siguiente) {
        if (actual->siguiente->dato > actual->dato) {
            longitudActual++;
        } else {
            if (longitudActual > mejorLongitud) {
                mejorLongitud = longitudActual;
                mejorInicio = inicioActual;
                mejorFin = actual;
            }
            inicioActual = actual->siguiente;
            longitudActual = 1;
        }
        actual = actual->siguiente;
    }
    if (longitudActual > mejorLongitud) { // Verificar última secuencia
        mejorInicio = inicioActual;
        mejorFin = actual;
    }
    return mejorInicio; // Retorna el inicio de la secuencia más larga
}

Nodo* rotarGrupos(Nodo* cabeza, int k) { // Invertir nodos en grupos de k, ejemplo: 1<->2<->3<->4<->5 con k=2 -> 2<->1<->4<->3<->5
    if (!cabeza || k <= 1) return cabeza;
    Nodo* resultado = nullptr;
    Nodo* finResultado = nullptr;
    Nodo* actual = cabeza;
    while (actual) {  
        Nodo* inicioGrupo = actual; // Tomar siguiente grupo de k elementos
        Nodo* finGrupo = actual; 
        for (int i = 1; i < k && finGrupo->siguiente; i++) { // Avanzar k posiciones o hasta el final
            finGrupo = finGrupo->siguiente;
        }       
        Nodo* siguienteGrupo = finGrupo->siguiente;
        finGrupo->siguiente = nullptr; // Desconectar grupo
        if (siguienteGrupo) siguienteGrupo->anterior = nullptr;
        Nodo* grupoInvertido = invertirLista(inicioGrupo); // Invertir grupo
        if (!resultado) { // Conectar al resultado
            resultado = grupoInvertido;
            finResultado = inicioGrupo; // inicioGrupo ahora es el final después de invertir
        } else {
            finResultado->siguiente = grupoInvertido;
            grupoInvertido->anterior = finResultado;
            finResultado = inicioGrupo;
        }
        actual = siguienteGrupo;
    }
    return resultado;
}

bool esPalindromo(Nodo* cabeza){
    if(!cabeza || !cabeza->siguiente) return true; // Lista vacía o con un solo elemento es palíndromo
    Nodo* cola = cabeza;
    while(cola->siguiente) cola = cola->siguiente; // Ir al final de la lista
    while(cabeza != cola && cabeza->anterior != cola) { // Mientras no se crucen
        if(cabeza->dato != cola->dato) return false; // Si los datos no coinciden, no es palíndromo
        cabeza = cabeza->siguiente; // Avanzar al siguiente nodo
        cola = cola->anterior; // Retroceder al anterior
    }
    return true; // Si se cruzan o son iguales, es palíndromo
}

// Reordenar lista: primera mitad + segunda mitad invertida
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5
// Resultado: 1 <-> 5 <-> 2 <-> 4 <-> 3
// Si la lista tiene un número impar de elementos, el elemento del medio se queda en su lugar
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
// Resultado: 1 <-> 6 <-> 2 <-> 5 <-> 3 <-> 4
// Si la lista tiene un número par de elementos, el elemento del medio se queda en su lugar
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
// Resultado: 1 <-> 6 <-> 2 <-> 5 <-> 3 <-> 4
void reorderList(Nodo*& cabeza){
    if(!cabeza || !cabeza->siguiente) return;
    // 1. Medio
    Nodo* slow=cabeza; Nodo* fast=cabeza;
    while(fast && fast->siguiente){ slow=slow->siguiente; fast=fast->siguiente->siguiente; }
    Nodo* second = slow;
    // 2. Cortar
    if(second->anterior){ second->anterior->siguiente=nullptr; second->anterior=nullptr; }
    // 3. Invertir segunda mitad (usar invertirLista sobre second)
    second = invertirLista(second);
    // 4. Mezclar alternando
    Nodo* first=cabeza;
    while(first && second){
        Nodo* fnext=first->siguiente;
        Nodo* snext=second->siguiente;
        first->siguiente = second;
        second->anterior = first;
        if(fnext){
            second->siguiente = fnext;
            fnext->anterior   = second;
        }
        first=fnext;
        second=snext;
    }
}

// Eliminar n-ésimo desde el final
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5, n=2 -> Eliminar 4
// Resultado: 1 <-> 2 <-> 3 <-> 5
// Si n es mayor o igual a la longitud de la lista, eliminar la cabeza
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5, n=5 -> Eliminar 1
// Resultado: 2 <-> 3 <-> 4 <-> 5
// Si n es mayor que la longitud de la lista, eliminar la cabeza
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5, n=6 -> Eliminar 1
Nodo* removeNthFromEnd(Nodo* cabeza,int n){
    if(!cabeza) return cabeza;
    Nodo* tail=cabeza; int len=1;
    while(tail->siguiente){ tail=tail->siguiente; len++; }
    if(n>=len){ // eliminar cabeza
        Nodo* tmp=cabeza;
        cabeza=cabeza->siguiente;
        if(cabeza) cabeza->anterior=nullptr;
        delete tmp;
        return cabeza;
    }
    int posFromStart = len-n;
    Nodo* cur=cabeza;
    while(--posFromStart) cur=cur->siguiente;
    Nodo* target=cur->siguiente;
    cur->siguiente = target->siguiente;
    if(target->siguiente) target->siguiente->anterior = cur;
    delete target;
    return cabeza;
}

// Particionar (LeetCode 86): < x seguido de >= x (estable)
// Dada una lista doblemente enlazada, reordena los nodos de tal manera que todos los nodos con valores menores que x aparezcan antes de los nodos con valores mayores o iguales a x.
// Mantiene el orden relativo de los nodos con valores menores que x y los nodos con valores mayores o iguales a x.
// Ejemplo: 1 <-> 4 <-> 3 <-> 2 <-> 5, x=3 -> 1 <-> 2 <-> 4 <-> 3 <-> 5
// Si no hay nodos menores que x, la lista permanece igual
// Ejemplo: 4 <-> 5 <-> 6, x=3 -> 4 <-> 5 <-> 6
// Si no hay nodos mayores o iguales a x, la lista permanece igual
// Ejemplo: 1 <-> 2 <-> 3, x=4 -> 1 <-> 2 <-> 3
Nodo* partitionList(Nodo* cabeza,int x){
    Nodo *lessH=nullptr,*lessT=nullptr,*geH=nullptr,*geT=nullptr,*cur=cabeza;
    while(cur){
        Nodo* nxt=cur->siguiente;
        cur->anterior = cur->siguiente = nullptr;
        if(cur->dato < x){
            if(!lessH) lessH=lessT=cur;
            else { lessT->siguiente=cur; cur->anterior=lessT; lessT=cur; }
        }else{
            if(!geH) geH=geT=cur;
            else { geT->siguiente=cur; cur->anterior=geT; geT=cur; }
        }
        cur=nxt;
    }
    if(!lessH) return geH;
    lessT->siguiente = geH;
    if(geH) geH->anterior = lessT;
    return lessH;
}

// Pairwise swap (intercambiar nodos adyacentes)
// Dada una lista doblemente enlazada, intercambia cada par de nodos adyacentes.
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 = 2 <-> 1 <-> 4 <-> 3
// Si la lista tiene un número impar de nodos, el último nodo permanece en su lugar
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5 = 2 <-> 1 <-> 4 <-> 3 <-> 5
Nodo* swapPairs(Nodo* cabeza){
    if(!cabeza || !cabeza->siguiente) return cabeza;
    Nodo* cur=cabeza;
    Nodo* newHead=cabeza->siguiente;
    while(cur && cur->siguiente){
        Nodo* nxt=cur->siguiente;
        Nodo* after=nxt->siguiente;
        // swap
        nxt->anterior = cur->anterior;
        nxt->siguiente = cur;
        cur->anterior = nxt;
        cur->siguiente = after;
        if(after) after->anterior = cur;
        if(nxt->anterior) nxt->anterior->siguiente = nxt;
        cur = after;
    }
    return newHead;
}

// Segregar pares adelante (estable dentro de cada grupo)
// Dada una lista doblemente enlazada, separa los nodos con valores pares y los nodos con valores impares.
// Los nodos con valores pares deben aparecer antes de los nodos con valores impares,
// manteniendo el orden relativo de los nodos dentro de cada grupo.
// Ejemplo: 1 <-> 2 <-> 3 <-> 4 <-> 5 = 2 <-> 4 <-> 1 <-> 3 <-> 5
// Si no hay nodos pares, la lista permanece igual
// Ejemplo: 1 <-> 3 <-> 5 = 1 <-> 3 <-> 5
// Si no hay nodos impares, la lista permanece igual
// Ejemplo: 2 <-> 4 <-> 6 = 2 <-> 4 <-> 6
Nodo* segregateEvenOdd(Nodo* cabeza){
    if(!cabeza) return cabeza;
    Nodo *evenH=nullptr,*evenT=nullptr,*oddH=nullptr,*oddT=nullptr;
    Nodo* cur=cabeza;
    while(cur){
        Nodo* nxt=cur->siguiente;
        cur->anterior=cur->siguiente=nullptr;
        if(cur->dato %2==0){
            if(!evenH) evenH=evenT=cur;
            else { evenT->siguiente=cur; cur->anterior=evenT; evenT=cur; }
        }else{
            if(!oddH) oddH=oddT=cur;
            else { oddT->siguiente=cur; cur->anterior=oddT; oddT=cur; }
        }
        cur=nxt;
    }
    if(!evenH) return oddH;
    evenT->siguiente = oddH;
    if(oddH) oddH->anterior = evenT;
    return evenH;
}

// Detectar ciclo (doble seguridad)
bool tieneCiclo(Nodo* cabeza){
    Nodo* slow=cabeza; Nodo* fast=cabeza;
    while(fast && fast->siguiente){
        slow=slow->siguiente;
        fast=fast->siguiente->siguiente;
        if(slow==fast) return true;
    }
    return false;
}

// Para llamar funciones en main
// inicializar lista con Nodo* cabeza = nullptr;
// llamar funciones como insertarInicio(cabeza, valor), insertarFinal(cabeza, valor), etc.