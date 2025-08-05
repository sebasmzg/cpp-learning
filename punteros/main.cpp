#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(){
    // ========================================
    // PUNTEROS EN C++
    // ========================================
    
    cout << "=== PUNTEROS EN C++ ===" << endl << endl;

    // Los punteros son variables que almacenan direcciones de memoria de otras variables
    // Son una herramienta que permite:
    // 1. Acceso directo a memoria.
    // 2. Manejo eficiente de datos grander
    // 3. Implementar estructuras de datos dinámicas
    // 4. Pasar por referencia, esto es, pasar la dirección de una variable a una función

    // ==========================================
    // 1. CONCEPTOS BÁSICOS
    // ==========================================
    cout << "1. CONCEPTOS BÁSICOS:" << endl;

    int numero = 42;
    cout << "Valor de 'numero': " << numero << endl;
    cout << "Dirección de 'numero' (&numero): " << &numero << endl;
    cout << "Tamaño de un puntero a int: " << sizeof(int*) << " bytes" << endl;

    // El operador '&' obtiene la dirección de memoria de una variable
    // El operador '*' se utiliza para declarar punteros y para acceder al valor apuntado por un puntero. desreferenciar.

    cout << "\n\n";

    // ==========================================
    // 2. DECLARACIÓN Y INICIALIZACIÓN
    // ==========================================
    cout << "2. DECLARACIÓN E INICIALIZACIÓN:" << endl;

    // Declaración de punteros
    int* ptr_entero;        // Punteri a entero
    double* ptr_double;     // Puntero a double
    char* ptr_caracter;     // Puntero a char

    cout << "Punteros declarados (contienen direcciones de memoria aleatorias)" << "\n";
    cout << "ptr_entero: " << &ptr_entero << "\n";
    cout << "ptr_double: " << &ptr_double << "\n";
    cout << "ptr_caracter: " << &ptr_caracter << "\n";

    cout << "\n";

    // Inicialización de punteros
    int valor = 100;
    int* ptr = &valor;      // ptr apunta a la dirección de valor

    cout << "Valor = " << valor << "\n";
    cout << "ptr = " << ptr << " (dirección de valor)" << "\n";
    cout << "*ptr = " << *ptr << " (valor apuntado por ptr)" << "\n";

    cout << "\n";

    // Puntero nulo
    int* ptr_nulo = nullptr;    // C+11 (preferido)
    //int* ptr_nulo_old = NULL;   // Estilo C (evitar)

    cout << "ptr_nulo = " << ptr_nulo << "\n";
    // imprime 0 o nullptr, indicando que no apunta a ninguna dirección válida

    cout << "\n\n";

    // ==========================================
    // 3. OPERADORES DE PUNTEROS
    // ==========================================
    cout << "3. OPERADORES DE PUNTEROS:" << "\n";

    int x = 25;
    int* p = &x;

    cout << "Variable x = " << x << "\n";
    cout << "Dirección de x (&x) = " << &x << "\n";
    cout << "Puntero p = " << p << " (almacena la dirección de x)" << "\n";
    // Será la misma dirección que &x porque p apunta a x 
    cout << "Valor apuntado (*p) = " << *p << "\n";

    // Modificar el calor a través del puntero
    *p = 50;
    cout << "\nDespués de *p = 50: " << "\n";
    cout << "x = " << x << " (cambio a través del puntero)" << endl;
    cout << "*p = " << *p << "\n";

    cout << "\n" << std::flush;

    // ==========================================
    // 4. PUNTEROS Y ARRAYS
    // ==========================================
    cout << "4. PUNTEROS Y ARRAYS:" << "\n";

    int numeros[] = {10,20,30,40,50};
    int* ptr_array = numeros; // El nombre del array es un puntero al primer elemento, entonces la dirección del array 'numeros' es la dirección del primer elemento

    cout << "Array numeros: ";
    for(int i = 0; i < 5; ++i){
        cout << numeros[i] << " ";
    }
    cout << "\n";

    cout << "Acceso con punteros:\n";
    cout << "ptr_array[0] = " << ptr_array[0] << "\n";
    cout << "*(ptr_array + 0) = " << *(ptr_array + 0) << "\n";
    cout << "*(ptr_array + 1) = " << *(ptr_array + 1) << "\n";
    cout << "*(ptr_array + 2) = " << *(ptr_array + 2) << "\n";
    // *(ptr_array) es equivalente a ptr_array[0], *(ptr_array + 1) es equivalente a ptr_array[1], etc.
    cout << "\n";

    // Diferencia entre direcciones
    cout << "Diferencia entre ptr_array+1 y ptr_array = " << ((ptr_array + 1) - ptr_array) << " elementos" << "\n";
    cout << "\n";

    cout << "Dirección memoria de elementos del array:\n";
    for(int i = 0; i < 5; ++i){
        cout << "Dirección de numeros[" << i << "] = " << &numeros[i] << "\n";
    }
    cout << "Dirección de numeros[] = " << &numeros << " es equivalente a la del primer elemento (numero[0])." << "\n";

    cout << "\n" << std::flush;

    // ==========================================
    // 5. PUNTEROS Y STRINGS
    // ==========================================
    cout << "5. PUNTEROS Y STRINGS:" << "\n";

    // String al estilo C (array de caracteres)
    char mensaje[] = "Hola";
    char* ptr_mensaje =  mensaje; // Puntero al primer carácter del string

    cout << "String: " << mensaje << "\n";
    cout << "A través del puntero: " << ptr_mensaje << "\n";
    
    cout << "Acceso a caracteres:\n";
    for(int i = 0; mensaje[i] != '\0'; ++i){
        // '\0' es el carácter nulo que indica el final de la cadena
        cout << "mensaje[" << i << "] = '" << mensaje[i] << "'" << "\n";
    }

    // String literal (solo lectura)
    const char* ptr_literal = "Mundo";
    cout << "String literal: " << ptr_literal << "\n";
    // No se puede modificar un string literal, es de solo lectura
    // ptr_literal[0] = 'm'; // ¡ERROR! No se puede modificar un string literal
    cout << "\n" << std::flush;

    // ==========================================
    // 6. PUNTEROS A PUNTEROS (DOUBLE POINTERS)
    // ==========================================
    cout << "6. PUNTEROS A PUNTEROS:" << "\n";

    int numero_original =123;
    int* ptr_simple = &numero_original; // Puntero simple
    int** ptr_doble = &ptr_simple; // Puntero a puntero

    cout << "numero_original = " << numero_original << "\n";
    cout << "ptr_simple = " << ptr_simple << " (dirección de numero_original)" << "\n";
    cout << "*ptr_simple = " << *ptr_simple << " (valor apuntado por ptr_simple)" << "\n";
    cout << "ptr_doble = " << ptr_doble << " (dirección de ptr_simple)" << "\n";
    cout << "*ptr_doble = " << *ptr_doble << " (valor de ptr_simple)" << "\n";
    cout << "**ptr_doble = " << **ptr_doble << " (valor apuntado por ptr_doble, que es numero_original)" << "\n";


    cout << "\n" << std::flush;

    // ==========================================
    // 7. PUNTEROS Y FUNCIONES
    // ==========================================
    cout << "7. PUNTEROS Y FUNCIONES:" << "\n";

    // Función que intercambia dos números usando punteros
    auto intercambiar = [](int* a, int* b){ // []() es una lambda function que recibe dos punteros a enteros
        // lambda es una función anónima que se puede definir en el lugar
        int temp = *a; // Guardar el valor apuntado por a
        *a = *b;       // Asignar el valor apuntado por b a a
        *b = temp;    // Asignar el valor guardado a b
    };

    int num1 = 10, num2 = 20;
    cout << "Antes de intercambiar: num1 = " << num1 << ", num2 = " << num2 << "\n";

    intercambiar(&num1, &num2); // Pasar las direcciones de num1 y num2

    cout << "Después de intercambiar: num1 = " << num1 << ", num2 = " << num2 << "\n";

    // Hay dos formas de pasar parámetros a una función:
    // 1. Por valor: se pasa una copia del valor, no se modifica el original
    // 2. Por referencia: se pasa la dirección de memoria, se puede modificar
    // En este caso, se usa por referencia para modificar los valores originales

    cout << "\n" << std::flush;

    // ==========================================
    // 8. MEMORIA DINÁMICA
    // ==========================================
    cout << "8. MEMORIA DINÁMICA:" << "\n";

    // Asignación dinámica con new
    int* ptr_dinamico = new int(99); // Reservar memoria para un entero y asignar el valor 99
    // new reserva memoria en el heap y devuelve un puntero a esa memoria
    cout << "valor dinámico = " << *ptr_dinamico << "\n";
    cout << "Dirección de memoria dinámica: " << ptr_dinamico << "\n";

    // Modificar el valor
    *ptr_dinamico = 200;
    cout << "Nuevo valor dinámico = " << *ptr_dinamico << "\n";

    // IMPORTANTE: Siempre liberar la memoria dinámica con delete
    delete ptr_dinamico; // Libera la memoria reservada
    ptr_dinamico = nullptr; // Evitar puntero colgante

    cout << "Memoria dinámica liberada, ptr_dinamico ahora es: " << ptr_dinamico << "\n";
    // delete libera la memoria reservada por new, evitando fugas de memoria
    // Es una buena práctica asignar nullptr después de liberar para evitar punteros colgantes
    // deberá imprimir 0 o nullptr, indicando que no apunta a ninguna dirección válida

    cout << "\n" << std::flush;

    // Array dinámico
    int tamano = 5;
    int* array_dinamico = new int[tamano]; // Reservar memoria para un array de 5 enteros

    // Inicializar el array dinámico
    for(int i = 0; i < tamano; ++i){
        array_dinamico[i] = (i + 1) * 10; // Asignar valores
    }

    cout << "Array dinámico: ";
    for(int i = 0; i < tamano; ++i){
        cout << array_dinamico[i] << " "; // Imprimir valores
    }
    cout << "\n";

    // Liberar memoria del array dinámico
    delete[] array_dinamico; // Usar delete[] para liberar memoria de arrays dinámicos
    array_dinamico = nullptr; // Evitar puntero colgante

    cout << "Memoria del array dinámico liberada, array_dinamico ahora es: " << array_dinamico << "\n";
    cout << "\n" << std::flush;

    // ==========================================
    // 9. PUNTEROS INTELIGENTES (SMART POINTERS)
    // ==========================================
    cout << "9. PUNTEROS INTELIGENTES (INTRODUCCIÓN):" << "\n";
    cout << "Los punteros inteligentes manejan automáticamente la memoria:" << "\n";
    cout << "• std::unique_ptr - Propiedad única" << "\n"; // Un puntero inteligente que asegura que solo un puntero lo posea
    cout << "• std::shared_ptr - Propiedad compartida" << "\n"; // Varios punteros pueden poseer el mismo recurso
    cout << "• std::weak_ptr - Referencia débil" << "\n"; // No afecta el conteo de referencias, esto quiere decir que no evita que el recurso sea liberado si no hay más punteros compartidos apuntando a él

    // Ejemplo simple con unique_ptr (C++11)
    // std::unique_ptr<int> smart_ptr = std::make_unique<int>(42);

    cout << "Nota: Los punteros inteligentes requieren #include <memory>" << "\n";
    cout << "Son la forma moderna y segura de manejar memoria dinámica" << "\n";

    cout << "\n" << std::flush;

    // ==========================================
    // 10. ARITMÉTICA DE PUNTEROS
    // ==========================================
    cout << "10. ARITMÉTICA DE PUNTEROS:" << "\n";

    int datos[] = {1,2,3,4,5};
    int* ptr_inicio = datos; // Puntero al inicio del array
    int* ptr_fin = datos + 4; // Puntero al final del array

    cout << "Array datos: ";
    for(int i = 0; i < 5; ++i){
        cout << datos[i] << " ";    
    }
    cout << "\n";

    cout << "Recorrido con aritmética de punteros:\n";
    for(int* ptr = ptr_inicio; ptr <= ptr_fin; ++ptr){
        cout << "Valor: " << *ptr << ", Dirección: " << ptr << "\n";
    }

    cout << "Diferencia entre punteros: " << (ptr_fin - ptr_inicio) << " elementos\n";
    // La diferencia entre dos punteros apunta a la cantidad de elementos entre ellos, no a la diferencia de bytes
    // Por ejemplo, si ptr_fin apunta al quinto elemento y ptr_inicio apunta al primer elemento, la diferencia será 4, ya que hay 4 elementos entre ellos.

    cout << "\n" << std::flush;

    // ==========================================
    // 11. PUNTEROS CONST
    // ==========================================
    cout << "11. PUNTEROS CONST:" << "\n";

    int variable1 = 10;
    int variable2 = 20;

    // Puntero a constante: no se puede modificar el valor apuntado
    const int* ptr_a_const = &variable1; // Puntero a int constante
    cout << "*ptr_a_const: " << *ptr_a_const << "\n";
    // *ptr_a_const = 15; // ERROR: no se puede modificar el valor apuntado por un puntero a constante
    ptr_a_const = &variable2; // Se puede cambiar a apuntar a otra dirección
    cout << "Ahora ptr_a_const apunta a variable2: " << *ptr_a_const << "\n";

    // puntero constante: no se puede cambiar la dirección a la que apunta
    int* const ptr_const = &variable1; // Puntero constante a int
    cout << "*ptr_const: " << *ptr_const << "\n";
    *ptr_const = 15; // Se puede modificar el valor apuntado
    // ptr_const = &variable2; // ERROR: no se puede cambiar la dirección de un puntero constante
    cout << "Después de modificar *ptr_const: " << *ptr_const << "\n";

    // Puntero constante a constante: no se puede modificar ni el valor apuntado ni la dirección
    const int* const ptr_const_a_const = &variable1; // Puntero constante a int constante
    cout << "*ptr_const_a_const: " << *ptr_const_a_const << "\n";
    // *ptr_const_a_const = 20; // ERROR: no se puede modificar el valor apuntado
    // ptr_const_a_const = &variable2; // ERROR: no se puede cambiar la dirección
    cout << "ptr_const_a_const sigue apuntando a variable1: " << *ptr_const_a_const << "\n";

    cout << "\n" << std::flush;

    // ==========================================
    // 12. EJEMPLOS PRÁCTICOS
    // ==========================================
    cout << "12. EJEMPLOS PRÁCTICOS:" << "\n";

    cout << "Ejemplo 1: Encontrar máximo en un array:\n";

    auto encontrar_maximo = [](int* arr, int tamano) -> int* { // -> significa que la funcion devuelve un puntero a int. -> es algo similar a la notacion de promesa de retorno de las funciones
        if(tamano <= 0) return nullptr; // Si el tamaño es 0 o negativo, retornar nullptr

        int* ptr_max = arr; // Inicializar puntero al primer elemento
        for(int i = 1; i < tamano; ++i){
            if(*(arr + i) > *ptr_max){ // *(arr + i) es equivalente a arr[i]
                ptr_max = arr + i; // Actualizar puntero al nuevo máximo
            }
        }
        return ptr_max; // Retornar puntero al máximo encontrado
    };

    int valores[] = {3,7, 9,1,8,2};
    int tamano_valores = sizeof(valores) / sizeof(valores[0]); // Calcular el tamaño del array 
    // divide el tamaño total del array entre el tamaño de un elemento para obtener la cantidad de elementos

    cout << "Array de valores: ";
    for(int i = 0; i < tamano_valores; ++i){
        cout << valores[i] << " ";
    }
    cout << "\n";

    int* ptr_max = encontrar_maximo(valores, tamano_valores);
    if(ptr_max != nullptr){
        cout << "El valor máximo es: " << *ptr_max << "\n";
        cout << "Se encuentra en la dirección: " << ptr_max << "\n";
    } else {
        cout << "Array vacío o inválido.\n";
    }

    cout << "\n";

    cout << "Ejemplo 2: Invertir un array:\n";

    auto invertir_array = [](int* arr, int tamano){
        int* inicio = arr; // Puntero al inicio del array
        int* fin = arr + tamano - 1; // Puntero al final

        while (inicio < fin){
            // intercambiar los valores apuntados por inicio y fin
            int temp = *inicio;
            *inicio = *fin;
            *fin = temp;
            inicio++; // Mover puntero de inicio hacia adelante
            fin--; // Mover puntero de fin hacia atrás
        };
    };

    cout << "\nAntes de invertir: ";
    for (int i = 0; i < tamano_valores; i++) {
        cout << valores[i] << " ";
    }
    cout << endl;
    
    invertir_array(valores, tamano_valores);
    
    cout << "Después de invertir: ";
    for (int i = 0; i < tamano_valores; i++) {
        cout << valores[i] << " ";
    }

    // Ejemplo 3: mover un elementos de un array x posiciones a la derecha si el valor es positivo
    // y a la izquierda si es negativo

    cout << "\n\nEjemplo 3: Mover elementos de un array:\n";
    auto mover_elementos = [](int* arr, int tamano, int posiciones){
        if(tamano <= 0 || posiciones == 0) return; // Si el tamaño es 0 o posiciones es 0, no hacer nada
        posiciones = ((posiciones % tamano) + tamano) % tamano; // Normalizar posiciones para evitar movimientos innecesarios
        // el calculo de posiciones asegura que si es negativo, se convierte en un desplazamiento válido hacia la izquierda

        int* ptr_temp = new int[tamano]; // Reservar memoria temporal para el array

        // Copiar el array original al temporal
        for(int i = 0; i < tamano; ++i){
            int nueva_pos = (i + posiciones) % tamano; // Calcular la nueva posición
            ptr_temp[nueva_pos] = arr[i];
        }

        // Mover los elementos
        for(int i = 0; i < tamano; ++i){
            arr[i] = ptr_temp[i]; // Copiar de vuelta al array original
        }

        delete[] ptr_temp; // Liberar memoria temporal

    };
    int valores_mover[] = {1, -2, 3, -4, 5};
    int tamano_valores_mover = sizeof(valores_mover) / sizeof(valores_mover[0]); // Calcular el tamaño del array
    cout << "Array original: ";
    for(int i = 0; i < tamano_valores_mover; ++i){
        cout << valores_mover[i] << " ";
    }
    cout << "\n";
    int posiciones = 2; // Mover 2 posiciones a la derecha
    mover_elementos(valores_mover, tamano_valores_mover, posiciones);
    cout << "Después de mover " << posiciones << " posiciones a la derecha: ";
    for(int i = 0; i < tamano_valores_mover; ++i){
        cout << valores_mover[i] << " ";
    }
    cout << "\n";
    posiciones = -4; // Mover 2 posiciones a la izquierda
    mover_elementos(valores_mover, tamano_valores_mover, posiciones);
    cout << "Después de mover " << posiciones << " posiciones a la izquierda: ";
    for(int i = 0; i < tamano_valores_mover; ++i){
        cout << valores_mover[i] << " ";
    }
    cout << "\n";

    cout << "\n" << std::flush;

    // ==========================================
    // 13. ERRORES COMUNES Y CÓMO EVITARLOS
    // ==========================================
    cout << "13. ERRORES COMUNES:" << endl;
    
    cout << "❌ ERRORES A EVITAR:" << endl;
    cout << "1. Usar punteros no inicializados" << endl;
    cout << "2. Acceso fuera de límites en arrays" << endl;
    cout << "3. Olvidar usar delete después de new" << endl;
    cout << "4. Usar delete en lugar de delete[] para arrays" << endl;
    cout << "5. Acceder a memoria liberada (dangling pointers)" << endl;
    cout << "6. Doble delete de la misma memoria" << endl;
    cout << "7. Memory leaks (no liberar memoria asignada)" << endl;
    
    cout << "\n✅ BUENAS PRÁCTICAS:" << endl;
    cout << "1. Inicializar punteros siempre (nullptr si no hay valor)" << endl;
    cout << "2. Verificar nullptr antes de usar punteros" << endl;
    cout << "3. Asignar nullptr después de delete" << endl;
    cout << "4. Usar punteros inteligentes en C++ moderno" << endl;
    cout << "5. Evitar aritmética de punteros innecesaria" << endl;
    cout << "6. Usar const cuando sea apropiado" << endl;
    cout << "7. Validar límites de arrays" << endl;
    
    cout << endl;
    
    // ==========================================
    // 14. CASOS DE USO COMUNES
    // ==========================================
    cout << "14. CASOS DE USO COMUNES:" << endl;
    cout << "• Pasar arrays a funciones" << endl;
    cout << "• Modificar variables en funciones (paso por referencia)" << endl;
    cout << "• Implementar estructuras de datos dinámicas (listas, árboles)" << endl;
    cout << "• Gestión eficiente de memoria para objetos grandes" << endl;
    cout << "• Interfaz con APIs de C" << endl;
    cout << "• Implementar polimorfismo (punteros a clases base)" << endl;
    cout << "• Crear arrays de tamaño variable en tiempo de ejecución" << endl;
    
    cout << endl;
    
    // ==========================================
    // 15. COMPARACIÓN: PUNTEROS VS REFERENCIAS
    // ==========================================
    cout << "15. PUNTEROS VS REFERENCIAS:" << endl;
    cout << "┌─────────────┬─────────────────┬─────────────────┐" << endl;
    cout << "│ ASPECTO     │    PUNTEROS     │   REFERENCIAS   │" << endl;
    cout << "├─────────────┼─────────────────┼─────────────────┤" << endl;
    cout << "│ Sintaxis    │ int* ptr; *ptr  │ int& ref = var; │" << endl;
    cout << "│ Nulos       │ Pueden ser null │ No pueden       │" << endl;
    cout << "│ Reasignación│ Sí              │ No              │" << endl;
    cout << "│ Aritmética  │ Sí              │ No              │" << endl;
    cout << "│ Memoria     │ Ocupan espacio  │ No (alias)      │" << endl;
    cout << "│ Seguridad   │ Menos seguro    │ Más seguro      │" << endl;
    cout << "└─────────────┴─────────────────┴─────────────────┘" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE SINTAXIS
    // ==========================================
    cout << "RESUMEN DE SINTAXIS:" << endl;
    cout << "int* ptr;              // Declarar puntero" << endl;
    cout << "ptr = &variable;       // Asignar dirección" << endl;
    cout << "*ptr;                  // Desreferenciar (obtener valor)" << endl;
    cout << "&variable;             // Obtener dirección" << endl;
    cout << "ptr++;                 // Aritmética de punteros" << endl;
    cout << "new int(42);           // Asignación dinámica" << endl;
    cout << "delete ptr;            // Liberar memoria" << endl;
    cout << "delete[] array_ptr;    // Liberar array dinámico" << endl;
    cout << "ptr = nullptr;         // Asignar puntero nulo" << endl;
    
    return 0;
}