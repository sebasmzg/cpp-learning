#include <iostream>
#include <vector> // Para usar std::vector
#include <utility> // Para std::pair
#include <algorithm> // Para std::swap
#include <unordered_map> // Para std::unordered_map
#include <unordered_set> // Para std::unordered_set

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int v) : dato(v), siguiente(nullptr) {} // Constructor para inicializar el nodo con un valor y un puntero nulo
};

// ======================= INSERCIÓN =======================
Nodo* insertarInicio(Nodo* cabeza, int dato) {
    Nodo* nuevo = new Nodo(dato); // Crear un nuevo nodo
    nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
    cabeza = nuevo; // Actualizar la cabeza para que apunte al nuevo nodo
    return cabeza; // Devolver la nueva cabeza de la lista
}

Nodo* insertarFinal(Nodo* cabeza, int dato){
    Nodo* nuevo = new Nodo(dato);
    if(!cabeza) {
        cabeza = nuevo; // Si la lista está vacía, el nuevo nodo es la cabeza
        return cabeza;
    }
    Nodo* temp = cabeza;
    while(temp->siguiente){ // mientras haya un nodo siguiente
        temp = temp->siguiente; // Avanzar al último nodo
    }
    temp->siguiente = nuevo; // El último nodo apunta al nuevo nodo
    return cabeza; // Devolver la cabeza de la lista
}

Nodo* insertarPosicion(Nodo* cabeza, int dato, int posicion){
    if(posicion == 0){
        insertarInicio(cabeza, dato); // Si la posición es 0, insertar al inicio
        return cabeza;
    }
    Nodo* nuevo = new Nodo(dato);
    Nodo* temp = cabeza;
    for(int i = 0; i < posicion - 1 && temp; ++i){ // i menor que posicin - 1, avanzar al nodo anterior y temp no sea nulo
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    if(!temp) return cabeza; // Si temp es nulo, la posición es inválida
    nuevo->siguiente = temp->siguiente; // El nuevo nodo apunta al siguiente del nodo actual
    temp->siguiente = nuevo; // El nodo actual apunta al nuevo nodo
    return cabeza; // Devolver la cabeza de la lista
}

Nodo* insertarEntreNodos(Nodo* cabeza, Nodo* nodoIzquierda, Nodo* nodoDerecha, int dato){
    if(!cabeza || !nodoIzquierda || !nodoDerecha) return cabeza; // Si la lista o los nodos son nulos, no hacer nada
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodoDerecha; // El nuevo nodo apunta al nodo derecho
    nodoIzquierda->siguiente = nuevo; // El nodo izquierdo apunta al nuevo nodo
    return cabeza; // Devolver la cabeza de la lista
}

void insertarDespuesDe(Nodo* nodo, int dato){
    if(!nodo) return; // Si el nodo es nulo, no hacer nada
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = nodo->siguiente; // El nuevo nodo apunta al siguiente del nodo actual
    nodo->siguiente = nuevo; // El nodo actual apunta al nuevo nodo
}

void insertarAntesDe(Nodo*& cabeza, Nodo* nodo, int dato){
    if(!cabeza || !nodo) return; // Si la lista o el nodo son nulos, no hacer nada
    if(cabeza == nodo) { // Si el nodo es la cabeza
        cabeza = insertarInicio(cabeza, dato); // Insertar al inicio
        return;
    }
    Nodo* nuevo = new Nodo(dato);
    Nodo* temp = cabeza;
    while(temp && temp->siguiente != nodo) { // Buscar el nodo anterior
        temp = temp->siguiente;
    }
    if(!temp) return; // Si no se encontró el nodo anterior, no hacer nada
    nuevo->siguiente = nodo; // El nuevo nodo apunta al nodo actual
    temp->siguiente = nuevo; // El nodo anterior apunta al nuevo nodo
}

Nodo* insertarOrdenado(Nodo*& cabeza, int dato){
    Nodo* nuevo = new Nodo(dato);
    if(!cabeza || cabeza->dato >= dato) { // Si la lista está vacía o el nuevo dato es menor que la cabeza
        nuevo->siguiente = cabeza; // El nuevo nodo apunta a la antigua cabeza
        cabeza = nuevo; // Actualizar la cabeza
        return cabeza; 
    }
    Nodo* temp = cabeza;
    while(temp->siguiente && temp->siguiente->dato < dato) { // Buscar la posición correcta
        temp = temp->siguiente;
    }
    nuevo->siguiente = temp->siguiente; // El nuevo nodo apunta al siguiente
    temp->siguiente = nuevo; // El nodo actual apunta al nuevo nodo
    return cabeza; // Devolver lista con nuevo nodo insertado
}
// ======================= BÚSQUEDA =======================
Nodo* buscar(Nodo* cabeza, int valor){
    Nodo* temp = cabeza;
    while(temp && temp->dato != valor){ // Mientras temp no sea nulo y el dato no sea el valor buscado
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return temp; // Si se encuentra el valor, devolver el nodo
}

int obtenerPosicion(Nodo* cabeza, int valor){ // Obtener la posición de un valor
    int posicion = 0;
    Nodo* temp = cabeza;
    while(temp){
        if(temp->dato == valor) return posicion; // Si se encuentra el valor, devolver la posición
        temp = temp->siguiente; // Avanzar al siguiente nodo
        posicion++; // Incrementar la posición
    }
    return -1; // Si no se encuentra el valor, devolver -1
}

std::vector<Nodo*> buscarTodos(Nodo* cabeza, int valor){ // Buscar múltiple ocurencias
    std::vector<Nodo*> resultados;
    if(!cabeza) return resultados; // Si la lista está vacía, devolver un vector vacío
    Nodo* temp = cabeza;
    while(temp){
        if(temp->dato == valor){
            resultados.push_back(temp); // Agregar el nodo a los resultados si el dato coincide
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return resultados; // Devolver todos los nodos encontrados
}

Nodo* buscarMinimo(Nodo* cabeza){
    if(!cabeza ) return nullptr; // Si la lista está vacía, devolver nulo
    Nodo* minimo = cabeza; // Suponer que el primer nodo es el mínimo
    Nodo* temp = cabeza->siguiente; // Empezar desde el segundo nodo
    while(temp){
        if(temp->dato < minimo->dato){ // Si el dato del nodo actual es menor que el mínimo
            minimo = temp; // Actualizar el mínimo
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return minimo; // Devolver el nodo con el valor mínimo
}

Nodo* buscarMaximo(Nodo* cabeza){
    if(!cabeza ) return nullptr; // Si la lista está vacía, devolver nulo
    Nodo* maximo = cabeza; // Suponer que el primer nodo es el máximo
    Nodo* temp = cabeza->siguiente; // Empezar desde el segundo nodo
    while(temp){
        if(temp->dato > maximo->dato){ // Si el dato del nodo actual es mayor que el máximo
            maximo = temp; // Actualizar el máximo
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return maximo; // Devolver el nodo con el valor máximo
}

Nodo* buscarSegundoMayor(Nodo* cabeza){
    if(!cabeza || !cabeza->siguiente) return nullptr; // Si la lista está vacía o tiene un solo elemento, devolver nulo
    Nodo* mayor = nullptr;
    Nodo* segundoMayor = nullptr;
    Nodo* temp = cabeza;
    while(temp){
        if(!mayor || temp->dato > mayor->dato){ // Si no hay mayor o el dato actual es mayor que el mayor
            segundoMayor = mayor; // Actualizar el segundo mayor
            mayor = temp; // Actualizar el mayor
        } else if((!segundoMayor || temp->dato > segundoMayor->dato) && temp->dato != mayor->dato){ // Si no hay segundo mayor o el dato actual es mayor que el segundo mayor y no es igual al mayor
            segundoMayor = temp; // Actualizar el segundo mayor
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return segundoMayor; // Devolver el nodo con el segundo valor máximo
}
// ======================= ELIMINACIÓN =======================
void eliminarInicio(Nodo*& cabeza){ // Recibe referencia a la cabeza
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    Nodo* temp = cabeza; // Guardar la cabeza actual
    cabeza = cabeza->siguiente; // Actualizar la cabeza al siguiente nodo
    delete temp; // Liberar memoria del nodo eliminado
}

void eliminarFinal(Nodo*& cabeza) {
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    if(!cabeza->siguiente) { // Si solo hay un nodo
        delete cabeza; // Liberar memoria del único nodo
        cabeza = nullptr; // Actualizar la cabeza a nulo
        return;
    }
    Nodo* temp = cabeza;
    while(temp->siguiente->siguiente) { // Mientras haya un nodo siguiente, avanzar hasta el penúltimo
        temp = temp->siguiente; // Avanzar al último nodo
    }
    // ahora temp apunta al penúltimo nodo
    delete temp->siguiente; // Liberar memoria del último nodo
    temp->siguiente = nullptr; // Actualizar el penúltimo nodo
}

void eliminarValor(Nodo*& cabeza, int valor) {
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    if(cabeza->dato == valor) { // Si el valor está en la cabeza
        eliminarInicio(cabeza); // Eliminar el nodo de inicio
        return;
    }
    Nodo* temp = cabeza;
    while(temp->siguiente && temp->siguiente->dato != valor) { // Buscar el nodo con el valor mientras que haya un siguiente nodo y el siguiente nodo no tenga el valor
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    if(temp->siguiente) { // Si se encontró el nodo
        Nodo* aEliminar = temp->siguiente; // Guardar el nodo a eliminar
        temp->siguiente = aEliminar->siguiente; // Actualizar el enlace del nodo anterior
        delete aEliminar; // Liberar memoria del nodo eliminado
    }
}

// eliminar todas ocurrencias de un valor
void eliminarTodasOcurrencias(Nodo*& cabeza, int valor) {
    while(cabeza && cabeza->dato == valor) { // Mientras la cabeza no sea nula y el dato de la cabeza sea el valor a eliminar
        eliminarInicio(cabeza); // Eliminar el nodo de inicio
    }
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    Nodo* temp = cabeza;
    while(temp->siguiente) { // Mientras haya un nodo siguiente
        if(temp->siguiente->dato == valor) { // Si el siguiente nodo tiene el valor a eliminar
            Nodo* aEliminar = temp->siguiente; // Guardar el nodo a eliminar
            temp->siguiente = aEliminar->siguiente; // Actualizar el enlace del nodo anterior
            delete aEliminar; // Liberar memoria del nodo eliminado
        } else {
            temp = temp->siguiente; // Avanzar al siguiente nodo
        }
    }
}

void eliminarPosicion(Nodo*& cabeza, int posicion) {
    if(!cabeza || posicion < 0) return; // Si la lista está vacía o la posición es inválida, no hacer nada
    if(posicion == 0) { // Si la posición es 0, eliminar el nodo de inicio
        eliminarInicio(cabeza);
        return;
    }
    Nodo* temp = cabeza;
    for(int i = 0; i < posicion - 1 && temp->siguiente; ++i) { // Avanzar al nodo anterior a la posición
        temp = temp->siguiente;
    }
    if(temp->siguiente) { // Si se encontró el nodo en la posición
        Nodo* aEliminar = temp->siguiente; // Guardar el nodo a eliminar
        temp->siguiente = aEliminar->siguiente; // Actualizar el enlace del nodo anterior
        delete aEliminar; // Liberar memoria del nodo eliminado
    }
}

void eliminarDuplicados(Nodo*& cabeza){
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    Nodo* actual = cabeza; // Nodo actual para recorrer la lista
    while(actual){
        Nodo* runner = actual;
        while(runner->siguiente){ // Nosdo runner para comparar con el siguiente
            if(runner->siguiente->dato == actual->dato){ // Si el siguiente nodo tiene el mismo dato
                Nodo* duplicado = runner->siguiente; // Guardar el nodo duplicado
                runner->siguiente = duplicado->siguiente; // Actualizar el enlace del nodo anterior
                delete duplicado; // Liberar memoria del nodo duplicado
            } else {
                runner = runner->siguiente; // Avanzar al siguiente nodo
            }
        }
        actual = actual->siguiente; // Avanzar al siguiente nodo
    }
}

void eliminarLista(Nodo*& cabeza) {
    while(cabeza) { // Mientras haya nodos en la lista
        Nodo* temp = cabeza; // Guardar la cabeza actual
        cabeza = cabeza->siguiente; // Actualizar la cabeza al siguiente nodo
        delete temp; // Liberar memoria del nodo eliminado
    }
    cabeza = nullptr; // Asegurarse de que la cabeza sea nula al final
}

void eliminarDuplicadosOrdenada(Nodo*& cabeza){ // Asumiendo que la lista está ordenada y hay duplicados consecutivos
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    Nodo* actual = cabeza; // Nodo actual para recorrer la lista
    while(actual && actual->siguiente){ // Mientras haya un nodo actual y un siguiente
        if(actual->dato == actual->siguiente->dato){ // Si el dato del nodo actual es igual al del siguiente
            Nodo* duplicado = actual->siguiente; // Guardar el nodo duplicado
            actual->siguiente = duplicado->siguiente; // Actualizar el enlace del nodo actual
            delete duplicado; // Liberar memoria del nodo duplicado
        } else {
            actual = actual->siguiente; // Avanzar al siguiente nodo
        }
    }
}
// ======================= MANIPULACIÓN =======================
void intercambiarNodos(Nodo*& cabeza, int x, int y){
    if(x == y) return; // Si los valores son iguales, no hacer nada
    if(!cabeza) return; // Si la lista está vacía, no hacer nada
    Nodo* prevX = nullptr, *currX = cabeza; // anterior x y actual x
    while(currX && currX->dato != x){ // Buscar el nodo con valor x
        prevX = currX; // Actualizar el nodo anterior
        currX = currX->siguiente; // Avanzar al siguiente nodo
    }
    Nodo* prevY = nullptr, *currY = cabeza; // anterior y y actual y
    while(currY && currY->dato != y){ // Buscar el nodo con valor y
        prevY = currY; // Actualizar el nodo anterior
        currY = currY->siguiente; // Avanzar al siguiente nodo  
    }
    if(!currX || !currY) return; // Si no se encontraron ambos nodos, no hacer nada
    if(prevX) prevX->siguiente = currY; // Si x no es la cabeza, actualizar el enlace del nodo anterior
    else cabeza = currY; // Si x es la cabeza, actualizar la cabeza
    if(prevY) prevY->siguiente = currX; // Si y no es la cabeza, actualizar el enlace del nodo anterior
    else cabeza = currX; // Si y es la cabeza, actualizar la cabeza
    Nodo* temp = currX->siguiente; // Guardar el siguiente de x
    currX->siguiente = currY->siguiente; // Actualizar el siguiente de x
    currY->siguiente = temp; // Actualizar el siguiente de y
}

Nodo* rotarDerecha(Nodo* cabeza, int k){ // Rotar lista hacia la derecha k posiciones
    if(!cabeza || !cabeza->siguiente || k == 0) return cabeza; // Si la lista está vacía, tiene un solo nodo o k es 0, no hacer nada
    // encontrar longitud y último noso
    int longitud = 1; // Contador de longitud
    Nodo* ultimo = cabeza; // Nodo último para recorrer la lista
    while (ultimo->siguiente) { // Mientras haya un nodo siguiente
        ultimo = ultimo->siguiente; // Avanzar al siguiente nodo
        longitud++; // Incrementar la longitud
    }
    // normalizar k
    k = k % longitud; // Ajustar k si es mayor que la longitud
    if(k == 0) return cabeza; // Si k es 0 después de normalizar, no hacer nada
    // encontrar nuevo punto de corte
    Nodo* nuevoCola = cabeza; // Nodo nuevo cola para recorrer la lista
    for(int i = 0; i < longitud - k - 1; ++i) { // Avanzar hasta el nodo que será la nueva cola
        nuevoCola = nuevoCola->siguiente; // Avanzar al siguiente nodo
    }
    Nodo* nuevaCabeza = nuevoCola->siguiente; // La nueva cabeza será el siguiente de la nueva cola
    nuevoCola->siguiente = nullptr; // La nueva cola ahora será el último nodo
    ultimo->siguiente = cabeza; // El último nodo apunta a la antigua cabeza
    return nuevaCabeza; // Devolver la nueva cabeza
}

Nodo* rotarIzquierda(Nodo* cabeza, int k) { // Rotar lista hacia la izquierda k posiciones
    if (!cabeza || !cabeza->siguiente || k == 0) return cabeza; // Si la lista está vacía, tiene un solo nodo o k es 0, no hacer nada
    // encontrar longitud y último nodo
    int longitud = 1; // Contador de longitud
    Nodo* ultimo = cabeza; // Nodo último para recorrer la lista
    while (ultimo->siguiente) { // Mientras haya un nodo siguiente
        ultimo = ultimo->siguiente; // Avanzar al siguiente nodo
        longitud++; // Incrementar la longitud
    }
    // normalizar k
    k = k % longitud; // Ajustar k si es mayor que la longitud
    if (k == 0) return cabeza; // Si k es 0 después de normalizar, no hacer nada
    // encontrar nuevo punto de corte
    Nodo* nuevoCabeza = cabeza; // Nodo nuevo cabeza para recorrer la lista
    for (int i = 0; i < k - 1; ++i) { // Avanzar hasta el nodo que será la nueva cabeza
        nuevoCabeza = nuevoCabeza->siguiente; // Avanzar al siguiente nodo
    }
    Nodo* nuevaCola = nuevoCabeza->siguiente; // La nueva cola será el siguiente de la nueva cabeza
    nuevoCabeza->siguiente = nullptr; // La nueva cabeza ahora será el último nodo
    ultimo->siguiente = cabeza; // El último nodo apunta a la antigua cabeza
    return nuevaCola; // Devolver la nueva cola
}

void ordenarLista(Nodo*& cabeza) {
    if (!cabeza || !cabeza->siguiente) return; // Si la lista está vacía o tiene un solo elemento
    Nodo* actual = cabeza; // Nodo actual para recorrer la lista
    Nodo* siguiente = nullptr; // Nodo para comparar con el actual
    while (actual) { // Mientras haya un nodo actual
        siguiente = actual->siguiente; // Empezar desde el siguiente nodo
        while (siguiente) { // Mientras haya un nodo siguiente
            if (actual->dato > siguiente->dato) { // Si el dato actual es mayor que el siguiente
                std::swap(actual->dato, siguiente->dato); // Intercambiar los datos
            }
            siguiente = siguiente->siguiente; // Avanzar al siguiente nodo
        }
        actual = actual->siguiente; // actual avanza al siguiente nodo
    }
}

int contarNodos(Nodo* cabeza) {
    int contador = 0;
    Nodo* temp = cabeza;
    while(temp) { // Mientras haya un nodo
        contador++; // Incrementar el contador
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return contador; // Devolver el número de nodos
}

Nodo* obtenerNodo(Nodo* cabeza, int posicion){
    if(posicion < 0) return nullptr; // Si la posición es inválida, devolver nulo
    Nodo* temp = cabeza;
    for(int i = 0; i < posicion && temp; ++i) { // Avanzar al nodo en la posición deseada
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    return temp; // Devolver el nodo en la posición deseada, o nulo si no existe    
}

Nodo* obtenerUltimoNodo(Nodo* cabeza) {
    if(!cabeza) return nullptr; // Si la lista está vacía, devolver nulo
    while(cabeza->siguiente) { // Mientras haya un nodo siguiente
        cabeza = cabeza->siguiente; // Avanzar al siguiente nodo
    }
    return cabeza; // Devolver el último nodo
};

Nodo* invertirLista(Nodo* cabeza) {
    Nodo* anterior = nullptr;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente; // 1. Guardar el siguiente
        actual->siguiente = anterior;           // 2. Invertir el enlace
        anterior = actual;                 // 3. Avanzar prev
        actual = siguiente;              // 4. Avanzar current
    }
    return anterior; // Nueva cabeza
}

Nodo* clonarLista(Nodo* cabeza){
    if(!cabeza) return nullptr; // Si la lista está vacía, devolver nulo
    Nodo* nuevaCabeza = new Nodo(cabeza->dato); // Crear el primer nodo de la nueva lista
    Nodo* actual = nuevaCabeza; // Nodo actual para la nueva lista
    Nodo* temp = cabeza->siguiente; // Nodo temporal para recorrer la lista original
    while(temp){
        actual->siguiente = new Nodo(temp->dato); // Crear un nuevo nodo con el dato del nodo temporal
        actual = actual->siguiente; // Avanzar al siguiente nodo en la nueva lista
        temp = temp->siguiente; // Avanzar al siguiente nodo en la lista original
    }
    return nuevaCabeza; // Devolver la nueva lista clonada
}

std::pair<Nodo*, Nodo*> dividirLista(Nodo* cabeza){ // Dividir la lista en dos mitades
    if(!cabeza || !cabeza->siguiente) return {cabeza, nullptr}; // Si la lista está vacía o tiene un solo nodo, devolver la cabeza y nulo
    Nodo* lento = cabeza; // Nodo lento para recorrer la lista
    Nodo* rapido = cabeza->siguiente; // Nodo rápido para recorrer la lista
    Nodo* anterior = nullptr; // Nodo anterior para mantener el enlace
    while(rapido && rapido->siguiente) { // Mientras haya un nodo rápido y un siguiente
        anterior = lento; // Guardar el nodo lento como anterior
        lento = lento->siguiente; // Avanzar lento al siguiente nodo
        rapido = rapido->siguiente->siguiente; // Avanzar rápido dos nodos
    }
    anterior->siguiente = nullptr; // Dividir la lista en dos
    return {cabeza, lento}; // Devolver la cabeza de la primera mitad y la cabeza de la segunda mitad
}

Nodo* concatenarListas(Nodo* cabeza1, Nodo* cabeza2) { // no importas si las listas están ordenadas o no
    if(!cabeza1) return cabeza2; // Si la primera lista está vacía, devolver la segunda lista
    if(!cabeza2) return cabeza1; // Si la segunda lista está vacía, devolver la primera lista
    Nodo* temp = cabeza1; // Nodo temporal para recorrer la primera lista
    while(temp->siguiente) { // Mientras haya un nodo siguiente
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    temp->siguiente = cabeza2; // Enlazar el último nodo de la primera lista con la cabeza de la segunda lista
    return cabeza1; // Devolver la cabeza de la lista concatenada
}

Nodo* mergeListas(Nodo* cabeza1, Nodo* cabeza2) { // Asumiendo que ambas listas están ordenadas 
    if(!cabeza1) return cabeza2; // Si la primera lista está vacía, devolver la segunda lista
    if(!cabeza2) return cabeza1; // Si la segunda lista está vacía, devolver la primera lista
    Nodo* cabezaResultado = nullptr; // Cabeza de la lista resultante
    Nodo** ultimo = &cabezaResultado; // Puntero al último nodo de la lista resultante
    while(cabeza1 && cabeza2) { // Mientras haya nodos en ambas listas
        if(cabeza1->dato < cabeza2->dato) { // Si el dato de la primera lista es menor
            *ultimo = cabeza1; // Enlazar el último nodo con el nodo de la primera lista
            cabeza1 = cabeza1->siguiente; // Avanzar al siguiente nodo en la primera lista
        } else {
            *ultimo = cabeza2; // Enlazar el último nodo con el nodo de la segunda lista
            cabeza2 = cabeza2->siguiente; // Avanzar al siguiente nodo en la segunda lista
        }
        ultimo = &((*ultimo)->siguiente); // Avanzar el puntero al último nodo
    }
    *ultimo = (cabeza1) ? cabeza1 : cabeza2; // Enlazar el resto de la lista que no esté vacía
    return cabezaResultado; // Devolver la cabeza de la lista resultante
}

bool tieneCiclo(Nodo* cabeza){ // Detectar cilos (Floyd's Cycle Detection) ejemplo: 1->2->3->4->5->3 (ciclo)
    if(!cabeza || !cabeza->siguiente) return false; // Si la lista está vacía o tiene un solo nodo, no hay ciclo
    Nodo* lento = cabeza; // Nodo lento para recorrer la lista
    Nodo* rapido = cabeza->siguiente; // Nodo rápido para recorrer la lista
    while(rapido && rapido->siguiente){
        lento = lento->siguiente; // Avanzar lento al siguiente nodo
        rapido = rapido->siguiente->siguiente; // Avanzar rápido dos nodos
        if(lento == rapido) { // Si lento y rápido se encuentran, hay un ciclo
            return true;
        }
    }
    return false; // Si no hay ciclo
}

Nodo* entrarMedio(Nodo* cabeza){ // ejemplo: si la lista es 1->2->3->4->5, el resultado será el nodo con valor 3
    if(!cabeza) return nullptr; // Si la lista está vacía, devolver nulo
    Nodo* lento = cabeza; // Nodo lento para recorrer la lista
    Nodo* rapido = cabeza; // Nodo rápido para recorrer la lista
    while(rapido->siguiente && rapido->siguiente->siguiente) { // Mientras haya un nodo rápido y un siguiente
        lento = lento->siguiente; // Avanzar lento al siguiente nodo
        rapido = rapido->siguiente->siguiente; // Avanzar rápido dos nodos
    }
    return lento; // Devolver el nodo en el punto medio
}

bool esPalindromo(Nodo* cabeza){
    if(!cabeza || !cabeza->siguiente) return true; // Si la lista está vacía o tiene un solo nodo, es palíndromo
    Nodo* medio = entrarMedio(cabeza);
    Nodo* segundaMitad = invertirLista(medio->siguiente);
    Nodo* temp1 = cabeza; // Comparar la primera mitad con la segunda mitad invertida
    Nodo* temp2 = segundaMitad;
    while(temp2) { // Mientras haya nodos en la segunda mitad
        if(temp1->dato != temp2->dato) { // Si los datos no coinciden
            return false; // No es palíndromo
        }
        temp1 = temp1->siguiente;
        temp2 = temp2->siguiente;
    }
    return true; // Es palíndromo
}

Nodo* nEsimoDesdeElfinal(Nodo* cabeza, int n){ // ejemplo: si la lista es 1->2->3->4->5 y n=2, el resultado será el nodo con valor 4
    Nodo* primero = cabeza; // Nodo primero para recorrer la lista
    Nodo* segundo = cabeza; // Nodo segundo para recorrer la lista
    for(int i = 0; i < n; ++i) { // Avanzar el nodo primero n veces
        if(!primero) return nullptr; // Si no hay suficientes nodos, devolver nulo
        primero = primero->siguiente; // Avanzar al siguiente nodo
    }
    while(primero) { // Mientras haya un nodo primero
        primero = primero->siguiente; // Avanzar al siguiente nodo
        segundo = segundo->siguiente; // Avanzar al siguiente nodo
    }
    return segundo; // Devolver el nodo en la posición n desde el final
}

Nodo* revertirEnGrupos(Nodo* cabeza, int k) { // ejemplo: si la lista es 1->2->3->4->5 y k=2, el resultado será 2->1->4->3->5
    if (!cabeza || k <= 1) return cabeza; // Si la lista está vacía o k es menor o igual a 1, no hacer nada
    // verificar si hay la menos k nodos
    Nodo* temp = cabeza;
    for(int i = 0; i < k; ++i){
        if(!temp) return cabeza; // Si no hay suficientes nodos, devolver la cabeza
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    // revertur los primeros k nodos
    Nodo* anterior = nullptr; // Nodo anterior para revertir
    Nodo* actual = cabeza; // Nodo actual para recorrer la lista
    for(int i = 0; i < k; ++i) { // Revertir los primeros k nodos
        Nodo* siguiente = actual->siguiente; // Guardar el siguiente nodo
        actual->siguiente = anterior; // Invertir el enlace
        anterior = actual; // Avanzar el nodo anterior
        actual = siguiente; // Avanzar al siguiente nodo
    }
    // recursivamente procesar el resto
    if(actual) { // Si hay más nodos después de los primeros k
        cabeza->siguiente = revertirEnGrupos(actual, k); // Enlazar la cabeza con el resultado de la recursión
    } else {
        cabeza->siguiente = nullptr; // Si no hay más nodos, enlazar con nulo
    }
    return anterior; // Devolver la nueva cabeza de la lista revertida
}

// Intercalar nodos (par/impar posiciones)
Nodo* intercalarNodos(Nodo* cabeza){ // esto hace que los nodos en posiciones pares queden antes que los nodos en posiciones impares
    if(!cabeza || !cabeza->siguiente) return cabeza; // Si la lista está vacía o tiene un solo nodo, no hacer nada
    Nodo* impar = cabeza; // Nodo impar para recorrer la lista
    Nodo* par = cabeza->siguiente; // Nodo par para recorrer la lista
    Nodo* cabezaPar = par; // Guardar la cabeza de los nodos pares
    while(par && par->siguiente){
        impar->siguiente = par->siguiente; // Enlazar el nodo impar con el siguiente nodo impar
        impar = impar->siguiente; // Avanzar al siguiente nodo impar
        par->siguiente = impar->siguiente; // Enlazar el nodo par con el siguiente nodo par
        par = par->siguiente; // Avanzar al siguiente nodo par
    }
    impar->siguiente = cabezaPar; // Enlazar la lista impar con la lista par
    return cabeza; // Devolver la cabeza de la lista intercalada
    // si se quiere que los nodos en posiciones impares queden antes que los nodos en posiciones pares, se puede cambiar el orden de los enlaces
}

Nodo* interseccionListas(Nodo* cabeza1, Nodo* cabeza2) { // ejemplo si las listas son 1->2->3->4 y 6->7->3->4, la intersección es el nodo con valor 3
    if(!cabeza1 || !cabeza2) return nullptr; // Si alguna de las listas está vacía, devolver nulo
    Nodo* p1 = cabeza1;
    Nodo* p2 = cabeza2;
    while(p1 != p2){
        p1 = p1 ? p1->siguiente : cabeza2; // Si p1 llega al final, reiniciar a cabeza2
        p2 = p2 ? p2->siguiente : cabeza1; // Si p2 llega al final, reiniciar a cabeza1
    }
    return p1; // Devolver el nodo de intersección
}

bool hayInterseccion(Nodo* cabeza1, Nodo* cabeza2) {
    return interseccionListas(cabeza1, cabeza2) != nullptr; // Si hay intersección, devolver verdadero
}

int longitudHastaInterseccion(Nodo* cabeza, Nodo* interseccion) { // Obtener la longitud desde la cabeza hasta el nodo de intersección
    int longitud = 0;
    while (cabeza && cabeza != interseccion) {
        cabeza = cabeza->siguiente;
        longitud++;
    }
    return cabeza ? longitud : -1;
}

Nodo* sumarNumeros(Nodo* l1, Nodo* l2) { // Asumiendo que l1 y l2 son listas enlazadas donde cada nodo representa un dígito de un número, con el dígito menos significativo al inicio
    // ejemplo: si l1 es 2 -> 4 -> 3 (342) y l2 es 5 -> 6 -> 4 (465), el resultado será 7 -> 0 -> 8 (807)
    Nodo* resultado = nullptr; // Cabeza de la lista resultado
    Nodo** ultimo = &resultado; // Puntero al último nodo de la lista resultado
    int carry = 0; // Llevar el acarreo
    while (l1 || l2 || carry) { // Mientras haya nodos en l1 o l2 o haya acarreo
        int suma = carry; // Empezar con el acarreo
        if (l1) { // Si hay un nodo en l1
            suma += l1->dato; // Sumar el dato del nodo l1
            l1 = l1->siguiente; // Avanzar al siguiente nodo en l1
        }
        if (l2) { // Si hay un nodo en l2
            suma += l2->dato; // Sumar el dato del nodo l2
            l2 = l2->siguiente; // Avanzar al siguiente nodo en l2
        }
        carry = suma / 10; // Calcular el nuevo acarreo
        *ultimo = new Nodo(suma % 10); // Crear un nuevo nodo con el dígito resultante y enlazarlo
        ultimo = &((*ultimo)->siguiente); // Avanzar el puntero al último nodo
    }
    return resultado; // Devolver la cabeza de la lista resultado
}

Nodo* multiplicarPorDigito(Nodo* cabeza, int digito){ // Asumiendo que la lista representa un número y el dígito es un entero entre 0 y 9
    // ejemplo : si la lista es 1 -> 2 -> 3 (123) y el dígito es 4, el resultado será 4 -> 9 -> 2 (492)
    if(!cabeza || digito <= 0) return nullptr; // Si la lista está vacía o el dígito es menor o igual a 0, devolver nulo
    Nodo* resultado = nullptr; // Cabeza de la lista resultado
    Nodo** ultimo = &resultado; // Puntero al último nodo de la lista resultado
    int carry = 0; // Llevar el acarreo
    while(cabeza || carry){
        int producto = carry;
        if(cabeza) {
            producto += cabeza->dato * digito;
            cabeza = cabeza->siguiente;
        }
        carry = producto / 10;
        *ultimo = new Nodo(producto % 10);
        ultimo = &((*ultimo)->siguiente);
    }
    return resultado;
}

int elementoMasFrecuente(Nodo* cabeza){ // Encontrar el elemento más frecuente en la lista
    if(!cabeza) return -1; // Si la lista está vacía, devolver -1
    std::unordered_map<int, int> frecuencia; // Mapa para contar la frecuencia de los elementos
    Nodo* temp = cabeza; // Nodo temporal para recorrer la lista
    while(temp){
        frecuencia[temp->dato]++; // Incrementar la frecuencia del dato del nodo
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    int maxFrecuencia = 0; // Encontrar el elemento más frecuente
    int elemento = -1;
    for(const auto& par : frecuencia){
        if(par.second > maxFrecuencia){
            maxFrecuencia = par.second;
            elemento = par.first;
        }
    }
    return elemento;
}

bool tieneElementosUnicos(Nodo* cabeza){ // Verificar si todos los elementos en la lista son únicos
    std::unordered_set<int> elementos; // Conjunto para almacenar los elementos únicos
    while(cabeza){
        if(elementos.count(cabeza->dato)) return false; // Si el elemento ya está en el conjunto, no es único
        elementos.insert(cabeza->dato); // Insertar el elemento en el conjunto
        cabeza = cabeza->siguiente; // Avanzar al siguiente nodo
    }
    return true; // Si se recorrió toda la lista y no se encontraron duplicados, devolver verdadero
}

bool sonIguales(Nodo* cabeza1, Nodo* cabeza2){ // Verificar si dos listas son iguales (mismo tamaño y mismos valores en el mismo orden)
    while(cabeza1 && cabeza2){
        if(cabeza1->dato != cabeza2->dato) return false; // Si los datos no son iguales, devolver falso
        cabeza1 = cabeza1->siguiente; // Avanzar al siguiente nodo en la primera lista
        cabeza2 = cabeza2->siguiente; // Avanzar al siguiente nodo en la segunda lista
    }
    return cabeza1 == cabeza2; // Si ambos punteros son nulos, las listas son iguales
}

bool estaOrdenada(Nodo* cabeza, bool ascendente = true) { // Verificar si la lista está ordenada (ascendente o descendente)
    if (!cabeza || !cabeza->siguiente) return true;
    while (cabeza->siguiente) {
        if (ascendente) {
            if (cabeza->dato > cabeza->siguiente->dato) return false;
        } else {
            if (cabeza->dato < cabeza->siguiente->dato) return false;
        }
        cabeza = cabeza->siguiente;
    }
    return true;
}

Nodo* generarListaAleatoria(int tamaño, int min = 1, int max = 100) { // Generar una lista enlazada con valores aleatorios entre min y max
    if (tamaño <= 0) return nullptr;   
    Nodo* cabeza = new Nodo(min + rand() % (max - min + 1));
    Nodo* actual = cabeza;  
    for (int i = 1; i < tamaño; i++) {
        actual->siguiente = new Nodo(min + rand() % (max - min + 1));
        actual = actual->siguiente;
    }
    return cabeza;
}
// ======================= CICLOS =======================
Nodo* encontrarInicioCiclo(Nodo* cabeza) {
    if (!cabeza || !cabeza->siguiente) return nullptr; 
    Nodo* lento = cabeza;
    Nodo* rapido = cabeza;
    while (rapido && rapido->siguiente) { // Detectar si hay ciclo
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
        if (lento == rapido) break;
    }   
    if (!rapido || !rapido->siguiente) return nullptr;
    lento = cabeza; // Encontrar el inicio del ciclo
    while (lento != rapido) {
        lento = lento->siguiente;
        rapido = rapido->siguiente;
    }
    return lento;
}

int longitudCiclo(Nodo* cabeza) {
    Nodo* encuentro = encontrarInicioCiclo(cabeza);
    if (!encuentro) return 0;
    int longitud = 1;
    Nodo* temp = encuentro->siguiente;
    while (temp != encuentro) {
        temp = temp->siguiente;
        longitud++;
    }
    return longitud;
}

void crearCiclo(Nodo* cabeza, int posicion) {
    if (!cabeza) return;
    Nodo* ultimo = cabeza;
    Nodo* nodoPos = nullptr;
    int index = 0;
    while (ultimo->siguiente) {
        if (index == posicion) nodoPos = ultimo;
        ultimo = ultimo->siguiente;
        index++;
    }
    if (nodoPos) ultimo->siguiente = nodoPos;
}

void printList(Nodo* head) {
    Nodo* temp = head;
    while (temp != nullptr) {
        std::cout << temp->dato << " -> ";
        temp = temp->siguiente;
    }
    std::cout << "nullptr\n\n";
}

void imprimirConIndices(Nodo* cabeza) {
    Nodo* temp = cabeza;
    int index = 0;
    std::cout << "Lista con índices:\n";
    while(temp) {
        std::cout << "[" << index << "]: " << temp->dato << " -> ";
        temp = temp->siguiente;
        index++;
    }
    std::cout << "nullptr\n";
}
// Para llamar funciones en main
// inicializar lista con Nodo* cabeza = nullptr;
// llamar funciones como insertarInicio(cabeza, valor), insertarFinal(cabeza, valor), etc.