// Tipos de Algoritmos de Ordenación Interna: Se dividen en dos grupos principales:
// • Métodos Directos (Básicos): Burbuja, Selección, Inserción. Son eficientes para listas pequeñas debido a su simplicidad, pero ineficaces para listas grandes.
// • Métodos Indirectos (Avanzados): Shell, Quicksort, Mergesort, Radixsort, Binsort, Heapsort. Son más eficientes para listas grandes.
// Algoritmos de comparación (útiles para strings): Mergesort, quicksort, heapsort, insertion, selection.
// Algoritmos de conteo/no comparativos: Counting(caracteres), radix(muy común strings, aplicando en cada carácter), bucket.
// Eficiencia Común: La complejidad de los algoritmos de burbuja, inserción y selección es O(n²), mientras que la de Heapsort, Radixsort, Mergesort y Quicksort es O(n log n).

#include <iostream>
#include <vector>
#include <algorithm>

// INTERCAMBIO
void intercambiar(int& x, int& y){
    int aux = x;
    x = y;
    y = aux;
}

// PROBAR ORDENACIONES
void probarOrdenacion(void (*algoritmo)(int[],int), const char* nombre){
    int arr[] = {5, 2, 3, 1, 8, 13, 0, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "\n" << nombre << ":" << std::endl;
    std::cout << "Original: ";
    for(int i = 0; i < n; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    algoritmo(arr, n);  // Llamar al algoritmo de ordenación
    
    std::cout << "Ordenado: ";
    for(int i = 0; i < n; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/*
*@param a[] Arreglo a ordenar
*@param n Tamaño del arreglo
*/
void ordIntercambio(int a[], int n){
    for(int i = 0; i < n - 1; ++i){
        // Situa el minimo de a[i+1]...a[n -1] en a[i]
        for(int j = i + 1; j < n; ++j){
            if(a[i] > a[j]){ // < salida descendente > salida ascendente
                intercambiar(a[i], a[j]);
            }
        }
    }
}


// SELECCIÓN
void seleccion(int a[], int n){
    int indiceMenor;
        // Ordenar a[0]..a[n-2] y a[n-1] en cada pasada
    for(int i = 0; i < n - 1; ++i){
        // comienzo de exploración en indice i
        indiceMenor = i;
        // j explora sublista a[i+1]..a[n-1]
        for(int j = i + 1; j < n; ++j){
            if(a[j] < a[indiceMenor]){ // < ascendente > salida descendente
                indiceMenor = j;
                // Situa elemento más pequeño en a[i]
            }
        }
        if(i != indiceMenor){
            intercambiar(a[i], a[indiceMenor]);
        }
    }
}

// INSERCIÓN
void insercion(int a[], int n){
    for(int i = 1; i < n; ++i){
        /* indice j para explorar sublista a[i-1]..a[0] buscando la posicion
        correcta del elemento destino*/
        int j = i;
        int aux = a[i];
        while(j > 0 && aux < a[j-1]){
            // Desplazar elementos hacia arriba para hacer espacio
            a[j] = a[j-1];
            --j; // Desplazar el índice hacia la izquierda
        }
        a[j] = aux; // Insertar el elemento en su posición correcta
    }
}

// BURBUJA
void burbuja(int a[], int n){
    bool interruptor = true;
    int pasada;
    // Bucle externo controla la cantidad de pasadas
    for(pasada = 0; pasada < n -1 && interruptor; ++pasada){
        interruptor = false; // suponer que no hay intercambios
        for(int j = 0; j < n - pasada - 1; ++j){
            if(a[j] > a[j + 1]){ // > ascendente
                interruptor = true; // Se realizó un intercambio
                intercambiar(a[j], a[j + 1]);
            }
        }
    }
}

// SHELL
// ordenación por inseción con incrementos decrecientes - mejora de inserción
// Salto inicial es igual a n/2
// Divisiones en grupos de 2 por saltos decreciente
// finaliza cuando el salto es 1
void ordenacionShell(int a[], int n){
    int salto = n/2; // Inicializa el salto
    while(salto > 0){ // Mientras el salto sea mayor que 0, finaliza cuando salto sea 1
        for(int i = salto; i < n; ++i){ // Explora elementos desde el índice "salto"
            int j = i - salto;
            while(j >= 0){ // j es el índice del primer elemento del subgrupo
                int k = j + salto; // k es el índice del segundo elemento del subgrupo
                if(a[j] <= a[k]){
                    j = -1;         // Par de elementos ordenado
                } else {
                    intercambiar(a[j], a[k]);
                    j -= salto;     // Seguir comparando en el subgrupo
                }
            }
        }
        salto /= 2; // Reduce el salto
    }
}

// QUICKSORT
// O(n log n)
void quicksort(int a[], int primero, int ultimo){
    int i,j, central;
    int pivote;
    central = (primero + ultimo)/2;
    pivote = a[central]; // pivote es el elemento central
    i = primero;
    j = ultimo;
    do{
        while(a[i] < pivote) ++i; // buscar elemento menor que pivote
        while(a[j] > pivote) --j; // buscar elemento mayor que pivote
        if(i <= j){
            intercambiar(a[i], a[j]);
            ++i;
            --j;
        }
    } while(i <= j);
    if(primero < j){
        quicksort(a, primero, j); // Ordenar sublista izquierda
    }
    if(i < ultimo){
        quicksort(a, i, ultimo); // Ordenar sublista derecha
    }
}
void quicksortWrapper(int a[], int n){
    quicksort(a, 0, n - 1);  // Llamar quicksort con parámetros completos
}

// COUNTING SORT
void countingsort(std::vector<int>& arr, int maxVal){
    int n = arr.size();
    // inicializar arreglo
    std::vector<int> count(maxVal + 1, 0); // rango de 0 a maxVal
    // Contar ocurrencias de cada número
    for(int i = 0; i < n; ++i){
        count[arr[i]]++;
    }
    // Reconstruir el arreglo ordenado
    int index = 0;
    for(int i = 0; i <= maxVal; ++i){
        while(count[i] > 0){
            arr[index++] = i;
            count[i]--; // Reducir la cuenta
        }
    }
}
void pruebaCountingSort(){
    std::vector<int> arr = {4, 2, 2, 81, 13, 23, 1, 101, 201, 39, 1052};
    int maxVal = *max_element(arr.begin(), arr.end());
    countingsort(arr, maxVal);
    for(int val : arr){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// BINSORT - BUCKETSORT
// O(n)

// Estructura estudiante
/*
struct Estudiante {
    string nombre;
    int nota; // clave
};
*/
void bucketsort(std::vector<double>& arr){
    int n = arr.size();
    // int RANGO = 101; // notas posibles en [0..100]
    // Creaer n cubetas (vectores vacíos)
    std::vector<std::vector<double>> buckets(n);
    // st::list<Estudiante>> buckets(rango) 

    // Distribuir los elementos en las cubetas
    // Formula indice bucket = arr[i] * n
    for(int i = 0; i < n; ++i){
    // for(auto& e : arr)
        // buckets[e.nota].push_back(e);
        int index = n * arr[i]; // arr[i] = 0.5 n = 10 index= 5
        buckets[index].push_back(arr[i]);
    }
    // Ordenar cada bucket de forma individual
    for(int i = 0; i < n; ++i){
        //para listas enlazadas:
        /*
        buckets[i].sort([](const Estudiante& a, const Estudiante& b) {
            return a.nombre < b.nombre;
        });
        */

        // Usando inserción
        for(size_t j = 1; j < buckets[i].size(); ++j){
            int k = j;
            double aux = buckets[i][k];
            while(k > 0 && aux < buckets[i][k-1]){
                // Desplazar elementos hacia arriba para hacer espacio
                buckets[i][k] = buckets[i][k-1];
                --k; // Desplazar el índice hacia la izquierda
            }
            buckets[i][k] = aux; // Insertar el elemento en su posición correcta
        }
    }
    // Concatenar todos los buckets en arr
    int index = 0;
    for(int i = 0; i < n; ++i){
        // Para listas enlazadas:
        // n sería RANGO
        /*
        for (auto& e : buckets[i]) {
            arr[index++] = e;
        }
        */
        for(double val : buckets[i]){
            arr[index++] = val;
        }
    }
}
void probarBucketsort(){
    /*
    vector<Estudiante> estudiantes = {
        {"Ana", 85}, {"Luis", 72}, {"Maria", 94}, {"Jose", 72},
        {"Elena", 85}, {"Pedro", 39}, {"Lucia", 94}, {"Carlos", 21}
    };
    */
    std::vector<double> arr = {0.5, 0, 0.75, 0.72, 0.2, 0.9, 0.1, 0.8, 75};
    bucketsort(arr);
    for(double val : arr){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// RADIX SORT
void countingsortForRadix(std::vector<int>& arr, int exp){
    int n = arr.size();
    std::vector<int> salida(n); // arreglo temporal ordenado
    int conteo[10] = {0}; // 10 posiboes digitos (0-9)
    // Contar ocurrencia de cada digito
    for(int i = 0; i < n; ++i){
        int digito = (arr[i] / exp) % 10;
        conteo[digito]++;
    }

    // Convertir a posiciones acumuladas
    for(int i = 1; i < 10; ++i){
        conteo[i] += conteo[i - 1];
    }

    // Construir salida (recorremos al revés por estabilidad)
    for(int i = n - 1; i >= 0; --i){
        int digito = (arr[i] / exp) % 10;
        salida[conteo[digito] - 1] = arr[i];
        conteo[digito]--;
    }

    // copiar salida al arreglo original
    for(int i = 0; i < n; ++i){
        arr[i] = salida[i];
    }
}
void radixsort(std::vector<int>& arr){
    // encontrar valor maximo
    int maxVal = *max_element(arr.begin(), arr.end());
    // Ordenar por cada digito usando counting sort
    for(int exp = 1; maxVal / exp > 0; exp *= 10){ // exp es la posición del dígito actual
        // maxVal / exp da como resultado el dígito actual, por ejemplo si maxVal=345 y exp=10, el dígito actual es 4
        // exp *= 10 para avanzar a la siguiente posición del dígito
        countingsortForRadix(arr, exp);
    }
}
void pruebaRadixSort(){
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    radixsort(arr);
    for(int val : arr){
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main(){
    // probarOrdenacion(burbuja, "Burbuja");
    // probarOrdenacion(insercion, "Inserción");
    // probarOrdenacion(seleccion, "Selección");
    // probarOrdenacion(ordenacionShell, "Shell");
    // probarOrdenacion(quicksortWrapper, "Quicksort");
    // pruebaCountingSort();
    // probarBucketsort();
    pruebaRadixSort();
    return 0;
}