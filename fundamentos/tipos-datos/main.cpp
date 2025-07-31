#include <iostream>
using std::cout; // Importar cout del espacio de nombres std para usarlo directamente
using std::endl; // Importar endl del espacio de nombres std para usarlo directamente

int main() {
    int boolean = true; // Declarar una variable booleana
    cout << "El valor de la variable booleana es: " << boolean << endl; // Imprimir el valor de la variable booleana
    cout << "Tiene un tamaño de: " << sizeof(boolean) << " bytes\n" << endl; // Imprimir el tamaño de la variable booleana

    char caracter = 'A'; // Declarar una variable char
    cout << "El valor de la variable char es: " << caracter << endl;
    cout << "Tiene un tamaño de: " << sizeof(caracter) << " bytes" << endl;
    cout << "Su rango es de -128 a 127\n" << endl;

    // TIPOS DE DATOS ENTEROS
    short numero_corto = 32767; // Declarar una variable short
    cout << "\nEl valor de la variable short es: " << numero_corto << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_corto) << " bytes" << endl;
    cout << "Su rango es de -32,768 a 32,767" << endl;

    int numero_entero = 2147483647; // Declarar una variable int
    cout << "\nEl valor de la variable int es: " << numero_entero << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_entero) << " bytes" << endl;
    cout << "Su rango es de -2,147,483,648 a 2,147,483,647" << endl;

    long numero_largo = 9223372036854775807L; // Declarar una variable long
    cout << "\nEl valor de la variable long es: " << numero_largo << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_largo) << " bytes" << endl;
    cout << "Su rango es de -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807" << endl;

    long long numero_muy_largo = 9223372036854775807LL; // Declarar una variable long long
    cout << "\nEl valor de la variable long long es: " << numero_muy_largo << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_muy_largo) << " bytes" << endl;

    // TIPOS DE DATOS SIN SIGNO (UNSIGNED)
    unsigned int numero_sin_signo = 4294967295U; // Declarar una variable unsigned int
    cout << "\nEl valor de la variable unsigned int es: " << numero_sin_signo << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_sin_signo) << " bytes" << endl;
    cout << "Su rango es de 0 a 4,294,967,295" << endl;

    // TIPOS DE DATOS DE PUNTO FLOTANTE
    float numero_flotante = 3.14159f; // Declarar una variable float
    cout << "\nEl valor de la variable float es: " << numero_flotante << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_flotante) << " bytes" << endl;
    cout << "Precisión aproximada: 7 dígitos decimales" << endl;

    double numero_doble = 3.141592653589793; // Declarar una variable double
    cout << "\nEl valor de la variable double es: " << numero_doble << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_doble) << " bytes" << endl;
    cout << "Precisión aproximada: 15-16 dígitos decimales" << endl;

    long double numero_doble_largo = 3.141592653589793238L; // Declarar una variable long double
    cout << "\nEl valor de la variable long double es: " << numero_doble_largo << endl;
    cout << "Tiene un tamaño de: " << sizeof(numero_doble_largo) << " bytes" << endl;
    cout << "Precisión aproximada: 19 dígitos decimales o más" << endl;

    // OTROS TIPOS IMPORTANTES
    wchar_t caracter_ancho = L'Ñ'; // Declarar una variable wchar_t para caracteres Unicode
    cout << "\nLa variable wchar_t puede almacenar caracteres Unicode" << endl;
    cout << "Tiene un tamaño de: " << sizeof(caracter_ancho) << " bytes" << endl;

    // TIPO VOID (se usa principalmente en funciones)
    cout << "\nEl tipo void no tiene tamaño definido, se usa para funciones que no retornan valor" << endl;

    // RESUMEN DE TAMAÑOS
    cout << "\n==== RESUMEN DE TAMAÑOS DE TIPOS DE DATOS ====" << endl;
    cout << "bool: " << sizeof(bool) << " byte(s)" << endl;
    cout << "char: " << sizeof(char) << " byte(s)" << endl;
    cout << "short: " << sizeof(short) << " byte(s)" << endl;
    cout << "int: " << sizeof(int) << " byte(s)" << endl;
    cout << "long: " << sizeof(long) << " byte(s)" << endl;
    cout << "long long: " << sizeof(long long) << " byte(s)" << endl;
    cout << "float: " << sizeof(float) << " byte(s)" << endl;
    cout << "double: " << sizeof(double) << " byte(s)" << endl;
    cout << "long double: " << sizeof(long double) << " byte(s)" << endl;
    cout << "wchar_t: " << sizeof(wchar_t) << " byte(s)" << endl;

    return 0;
}