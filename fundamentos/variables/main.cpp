#include <iostream>
using std::cout; 
using std::endl; 

int main(){
    // ========================================
    // INTRODUCCIÓN A VARIABLES EN C++
    // ========================================
    
    cout << "=== INTRODUCCIÓN A VARIABLES EN C++ ===" << endl << endl;
    
    // ¿QUÉ ES UNA VARIABLE?
    // Una variable es un espacio en memoria que tiene un nombre y puede almacenar un valor
    // Las variables en C++ deben ser declaradas antes de usarse
    
    // 1. DECLARACIÓN DE VARIABLES
    cout << "1. DECLARACIÓN DE VARIABLES:" << endl;
    
    // Sintaxis: tipo_de_dato nombre_variable;
    int edad;                    // Declaraciones sin inicializar
    double salario;              
    char inicial;                
    bool es_estudiante;          
    
    cout << "Variables declaradas (sin inicializar)" << endl;
    cout << "CUIDADO: Variables no inicializadas contienen valores basura!" << endl << endl;
    
    // 2. INICIALIZACIÓN DE VARIABLES
    cout << "2. INICIALIZACIÓN DE VARIABLES:" << endl;
    
    // Forma 1: Inicialización en la declaración
    int numero = 42;             // Inicialización directa
    double pi = 3.14159;         
    char letra = 'A';            
    u_int8_t activo = true;          
    
    cout << "numero = " << numero << endl;
    cout << "pi = " << pi << endl;
    cout << "letra = " << letra << endl;
    cout << "activo = " << activo << endl << endl;
    
    // Forma 2: Inicialización después de la declaración
    edad = 25;                   // Asignación de valor
    salario = 50000.50;          
    inicial = 'J';               
    es_estudiante = 0;       // Buena practica usar valores binarios (0 o 1) para variables booleanas. son tipo uint8_t

    cout << "Después de la asignación:" << endl;
    cout << "edad = " << edad << endl;
    cout << "salario = " << salario << endl;
    cout << "inicial = " << inicial << endl;
    cout << "es_estudiante = " << es_estudiante << endl << endl;
    
    // 3. MÚLTIPLES DECLARACIONES
    cout << "3. MÚLTIPLES DECLARACIONES:" << endl;
    
    // Declarar múltiples variables del mismo tipo en una línea
    int a, b, c;                 // Tres variables int sin inicializar
    int x = 10, y = 20, z = 30;  // Tres variables int inicializadas
    
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl << endl;
    
    // 4. CONSTANTES
    cout << "4. CONSTANTES:" << endl;
    
    // Las constantes no pueden cambiar su valor después de la inicialización
    const int DIAS_SEMANA = 7;          // Constante entera
    const double GRAVEDAD = 9.81;       // Constante decimal
    const char GRADO = 'C';             // Constante carácter
    
    cout << "DIAS_SEMANA = " << DIAS_SEMANA << endl;
    cout << "GRAVEDAD = " << GRAVEDAD << endl;
    cout << "GRADO = " << GRADO << endl << endl;
    
    // DIAS_SEMANA = 8; // ¡ERROR! No se puede modificar una constante
    
    // 5. REGLAS PARA NOMBRES DE VARIABLES
    cout << "5. REGLAS PARA NOMBRES DE VARIABLES:" << endl;
    
    // Nombres válidos:
    int mi_edad = 30;            // Guión bajo permitido
    int edad2 = 25;              // Números al final permitidos
    int MiVariable = 100;        // Mayúsculas permitidas
    int _variable = 50;          // Puede empezar con guión bajo
    
    // Nombres NO válidos (comentados para evitar errores):
    // int 2edad = 25;           // NO puede empezar con número
    // int mi-edad = 30;         // NO se permiten guiones
    // int int = 10;             // NO se pueden usar palabras reservadas
    // int mi edad = 20;         // NO se permiten espacios
    
    cout << "mi_edad = " << mi_edad << endl;
    cout << "edad2 = " << edad2 << endl;
    cout << "MiVariable = " << MiVariable << endl;
    cout << "_variable = " << _variable << endl << endl;
    
    // 6. ALCANCE (SCOPE) DE VARIABLES
    cout << "6. ALCANCE DE VARIABLES:" << endl;
    
    int variable_global = 100;   // Variable en el scope de main
    
    {
        // Bloque interno - nuevo scope
        int variable_local = 200;    // Solo existe dentro de este bloque
        cout << "Dentro del bloque:" << endl;
        cout << "variable_global = " << variable_global << endl;  // Accesible
        cout << "variable_local = " << variable_local << endl;    // Accesible
    }
    
    cout << "Fuera del bloque:" << endl;
    cout << "variable_global = " << variable_global << endl;      // Accesible
    // cout << variable_local << endl;  // ¡ERROR! No accesible fuera del bloque
    
    cout << endl;
    
    // 6.1. REDECLARACIÓN DE VARIABLES
    cout << "6.1. REDECLARACIÓN DE VARIABLES:" << endl;
    
    // ¡IMPORTANTE! No se puede redeclarar una variable en el mismo scope
    int numero_original = 100;
    cout << "numero_original = " << numero_original << endl;

    // int numero_original = 200;  // ¡ERROR! Redeclaración en el mismo scope

    // Sin embargo, SÍ se puede reasignar un nuevo valor
    numero_original = 200;  // ✅ Correcto: reasignación
    cout << "numero_original después de reasignar = " << numero_original << endl;
    
    // Pero en diferentes scopes SÍ se puede "redeclarar" (shadowing)
    {
        int numero_original = 300;  // ✅ Correcto: diferente scope (shadowing)
        cout << "numero_original dentro del bloque = " << numero_original << endl;
        // Esta variable "oculta" la variable del scope exterior
    }
    
    cout << "numero_original fuera del bloque = " << numero_original << endl;
    cout << "La variable exterior mantiene su valor original" << endl;
    
    // Otro ejemplo de shadowing
    {
        int variable_global = 999;  // Sombrea la variable_global del scope principal
        cout << "variable_global sombreada = " << variable_global << endl;
    }
    cout << "variable_global original = " << variable_global << endl;
    
    cout << endl;
    
    // CASOS DE ERROR COMUNES:
    cout << "CASOS DE ERROR COMUNES:" << endl;
    
    // ❌ Error 1: Redeclaración en el mismo scope
    // int contador = 10;     // Ya está declarado arriba
    // int contador = 20;     // ¡ERROR DE COMPILACIÓN!
    
    // ❌ Error 2: Usar variable antes de declararla
    // nueva_variable = 50;   // ¡ERROR! Variable no declarada
    // int nueva_variable;
    
    // ❌ Error 3: Redeclarar con diferente tipo
    // double contador;       // ¡ERROR! Ya existe como int
    
    cout << "• No se puede redeclarar en el mismo scope" << endl;
    cout << "• Sí se puede hacer shadowing en scopes diferentes" << endl;
    cout << "• El shadowing puede confundir, usarlo con cuidado" << endl;
    
    cout << endl;
    
    // 7. MODIFICACIÓN DE VARIABLES
    cout << "7. MODIFICACIÓN DE VARIABLES:" << endl;
    
    int contador = 0;
    cout << "contador inicial = " << contador << endl;
    
    contador = 5;                // Asignación
    cout << "después de asignar 5 = " << contador << endl;
    
    contador = contador + 10;    // Incremento
    cout << "después de sumar 10 = " << contador << endl;
    
    contador += 5;               // Operador de asignación compuesta
    cout << "después de += 5 = " << contador << endl;
    
    contador++;                  // Incremento en 1
    cout << "después de ++ = " << contador << endl;
    
    contador--;                  // Decremento en 1
    cout << "después de -- = " << contador << endl << endl;
    
    // 8. BUENAS PRÁCTICAS
    cout << "8. BUENAS PRÁCTICAS:" << endl;
    
    // ✅ Usar nombres descriptivos
    int numero_estudiantes = 25;         // Mejor que: int n = 25;
    double temperatura_ambiente = 23.5;  // Mejor que: double temp = 23.5;
    bool archivo_existe = true;          // Mejor que: bool flag = true;
    
    // ✅ Inicializar variables al declararlas
    int puntuacion = 0;                  // Mejor que declarar sin inicializar
    
    // ✅ Usar const para valores que no cambian
    const double IVA = 0.19;             // Valor que no debe cambiar
    
    cout << "Nombres descriptivos facilitan la lectura del código" << endl;
    cout << "numero_estudiantes = " << numero_estudiantes << endl;
    cout << "temperatura_ambiente = " << temperatura_ambiente << endl;
    cout << "archivo_existe = " << archivo_existe << endl;
    cout << "IVA = " << IVA << endl << endl;
    
    // RESUMEN
    cout << "=== RESUMEN ===" << endl;
    cout << "• Las variables almacenan datos en memoria" << endl;
    cout << "• Deben declararse antes de usarse" << endl;
    cout << "• Es buena práctica inicializarlas al declararlas" << endl;
    cout << "• Usar const para valores que no cambian" << endl;
    cout << "• Elegir nombres descriptivos y seguir convenciones" << endl;
    cout << "• Considerar el alcance (scope) de las variables" << endl;
    
    return 0;
}