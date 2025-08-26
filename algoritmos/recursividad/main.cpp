#include <iostream>
#include <climits>

using namespace std;

int sumaNenteros (int n){
    if (n == 1){ // Definir caso base
        return 1;
    }else {
        return n + sumaNenteros(n - 1);  // Usar recursión usando n - 1 que se va acercando al caso base
    }
}

// fibonacci iterativo
// complejidad O(n)
long fibonacciIterativo(int n){
    if( n == 0 || n == 1){ // Condición de salida
        return n;
    }
    long fibinf = 0;
    long fibsup = 1;
    for(int i = 2; i <= n; ++i){
        int x = fibinf; // Calcular el siguiente número de Fibonacci x= 0
        fibinf = fibsup; // Actualizar el anterior fibinf = 1
        fibsup = x + fibinf; // Actualizar el actual fibsup = 0 + 1 = 1
    }
    return fibsup;
}

// fibonacci recursivo
// complejidad O(2^n)
long fibonacciRecursivo(int n){
    if( n == 0 || n == 1){ 
        return n; // Caso base
    }
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

// Recursividad indirecta

void functionA(char c);
void functionB(char c);

void functionA(char c){
    if(c >= 'A'){
        functionB(c); // Llamada a la función B que pasa el carácter actual
        std::cout << c << " "; // Imprimir el carácter actual
    }
}

void functionB(char c){
    functionA(--c); // llamada recursiva de functionA. --c es el carácter anterior
}

// Dado un numero natural obtener la suma de los digitos de que consta 
int sumaRecursiva(int n){
    if(n <= 9){
        return n; // Caso base: si n es un dígito, retornar n
    }
    // n % 10 obtiene el último dígito 
    // n / 10 elimina el último dígito
    return n % 10 + sumaRecursiva(n / 10); // Sumar el último dígito y llamar recursivamente con el resto
}

int sumaIterativa(int n){
    int suma = 0;
    while(n > 9){
        suma += n % 10;
        n /= 10;
    }
    return suma + n; // Retornar la suma total
}

// maximo comun divisor, el mayor divide al menor
int mcd(int m, int n){
// mcd(m,n) = n                                     si n <= m y n divide a m
    // mcd(m,n) = mcd(m,n)                          si m < n
    // mcd(m,n) = mcd(n, resto de m dividido n)     en caso contrario
    if(n <= m && m % n == 0){
        return n;
    } else if(m < n){
        return mcd(n, m);
    } else{
        return mcd(n, m % n);
    }
}

// Torres de Hanoi
// complejidad O(2^n)
void hanoi(char inicial, char centro, char destino, int n){
    if(n == 1){
        std::cout << "Mover disco " << n << "  desde varilla " << inicial << " a varilla " << destino << std::endl;
    } else {
        hanoi(inicial, destino, centro, n-1);  // mueve disco n-1 de inicial a centro, usando destino como auxiliar
        std::cout << "Mover disco " << n << " desde varilla " << inicial << " a varilla " << destino << std::endl;
        hanoi(centro, inicial, destino, n -1); // mueve disco n-1 de centro a destino, usando inicial como auxiliar
    }
}

// Búsqueda binaria
/*
*@param a[] Arreglo ordenado de elementos
*@param clave Elemento a buscar
*@param izquierda Índice izquierdo del subarreglo
*@param derecha Índice derecho del subarreglo
*@return Índice del elemento encontrado o -1 si no se encuentra
*/
// complejidad O(log n)
int busquedaBinaria(double a[], double clave, int inferior, int superior){
    int central; // punto medio
    if(inferior > superior){
        return -1; // Si el índice izquierdo es mayor que el derecho, no se encuentra
    } else {
        central = (inferior + superior) / 2; // calcular punto medio
        if(a[central] == clave){
            return central; // Si el elemento en el punto medio es igual a la clave, retornar central
        } else if(a[central] < clave){
            return busquedaBinaria(a, clave, central + 1, superior); // Buscar en la mitad superior
            // params: a= arreglo, clave= elemento a buscar, inferior= central + 1, superior= superior
            // inferior es central + 1, ya que el elemento en central es menor que la clave
        } else {
            return busquedaBinaria(a, clave, inferior, central - 1); // Buscar en la mitad inferior
            // params: a= arreglo, clave= elemento a buscar, inferior= inferior, superior= central - 1
            // superior es central - 1, ya que el elemento en central es mayor que la clave
        }
    }
    return -1;
}

// Encontrar subarreglo máximo usando divide y vencerás
int calMaxMitad(int arr[], int inferior, int central, int superior){
    int suma = 0;
    int sumaIzquierda = 0;
    for(int i = central; i >= inferior; --i){ // recorrer la mitad izquierda
        suma += arr[i]; // Sumar el elemento actual a la suma
        if(suma > sumaIzquierda) sumaIzquierda = suma; // Si la suma actual es mayor que la máxima encontrada
        // Actualizar la suma total
    }

    suma = 0;
    int sumaDerecha = 0;
    for(int i = central + 1; i <= superior; ++i){ // recorrer la mitad derecha
        suma += arr[i]; // Sumar el elemento actual a la suma
        if(suma > sumaDerecha) sumaDerecha = suma; // Si la suma actual es mayor que la máxima encontrada
        // Actualizar la suma total
    }
    return sumaIzquierda + sumaDerecha;
}

int subArrMax(int arr[], int inferior, int superior){
    // si arreglo solo tiene un elemento
    if(inferior == superior){
        return arr[inferior];
    }
    int central = (inferior + superior) / 2; 
    int maxInferior = subArrMax(arr,inferior, central);
    int maxSuperior = subArrMax(arr, central + 1, superior);
    int maxMitad = calMaxMitad(arr, inferior, central, superior);
    return std::max(std::max(maxInferior, maxSuperior), maxMitad);
}

// Mergesort
// Complejidad O(n log n)
void mezcla(int a[], int izq, int mid, int der){
    int* tmp; 
    int i, k, z; //  i es el índice del subarreglo izquierdo, k es el índice del subarreglo derecho, z es el índice del arreglo temporal
    tmp = new int[der - izq + 1]; // Crear un arreglo temporal para almacenar los elementos ordenados
    // new reserva memoria en el heap para arreglo de enteros del tamaño adecuado, la formula indica cantidad de elementos entre los indices
    i = z = izq; 
    k = mid + 1;
    z = 0;
    // bucle para mezcla utilizando temp[] como array auxiliar
    while(i <= mid && k <= der){
        if(a[i] <= a[k]){
            tmp[z++] = a[i++]; // Si el elemento del subarreglo izquierdo es menor o igual al del derecho, agregarlo al arreglo temporal
        } else {
            tmp[z++] = a[k++]; // Si el elemento del subarreglo derecho es menor, agregarlo al arreglo temporal
        }
    }
    // se mueven elementos no mezclados de sublistas
    while(i <= mid){
        tmp[z++] = a[i++]; // Agregar los elementos restantes del subarreglo izquierdo al arreglo temporal
    }

    while(k <= der){
        tmp[z++] = a[k++]; // Agregar los elementos restantes del subarreglo derecho al arreglo temporal
    }
    // copia los elementos de tmp[] al arreglo original
    for(i = izq; i <= der; ++i){
        a[i] = tmp[i - izq];
    }
    delete[] tmp;
}

void mergesort(int a[], int primero, int ultimo){
    int mitad;
    if(primero < ultimo){
        mitad  = (primero + ultimo)/2;
        mergesort(a, primero, mitad); // Ordenar la mitad izquierda
        mergesort(a, mitad + 1, ultimo); // Ordenar la mitad derecha
        mezcla(a, primero, mitad, ultimo); // Mezclar las dos mitades ordenadas
    }
}

// Quicksort
// Complejidad O(n log n) peor caso O(n^2)

int particion(int arr[], int inferior, int superior){
    int pivote = arr[superior]; // Elegir último elemento como pivote
    int i = (inferior -1);      // El indice del elemento más pequeño

    // Recorrer elementos, excepto el pivote
    for(int j = inferior; j <= superior - 1; ++j){
        if(arr[j] <= pivote){
            ++i; // Incrementar indice de elemento más pequeño
            // Intercambiar arr[i] y arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            // también se pude usar swap(arr[i], arr[j]);
        }
    }

    // Colocar pivote en posicion correcta
    int temp = arr[i + 1];
    arr[i + 1] = arr[superior];
    arr[superior] = temp;
    // swap(arr[i + 1], arr[superior]);
    return (i + 1); // Retornar el índice del pivote
}

void quicksort(int arr[], int inferior, int superior){
    if(inferior < superior){
        // pi es el índice de particion arr[pi] está en el lugar correcto
        int pi = particion(arr, inferior, superior);
        // recursivamente ordenar elmentos antes y después de la particion
        quicksort(arr, inferior, pi - 1); // subarreglo izquierdo
        quicksort(arr, pi + 1, superior); // subarreglo derecho
    }
}

// Backtracking
// Complejidad O(n!)

// algoritmo salto del caballo
/*
const int N= 8; // tamaño del tablero
// const int n = (N+1); // tamaño del tablero + 1
// int tablero [n][n]; // tablero del caballo
int d[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}; // movimientos del caballo
/*
*@param i = índice del movimiento actual
*@param x = posición x actual del caballo
*@param y = posición y actual del caballo
*@param exito = variable booleana que indica si se encontró una solución
*/
/*
void saltoCaballo(int i, int x, int y, bool& exito){
    int nx, ny; // nuevas posiciones
    int k; // movimientos del caballo

    exito = false; // inicialmente no hay solución
    k = 0; // inicializa contador de posibles (8) movimientos

    do{
        k++;                                        // suma +1 movimiento
        nx = x + d[k -1][0];                        // nueva posición x. X -> es la columna 0 de d[i][j]
        ny = y + d[k -1][1];                        // nueva posición y. Y -> es la columna 1 de d[i][j] 
        // determinar si las nuevas coordenadas son aceptables
        if((nx >= 1) && (nx <= N) &&                // nuevas coordenadas están en el rango del tablero
            (ny >= 1) && (ny <= N) &&               // Y son menores o iguales 
            (tablero[nx][ny] == 0)){                // y no han sido visitadas
                tablero[nx][ny] = i;                // marcar la casilla con el número del movimiento
            if(i < N * N){                          // Si i es menor que el total de casillas
                saltoCaballo(i + 1, nx, ny, exito); // analiza si se ha completado la solución
                if(!exito){                         // si no se encontró solución
                    tablero[nx][ny] = 0;            // desmarcar la casilla
                }
            }
        }
    } while((k<8) && !exito);                       // mientras haya movimientos y no se haya encontrado solución
}

void escribeTablero(){
    int i,j;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= N; ++j){
            cout.width(2); // ancho de campo
            cout << tablero[i][j] << " "; // imprimir valor en la casilla
        }
        cout << endl;
    }
}
*/

// Algoritmo de las n reinas
/*
int reinas[n];

bool valido(int i){ // verificar si la posición es válida
    // comprueba si la reina de la columna i es atacada por alguna
    // reina colocada anteriormente
    int r; // fila de la reina
    bool v = true; // posicion valida
    for(r = 1; r <= i - 1; ++r){
        v = v && (reinas[r] != reinas[i]); // no esté en la misma fila
        v = v && ((reinas[i] - i) != (reinas[r] - r)); // no esté en la misma diagonal 1
        v = v && ((reinas[i] + i) != (reinas[r] + r)); // no esté en la misma diagonal 2
    }
    return v;
}

void ponerReina(int i, bool& solucion){
    int k;
    solucion = false;
    k= 0; // contador de movimientos
    do{
        k++;
        reinas[i] = k; // poner reina en la columna k de la fila i
        if(valido(i)){
            if(i < N){
                ponerReina(i + 1, solucion); // intentar poner reina en la siguiente fila
                if(!solucion){ // si no se encontró solución
                    reinas[i] = 0; // quitar reina de la fila i
                }
            } else { // Todas las reinas colocadas
                solucion = true; // se encontró solución
            }
        }
    } while((k < 8) && !solucion);
}
*/


// Objetos que totalizan un peso
// Problema de la mochila - suma de subconjuntos

const int Max = 12;               // Capacidad máxima de la mochila
int nObjs = 6;                      // Número máximo de objetos
int objs[Max];                // Número de objetos

// Definición de tipo conjunto (puedes ajustar según el uso esperado)
struct conjunto {
    int elementos[Max];
    int cantidad;
    
    // Constructor
    conjunto() {
        cantidad = 0;
        for(int i = 0; i < Max; i++) {
            elementos[i] = 0;
        }
    }
    
    // Insertar un elemento en el conjunto
    void insertar(int elemento) {
        if(cantidad < Max && !pertenece(elemento)) {
            elementos[cantidad] = elemento;
            cantidad++;
        }
    }
    
    // Retirar un elemento del conjunto
    void retirar(int elemento) {
        for(int i = 0; i < cantidad; i++) {
            if(elementos[i] == elemento) {
                // Mover todos los elementos una posición hacia atrás
                for(int j = i; j < cantidad - 1; j++) {
                    elementos[j] = elementos[j + 1];
                }
                cantidad--;
                break;
            }
        }
    }
    
    // Verificar si un elemento pertenece al conjunto
    bool pertenece(int elemento) {
        for(int i = 0; i < cantidad; i++) {
            if(elementos[i] == elemento) {
                return true;
            }
        }
        return false;
    }
    
    // Limpiar el conjunto
    void limpiar() {
        cantidad = 0;
        for(int i = 0; i < Max; i++) {
            elementos[i] = 0;
        }
    }
    
    // Mostrar elementos del conjunto
    void mostrar() {
        cout << "{ ";
        for(int i = 0; i < cantidad; i++) {
            cout << elementos[i];
            if(i < cantidad - 1) cout << ", ";
        }
        cout << " }";
    }
};

conjunto bolsa;
/*
*@param obj = peso objetivo
*@param candidato = indice del peso a añadir
*@param suma = suma parcial de pesos
*@param encontrado = bandera de solución encontrada
*/
void seleccion(int obj, int candidato, int suma, bool& encontrado){
    encontrado = false;
    while((candidato < nObjs) && !encontrado){
        candidato++;
        if(suma + objs[candidato - 1] <= obj){
            bolsa.insertar(candidato);      // Objeto anotado
            suma += objs[candidato - 1];
            if(suma < obj){                 // Ensaya con siguiente objeto
                seleccion(obj, candidato, suma, encontrado); // llamada recursiva
                if(!encontrado){              // Si no se encontró solución
                    bolsa.retirar(candidato); // Desmarcar objeto
                    suma -= objs[candidato - 1];
                }
            }
        } else {
            encontrado = true; // Se encontró solución
        }
    }
}

void escribirSeleccion(){
    cout << "\nSelección de objetos: ";
    for(int candidato = 1; candidato <= nObjs; ++candidato){
        if(bolsa.pertenece(candidato)){
            cout << "\nObjeto " << candidato << "\n" << "Peso: " << objs[candidato - 1] << endl;
            bolsa.retirar(candidato); // Retirar para la próxima vez
        }
    }
    cout << endl;
}

void todasLasSoluciones(int obj, int candidato, int suma, bool& encontrado){
    while(candidato <= nObjs){
        candidato++;
        if((suma + objs[candidato - 1]) <= obj){
            bolsa.insertar(candidato);      // Objeto anotado
            suma += objs[candidato - 1];
            if(suma < obj){
                todasLasSoluciones(obj, candidato, suma, encontrado);
            } else {
                escribirSeleccion(); // Desmarcar objeto, vuelta atrás
            }
            bolsa.retirar(candidato); 
            suma -= objs[candidato - 1]; 
        }
    }
}

void probarProblemaMochila() {
    // Inicializar objetos con diferentes pesos
    int n = 6;  // 6 objetos disponibles
    objs[0] = 3;   // Objeto 1: peso 3
    objs[1] = 5;   // Objeto 2: peso 5
    objs[2] = 2;   // Objeto 3: peso 2
    objs[3] = 8;   // Objeto 4: peso 8
    objs[4] = 4;   // Objeto 5: peso 4
    objs[5] = 7;   // Objeto 6: peso 7
    
    cout << "🎯 Objetos disponibles:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "   Objeto " << (i+1) << ": peso " << objs[i] << endl;
    }
    
    int objetivo = 10;  // Peso objetivo
    // Limpiar bolsa antes de empezar
    bolsa.limpiar();
    bool encontrado = false;
    seleccion(objetivo, 0, 0, encontrado);
    if(encontrado) {
        cout << "✅ ¡Solución encontrada!" << endl;
        escribirSeleccion();
    } else {
        cout << "❌ No se encontró ninguna solución." << endl;
    }
    // Limpiar bolsa para la siguiente búsqueda
    bolsa.limpiar();

    // Buscar TODAS las soluciones
    encontrado = false;
    // Modificar todasLasSoluciones para contar soluciones
    cout << "Explorando todas las combinaciones posibles...\n" << endl;
    todasLasSoluciones(objetivo, 0, 0, encontrado);
    
    if(!encontrado) {
        cout << "❌ No se encontraron soluciones." << endl;
    }
}

// Solución óptima

// Programa del viajante:
// Joyero que carga joyas con un peso y un valor. busca que el valor sea el másico y el peso no exceda la capacidad de la maleta
// knapsack

const int M = 12;   // número máximo de objetos
int n;              // número de objetos
int pesoObjs[M];
int valorObjs[M];
conjunto actual, optimo;
int pesoMaximo;

/*
*@param i índice del objeto actual
*@param pt peso total hasta el momento
*@param va valor total hasta el momento
*@param mejorValor referencia al mejor valor encontrado
*/
void probarObjeto(int i, int pt, int va, int& mejorValor){
    if(i > n) {  // Caso base: todos los objetos fueron considerados
        if(va > mejorValor) {
            optimo = actual;        // Guardar mejor solución
            mejorValor = va;
        }
        return;
    }
    
    // OPCIÓN 1: INCLUIR el objeto i
    if(pt + pesoObjs[i - 1] <= pesoMaximo) {    // Si cabe en la mochila
        actual.insertar(i);                      // Incluir objeto
        probarObjeto(i + 1, pt + pesoObjs[i - 1], va + valorObjs[i - 1], mejorValor);
        actual.retirar(i);                       // Backtrack: quitar objeto
    }
    
    // OPCIÓN 2: NO INCLUIR el objeto i
    probarObjeto(i + 1, pt, va, mejorValor);    // Continuar sin incluir este objeto

}

void escribirOptimo(int mejor){
    cout << "\n💎 Joyas seleccionadas:" << endl;
    
    int pesoTotal = 0;
    for(int j = 1; j <= n; ++j){
        if(optimo.pertenece(j)){
            cout << "   ✅ Joya " << j << ": peso " << pesoObjs[j - 1] 
                 << " kg, valor " << valorObjs[j - 1] << " €" << endl;
            pesoTotal += pesoObjs[j - 1];
        }
    }
    
    cout << "\n📊 Resumen:" << endl;
    cout << "   💰 Valor total: " << mejor << " €" << endl;
    cout << "   ⚖️  Peso total: " << pesoTotal << " kg" << endl;
    cout << "   📦 Capacidad usada: " << pesoTotal << "/" << pesoMaximo << " kg" << endl;
}

int main(){
    // int resultado = sumaNenteros(5);
    // std::cout << "La suma de los primeros 5 enteros es: " << resultado << std::endl;

    // long fibResultado = fibonacciIterativo(5);
    // std::cout << "El 5to número de Fibonacci es: " << fibResultado << std::endl;
    // fibResultado = fibonacciRecursivo(5);
    // std::cout << "El 5to número de Fibonacci (recursivo) es: " << fibResultado << std::endl;

    // std::cout << "Alfabeto: ";
    // functionA('Z');
    // std::cout << std::endl;

    // std::cout << "Suma recursiva de dígitos de 259: " << sumaRecursiva(259) << std::endl;
    // std::cout << "Suma iterativa de dígitos de 259: " << sumaIterativa(259) << std::endl;

    // std::cout << "Máximo común divisor de 124 y 6: " << mcd(124, 6) << std::endl;

    // hanoi('A', 'B', 'C', 3);

    // Búsqueda binaria
    // double arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    // int superior = sizeof(arr)/sizeof(arr[0]) - 1;
    // int resultado = busquedaBinaria(arr, 6.6, 0, superior);
    // std::cout << "Elemento en el índice: " << resultado << std::endl;

    // Encontrar subarreglo máximo
    // complejidad O(n log n)
    // int arr[] = {1, -2, 3, 4, -5, 8};
    // int n = sizeof(arr) / sizeof(arr[0]);
    // int maxSubArray = subArrMax(arr, 0, n - 1); // superior es n -1 porque estamos usando índices
    // std::cout << "La suma del subarreglo máximo es: " << maxSubArray << std::endl;
    // sub arreglo máximo es 3 + 4 + -5 + 8 = 10

    // int arr[] = {5, 2, 9, 7, 1, 5, 6, 8, 3};
    // Mergesort
    // int n = sizeof(arr) / sizeof(arr[0]);
    // mergesort(arr, 0, n - 1);
    // std::cout << "Arreglo ordenado (mergesort): ";
    // for(int i = 0; i < n; ++i){
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    // Quicksort
    // int n2 = sizeof(arr) / sizeof(arr[0]);
    // quicksort(arr, 0, n2 - 1);
    // std::cout << "Arreglo ordenado (quicksort): ";
    // for(int i = 0; i < n2; ++i){
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    // Probar el problema de la mochila
    // probarProblemaMochila();
    
    // Snapsack Joyero
    n = 5;              // 5 joyas disponibles
    pesoMaximo = 10;    // Capacidad máxima: 10 kg

    // Inicializar pesos y valores de las joyas
    pesoObjs[0] = 1;    valorObjs[0] = 5;   // Joya 1: peso 1, valor 5
    pesoObjs[1] = 3;    valorObjs[1] = 4;   // Joya 2: peso 3, valor 4
    pesoObjs[2] = 4;    valorObjs[2] = 5;   // Joya 3: peso 4, valor 5
    pesoObjs[3] = 5;    valorObjs[3] = 6;   // Joya 4: peso 5, valor 6
    pesoObjs[4] = 1;    valorObjs[4] = 2;   // Joya 5: peso 1, valor 2
    
    // Limpiar conjuntos
    actual.limpiar();
    optimo.limpiar();

    int mejorValor = 0;
    probarObjeto(1, 0, 0, mejorValor);  // Empezar desde joya 1, peso 0, valor 0
    
    escribirOptimo(mejorValor);
    // modificar 

    return 0;
}