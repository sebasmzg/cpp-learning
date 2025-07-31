#include <iostream>
using std::string;
using std::cout;
using std::endl;

int main() {
    // ========================================
    // OPERADORES EN C++
    // ========================================
    
    cout << "=== OPERADORES EN C++ ===" << endl << endl;
    
    // Los operadores son símbolos que realizan operaciones sobre variables y valores
    // C++ tiene varios tipos de operadores:
    // 1. Aritméticos, 2. Asignación, 3. Comparación, 4. Lógicos, 
    // 5. Incremento/Decremento, 6. Bitwise, 7. Otros
    
    // ==========================================
    // 1. OPERADORES ARITMÉTICOS
    // ==========================================
    cout << "1. OPERADORES ARITMÉTICOS:" << endl;
    
    int a = 15, b = 4;
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << (a + b) << " (suma)" << endl;
    cout << "a - b = " << (a - b) << " (resta)" << endl;
    cout << "a * b = " << (a * b) << " (multiplicación)" << endl;
    cout << "a / b = " << (a / b) << " (división entera)" << endl;
    cout << "a % b = " << (a % b) << " (módulo - resto de la división)" << endl;
    
    // División con decimales
    double x = 15.0, y = 4.0;
    cout << "x / y = " << (x / y) << " (división decimal)" << endl;
    
    cout << endl;
    
    // ==========================================
    // 2. OPERADORES DE ASIGNACIÓN
    // ==========================================
    cout << "2. OPERADORES DE ASIGNACIÓN:" << endl;
    
    int numero = 10;
    cout << "número inicial = " << numero << endl;
    
    numero += 5;  // Equivale a: numero = numero + 5
    cout << "después de += 5: " << numero << endl;
    
    numero -= 3;  // Equivale a: numero = numero - 3
    cout << "después de -= 3: " << numero << endl;
    
    numero *= 2;  // Equivale a: numero = numero * 2
    cout << "después de *= 2: " << numero << endl;
    
    numero /= 4;  // Equivale a: numero = numero / 4
    cout << "después de /= 4: " << numero << endl;
    
    numero %= 3;  // Equivale a: numero = numero % 3
    cout << "después de %= 3: " << numero << endl;
    
    cout << endl;
    
    // ==========================================
    // 3. OPERADORES DE COMPARACIÓN
    // ==========================================
    cout << "3. OPERADORES DE COMPARACIÓN:" << endl;
    
    int p = 10, q = 20;
    cout << "p = " << p << ", q = " << q << endl;
    
    cout << "p == q: " << (p == q) << " (igual a)" << endl;
    cout << "p != q: " << (p != q) << " (diferente de)" << endl;
    cout << "p < q: " << (p < q) << " (menor que)" << endl;
    cout << "p > q: " << (p > q) << " (mayor que)" << endl;
    cout << "p <= q: " << (p <= q) << " (menor o igual que)" << endl;
    cout << "p >= q: " << (p >= q) << " (mayor o igual que)" << endl;
    cout << "Nota: Los operadores de comparación devuelven 1 (true) o 0 (false)" << endl;
    cout << endl;
    
    // ==========================================
    // 4. OPERADORES LÓGICOS
    // ==========================================
    cout << "4. OPERADORES LÓGICOS:" << endl;
    
    bool verdadero = true;  // puede ser tipo uint = 1
    bool falso = false;     // puede ser tipo uint = 0
    
    cout << "verdadero = " << verdadero << ", falso = " << falso << endl;
    
    cout << "verdadero && falso: " << (verdadero && falso) << " (AND lógico)" << endl;
    cout << "verdadero || falso: " << (verdadero || falso) << " (OR lógico)" << endl;
    cout << "!verdadero: " << (!verdadero) << " (NOT lógico)" << endl;
    cout << "!falso: " << (!falso) << " (NOT lógico)" << endl;
    
    // Ejemplo práctico
    int edad = 25;
    bool tiene_licencia = true;
    bool puede_conducir = (edad >= 18) && tiene_licencia;
    cout << "¿Puede conducir? (edad >= 18 && tiene_licencia): " << puede_conducir << endl;
    
    cout << endl;
    
    // ==========================================
    // 5. OPERADORES DE INCREMENTO Y DECREMENTO
    // ==========================================
    cout << "5. OPERADORES DE INCREMENTO Y DECREMENTO:" << endl;
    
    int contador = 5;
    cout << "contador inicial = " << contador << endl;
    
    // Pre-incremento: incrementa ANTES de usar el valor
    cout << "++contador = " << (++contador) << " (pre-incremento)" << endl;
    cout << "contador después de pre-incremento = " << contador << endl;
    
    // Post-incremento: usa el valor ANTES de incrementar
    cout << "contador++ = " << (contador++) << " (post-incremento)" << endl;
    cout << "contador después de post-incremento = " << contador << endl;
    
    // Pre-decremento
    cout << "--contador = " << (--contador) << " (pre-decremento)" << endl;
    cout << "contador después de pre-decremento = " << contador << endl;
    
    // Post-decremento
    cout << "contador-- = " << (contador--) << " (post-decremento)" << endl;
    cout << "contador después de post-decremento = " << contador << endl;
    
    cout << endl;
    
    // ==========================================
    // 6. OPERADOR TERNARIO (CONDICIONAL)
    // ==========================================
    cout << "6. OPERADOR TERNARIO (? :):" << endl;
    
    int num1 = 10, num2 = 20;
    
    // Sintaxis: condición ? valor_si_verdadero : valor_si_falso
    int mayor = (num1 > num2) ? num1 : num2;
    cout << "El mayor entre " << num1 << " y " << num2 << " es: " << mayor << endl;
    
    string resultado = (num1 % 2 == 0) ? "par" : "impar";
    cout << num1 << " es " << resultado << endl;
    
    cout << endl;
    
    // ==========================================
    // 7. OPERADORES BITWISE (A NIVEL DE BITS)
    // ==========================================
    cout << "7. OPERADORES BITWISE:" << endl;
    
    int m = 12;  // 1100 en binario
    int n = 10;  // 1010 en binario
    
    cout << "m = " << m << " (1100 en binario)" << endl;
    cout << "n = " << n << " (1010 en binario)" << endl;
    
    cout << "m & n = " << (m & n) << " (AND bitwise)" << endl;
    cout << "m | n = " << (m | n) << " (OR bitwise)" << endl;
    cout << "m ^ n = " << (m ^ n) << " (XOR bitwise)" << endl;
    cout << "~m = " << (~m) << " (NOT bitwise)" << endl;
    cout << "m << 1 = " << (m << 1) << " (desplazamiento izquierda)" << endl;
    cout << "m >> 1 = " << (m >> 1) << " (desplazamiento derecha)" << endl;
    
    cout << endl;
    
    // ==========================================
    // 8. OPERADOR SIZEOF
    // ==========================================
    cout << "8. OPERADOR SIZEOF:" << endl;
    
    cout << "sizeof(int) = " << sizeof(int) << " bytes" << endl;
    cout << "sizeof(double) = " << sizeof(double) << " bytes" << endl;
    cout << "sizeof(char) = " << sizeof(char) << " byte" << endl;
    cout << "sizeof(bool) = " << sizeof(bool) << " byte" << endl;
    
    int array[10];
    cout << "sizeof(array[10]) = " << sizeof(array) << " bytes" << endl;
    
    cout << endl;
    
    // ==========================================
    // 9. OPERADORES DE PUNTEROS (BÁSICO)
    // ==========================================
    cout << "9. OPERADORES DE PUNTEROS (BÁSICO):" << endl;
    
    int valor = 42;
    int* puntero = &valor;  // & = dirección de
    
    cout << "valor = " << valor << endl;
    cout << "dirección de valor (&valor) = " << &valor << endl;
    cout << "puntero = " << puntero << endl;
    cout << "valor apuntado (*puntero) = " << *puntero << endl;
    
    cout << endl;
    
    // ==========================================
    // 10. PRECEDENCIA DE OPERADORES
    // ==========================================
    cout << "10. PRECEDENCIA DE OPERADORES:" << endl;
    
    int resultado1 = 2 + 3 * 4;        // = 2 + 12 = 14 (multiplicación primero)
    int resultado2 = (2 + 3) * 4;      // = 5 * 4 = 20 (paréntesis primero)
    int resultado3 = 10 / 2 + 3;       // = 5 + 3 = 8 (división primero)
    int resultado4 = 10 / (2 + 3);     // = 10 / 5 = 2 (paréntesis primero)
    
    cout << "2 + 3 * 4 = " << resultado1 << endl;
    cout << "(2 + 3) * 4 = " << resultado2 << endl;
    cout << "10 / 2 + 3 = " << resultado3 << endl;
    cout << "10 / (2 + 3) = " << resultado4 << endl;
    
    cout << endl;
    
    // ==========================================
    // 11. EJEMPLOS PRÁCTICOS
    // ==========================================

    // Calcular área de un circulo
    double radio = 5.0;
    double pi = 3.1416;
    double area = pi * radio * radio;
    cout << "Área de im circulo (radio = " << radio << "): " << area << endl;

    // Determinar si un año es bisiesto
    int anio = 2024;
    bool es_bisiesto = (anio % 4 == 0 && anio % 100 !=0) || (anio % 400 == 0);
    cout << "¿Es " << anio << " un año bisiesto? " << (es_bisiesto ? "Sí" : "No") << endl;

    // Intercambiar dos variables sin variable temporal (usando XOR)
    int var1 = 25, var2 = 30;
    cout << "Antes del intercambio: var1 = " << var1 << ", var2 = " << var2 << endl;
    var1 ^= var2;
    var2 ^= var1;
    var1 ^= var2;
    cout << "Después del intercambio: var1 = "<< var1 << ", var2 = " << var2 << endl;

    // Verificar si un número es potencia de 2
    int numero_potencia = 16;
    bool es_potencia_de_2 = (numero_potencia > 0) && ((numero_potencia & (numero_potencia - 1)) == 0);
    /*
    numero_potencia       = 16 = 00010000
    numero_potencia - 1   = 15 = 00001111
    -------------------------------
    bitwise AND result    =      00000000
    */
    cout << endl;

    // ==========================================
    // 12. ORDEN DE PRECEDENCIA (RESUMEN)
    // ==========================================
    cout << "12. ORDEN DE PRECEDENCIA (de mayor a menor):" << endl;
    cout << "1. () [] -> .         (paréntesis, corchetes, acceso)" << endl;
    cout << "2. ! ~ ++ -- + - * &  (unarios)" << endl;
    cout << "3. * / %              (multiplicación, división, módulo)" << endl;
    cout << "4. + -                (suma, resta)" << endl;
    cout << "5. << >>              (desplazamiento)" << endl;
    cout << "6. < <= > >=          (comparación)" << endl;
    cout << "7. == !=              (igualdad)" << endl;
    cout << "8. &                  (AND bitwise)" << endl;
    cout << "9. ^                  (XOR bitwise)" << endl;
    cout << "10. |                 (OR bitwise)" << endl;
    cout << "11. &&                (AND lógico)" << endl;
    cout << "12. ||                (OR lógico)" << endl;
    cout << "13. ?:                (ternario)" << endl;
    cout << "14. = += -= *= /= %=  (asignación)" << endl;

    cout << endl;
    
    // ==========================================
    // CONSEJOS Y BUENAS PRÁCTICAS
    // ==========================================
    cout << "CONSEJOS Y BUENAS PRÁCTICAS:" << endl;
    cout << "Usa paréntesis para clarificar expresiones complejas" << endl;
    cout << "Evita mezclar ++ y -- en expresiones complejas" << endl;
    cout << "Prefiere pre-incremento (++i) sobre post-incremento (i++) en bucles" << endl;
    cout << "Usa operadores de asignación compuesta (+=, -=) para mayor claridad" << endl;
    cout << "Ten cuidado con la división entera vs decimal" << endl;
    cout << "Los operadores bitwise son útiles para optimizaciones y flags" << endl;
    cout << "Siempre inicializa variables antes de usar operadores" << endl;
    
    return 0;
}