#include <iostream>
#include <string>
#include <iomanip> // para manipuladores de formato
#include <sstream> // Para usar stringstream que permite manipular cadenas como flujos de entrada/salida
#include <fstream> // Para manejar archivos
using std::cout; // permite imprimir en consola
using std::cin; // permite leer desde consola
using std::endl; // fin de línea, equivalente a '\n'
using std::string; // para usar cadenas de texto (strings)
using std::getline; // para leer líneas completas

int main(){
     // ========================================
    // ENTRADA Y SALIDA DE DATOS EN C++
    // ========================================
    
    cout << "=== ENTRADA Y SALIDA DE DATOS EN C++ ===" << endl << endl;
    
    // C++ utiliza streams (flujos) para manejar entrada y salida de datos
    // Los principales son: cout (salida), cin (entrada), cerr (errores)
    
    // ==========================================
    // 1. SALIDA DE DATOS (cout)
    // ==========================================
    cout << "1. SALIDA DE DATOS CON cout:" << endl;
    
    // Salida básica
    cout << "Hola mundo!" << endl;
    cout << "El operador << se llama 'operador de inserción'" << endl;
    
    // Salida de variables
    int edad = 25;
    double altura = 1.75;
    string nombre = "Ana";
    
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << " años" << endl;
    cout << "Altura: " << altura << " metros" << endl;
    
    // Concatenar múltiples valores
    cout << nombre << " tiene " << edad << " años y mide " << altura << "m" << endl;
    
    // Diferentes formas de salto de línea
    cout << "Línea 1" << endl;          // Con endl (más lento, limpia buffer)
    cout << "Línea 2\n";               // Con \n (más rápido)
    cout << "Línea 3" << std::flush;   // Sin salto, pero limpia buffer
    cout << "\n\n";

    // ==========================================
    // 2. ENTRADA DE DATOS (cin)
    // ==========================================
    //cout << "2. ENTRADA DE DATOS CON cin:" << endl;

    // entrada básica de números
    /*
    int numero;
    cout << "Ingrese un número entero: ";
    cin >> numero; // Lee un número entero desde la entrada estándar
    cout << "Ingresaste el número: " << numero << endl;
    */

    // entrada de caracteres
    /*
    char caracter;
    cout << "Ingrese un carácter: ";
    cin >> caracter; // Lee un único carácter
    cout << "Ingresaste el carácter: " << caracter << endl;
    */

    // Problema con cin y strings con espacios
    /*
    cout << "\nProblema con cin y strings con espacios:" << endl;
    string palabra;
    cout << "Ingrese una palabra (sin espacios): ";
    cin >> palabra; // Solo lee hasta el primer espacio
    cout << "Ingresaste: " << palabra << endl;
    */

    // Limpiar buffer antes de usar getline
    //cin.ignore(); // Limpia el buffer de entrada

    cout << endl;

     // ==========================================
    // 3. ENTRADA DE LÍNEAS COMPLETAS (getline)
    // ==========================================
    cout << "3. ENTRADA DE LÍNEAS COMPLETAS:" << endl;
    /*
    string frase_completa;
    cout << "Ingrese una frase completa (con espacios): ";
    getline(cin, frase_completa); // Lee una línea completa incluyendo espacios
    //cin es un objeto de tipo istream que permite leer datos de la entrada estándar (teclado)
    cout << "Ingresaste: " << frase_completa << endl;
    */

    // getline con delimitador personalizado
    /*
    string texto_delimitado;
    cout << "Ingresa texto (termina con ';): ";
    getline(cin, texto_delimitado, ';'); // Lee hasta el delimitador ';'
    cout << "Texto hasta ';': " << texto_delimitado << endl;
    */

    // Limpiar buffer residual
    //cin.ignore();

    cout << endl;
    
    // ==========================================
    // 4. FORMATEO DE SALIDA
    // ==========================================
    cout << "4. FORMATEO DE SALIDA:" << endl;

    double pi = 3.14159265358979323846;
    int entero = 42;
    
    // Presicion decimal
    cout << "Pi con 2 decimales: " << std::fixed << std::setprecision(2) << pi << endl;
    // std::fixed asegura que se muestre en notación decimal
    // std::setprecision(x) establece la precisión a x decimales
    cout << "Pi con 5 decimales: " << std::setprecision(5) << pi << endl;

    cout << endl;

    // Ancho de campo
    cout << "Números alineados:" << endl;
    cout << std::setw(10) << "Número" << std::setw(10) << "Cuadrado" << endl;
    for(int i = 1; i <= 5; ++i){
        cout << std::setw(10) << i << std::setw(10) << (i * i) << endl;
    }

    cout << endl;

    // Relleno con caracteres
    cout << "Relleno con asteriscos: " << std::setfill('*') << std::setw(15) << entero <<endl;
    cout << std::setfill(' '); // Restablecer el relleno a espacio

    cout << endl;

    // Bases numéricas
    int numero_base = 255;
    cout << "Número decimal: " << std::dec << numero_base << endl; 
    cout << "Número hexadecimal: " << std::hex << numero_base << endl;
    cout << "Número octal: " << std::oct << numero_base << endl;
    cout << std::dec; // Restablecer a decimal

    cout << endl;

    // ==========================================
    // 5. VALIDACIÓN DE ENTRADA
    // ==========================================
    cout << "5. VALIDACIÓN DE ENTRADA:" << endl;
    
    /*
    int numero_validado;
    cout << "Ingresa un número entero válido: ";

    while(!(cin >> numero_validado)){
        cout << "Error: Entrada inválida. Ingresa un número entero: ";
        cin.clear(); // Limpia el estado de error del cin
        cin.ignore(10000, '\n'); // Ignorar caracteres inválidos hasta el salto de línea
    }

    cout << "Número ingresado: " << numero_validado << endl;
    */
    //cin.ignore(); // Limpiar buffer para futuras entradas

    cout << endl;

    // ==========================================
    // 6. ENTRADA/SALIDA CON ARCHIVOS
    // ==========================================
    cout << "6. ENTRADA/SALIDA CON ARCHIVOS:" << endl;

    // Escribir en un archivo
    std::ofstream archivo_salida("datos.txt"); // lo que hace ofstream es abrir un archivo para escritura
    // si no existe, lo crea; si existe, lo sobreescribe
    if(archivo_salida.is_open()){
        archivo_salida << "Nombre: " << nombre << endl;
        archivo_salida << "Edad: " << edad << endl;
        archivo_salida << "Altura: " << altura << endl;
        archivo_salida.close(); // Cerrar el archivo
        cout << "Datos escritos en datos.txt" << endl;
    } else {
        cout << "Error al crear el archivo para escritura." << endl;
    }

    cout << endl;

    // Leer un archivo
    std::ifstream archivo_entrada("datos.txt"); // lo que hace ifstream es abrir un archivo para lectura
    if(archivo_entrada.is_open()){
        string linea;
        cout << "Contenido de datos.txt:" << endl;
        while(getline(archivo_entrada, linea)){ // lee línea por línea
            cout << " " << linea << endl;
        }
        archivo_entrada.close(); // Cerrar el archivo
    } else {
        cout << "Error al abrir el archivo para lectura." << endl;
    }

    cout << endl;

    // ==========================================
    // 7. STRINGSTREAM (CONVERSIONES)
    // ==========================================
    cout << "7. STRINGSTREAM PARA CONVERSIONES:" << endl;

    // Convertir string a números
    string numero_string = "12345";
    std::stringstream ss1(numero_string);
    // la diferencia entre stringstream y cin es que stringstream permite manipular cadenas como si fueran flujos de entrada/salida
    int numero_convertido;
    ss1 >> numero_convertido; // Extrae el número del stringstream
    cout << "String '" << numero_string << "' convertido a int: " << numero_convertido << endl;

    cout << endl;

    // Convertir numeros a string
    std::stringstream ss2;
    ss2 << "El número es: " << 456 << " y el decimal es: " << 78.9;
    string resultado = ss2.str(); // Obtener el contenido del stringstream como string
    cout << "String construido: " << resultado << endl;

    cout << endl; 

    // Parsear múltiples valores de un string
    string datos = "Juan 25 1.80";
    std::stringstream ss3(datos);
    string nombre_parseado;
    int edad_parseada;
    double altura_parseada;

    ss3 >> nombre_parseado >> edad_parseada >> altura_parseada; // Extrae los valores del stringstream
    cout << "Datos parseados - Nombre: " << nombre_parseado 
         << ", Edad: " << edad_parseada << ", Altura: " << altura_parseada << endl;
    
    cout << endl; 

    // ==========================================
    // 8. MANIPULADORES ÚTILES
    // ==========================================
    cout << "8. MANIPULADORES ÚTILES:" << endl;
    
    bool valor_bool = true;
    cout << "Bool como número: " << valor_bool << endl;
    cout << "Bool como texto: " << std::boolalpha << valor_bool << endl;
    cout << std::noboolalpha; // Restaurar formato numérico
    
    // Mostrar signo positivo
    int positivo = 42;
    cout << "Sin signo: " << positivo << endl;
    cout << "Con signo: " << std::showpos << positivo << endl;
    cout << std::noshowpos; // Quitar signo positivo
    
    // Notación científica
    double grande = 123456789.0;
    cout << "Número grande normal: " << grande << endl;
    cout << "Notación científica: " << std::scientific << grande << endl;
    cout << std::fixed; // Restaurar notación fija
    
    cout << endl;

    // ==========================================
    // 9. EJEMPLO PRÁCTICO: CALCULADORA SIMPLE
    // ==========================================
    cout << "9. EJEMPLO PRÁCTICO - CALCULADORA SIMPLE:" << endl;
    
    double num1, num2;
    char operador;
    
    cout << "Ingresa una operación (ej: 5 + 3): ";
    cin >> num1 >> operador >> num2; // Leer dos números y un operador

    cout << std::fixed << std::setprecision(2); // Formato de salida para resultados

    switch(operador){
        case '+':
            cout << num1 << "+" << num2 << " = " << (num1 + num2) << endl;
            break;
        case '-':
            cout << num1 << "-" << num2 << " = " << (num1 - num2) << endl;
            break;
        case '*':
            cout << num1 << "*" << num2 << " = " << (num1 * num2) << endl;
            break;
        case '/':
            if(num2 != 0){
                cout << num1 << "/" << num2 << " = " << (num1 / num2) << endl;
            } else {
                cout << "Error: División por cero" << endl;
            }
            break;
        default:
            cout << "Operador no válido: " << operador << endl;

    }

    cout << endl;

    // ==========================================
    // 10. BUENAS PRÁCTICAS
    // ==========================================
    cout << "10. BUENAS PRÁCTICAS:" << endl;
    cout << "• Validar siempre la entrada del usuario" << endl;
    cout << "• Usa getline() para strings con espacios" << endl;
    cout << "• Limpiar el buffer con cin.ignore() cuando sea necesario" << endl;
    cout << "• Verifica rque los archivos se abran correctamente" << endl;
    cout << "• Usar manipuladores de formato para salidas profesionales" << endl;
    cout << "• Manejar errores de entrada/salida apropiadamente" << endl;
    cout << "• Cerrar archivos después de usarlos" << endl;
    cout << "• Usar endl solo cuando necesites limpiar el buffer" << endl;
    cout << "• Preferir \\n sobre endl para mejor rendimiento" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE FUNCIONES IMPORTANTES
    // ==========================================
    cout << "RESUMEN DE FUNCIONES IMPORTANTES:" << endl;
    cout << "cout << valor          - Salida de datos" << endl;
    cout << "cin >> variable        - Entrada de datos" << endl;
    cout << "getline(cin, string)   - Leer línea completa" << endl;
    cout << "cin.ignore()           - Limpiar buffer" << endl;
    cout << "cin.clear()            - Limpiar flags de error" << endl;
    cout << "setprecision(n)        - Precisión decimal" << endl;
    cout << "setw(n)                - Ancho de campo" << endl;
    cout << "setfill(char)          - Carácter de relleno" << endl;
    cout << "fixed/scientific       - Formato de números" << endl;
    cout << "hex/oct/dec            - Base numérica" << endl;

    return 0;
}