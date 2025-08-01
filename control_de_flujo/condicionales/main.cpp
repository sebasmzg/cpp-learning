#include <iostream>
#include <string>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    // ========================================
    // CONDICIONALES EN C++
    // ========================================
    
    cout << "=== CONDICIONALES EN C++ ===" << endl << endl;
    
    // Las estructuras condicionales permiten ejecutar diferentes bloques de código
    // basándose en condiciones (expresiones que evalúan a true o false)
    // C++ tiene varias estructuras condicionales:
    // 1. if, 2. if-else, 3. if-else if-else, 4. switch-case, 5. operador ternario
    
    // ==========================================
    // 1. ESTRUCTURA IF BÁSICA
    // ==========================================
    cout << "1. ESTRUCTURA IF BÁSICA:" << endl;
    
    int edad = 18;
    cout << "Edad: " << edad << " años" << endl;
    
    if (edad >= 18) {
        cout << "Eres mayor de edad" << endl;
    }
    
    cout << "Esta línea siempre se ejecuta" << endl << endl;
    
    // Ejemplo con diferentes tipos de condiciones
    bool tiene_licencia = true;
    double saldo = 1500.50;
    
    if (tiene_licencia) {
        cout << "Puede conducir (tiene licencia)" << endl;
    }
    
    if (saldo > 1000) {
        cout << "Saldo suficiente para la compra" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 2. ESTRUCTURA IF-ELSE
    // ==========================================
    cout << "2. ESTRUCTURA IF-ELSE:" << endl;
    
    int numero = 15;
    cout << "Número: " << numero << endl;
    
    if (numero % 2 == 0) {
        cout << "El número es par" << endl;
    } else {
        cout << "El número es impar" << endl;
    }
    
    // Ejemplo con strings
    string password = "123456";
    string intento = "123456";
    
    cout << "\nValidación de contraseña:" << endl;
    if (intento == password) {
        cout << "¡Acceso concedido!" << endl;
    } else {
        cout << "Contraseña incorrecta" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 3. ESTRUCTURA IF-ELSE IF-ELSE
    // ==========================================
    cout << "3. ESTRUCTURA IF-ELSE IF-ELSE:" << endl;
    
    double nota = 85.5;
    cout << "Nota obtenida: " << nota << endl;
    
    if (nota >= 90) {
        cout << "Calificación: A (Excelente)" << endl;
    } else if (nota >= 80) {
        cout << "Calificación: B (Muy bueno)" << endl;
    } else if (nota >= 70) {
        cout << "Calificación: C (Bueno)" << endl;
    } else if (nota >= 60) {
        cout << "Calificación: D (Suficiente)" << endl;
    } else {
        cout << "Calificación: F (Insuficiente)" << endl;
    }
    
    cout << endl;
    
    // Ejemplo con múltiples condiciones
    int hora = 14;
    cout << "Hora actual: " << hora << ":00" << endl;
    
    if (hora >= 6 && hora < 12) {
        cout << "Buenos días" << endl;
    } else if (hora >= 12 && hora < 18) {
        cout << "Buenas tardes" << endl;
    } else if (hora >= 18 && hora < 24) {
        cout << "Buenas noches" << endl;
    } else {
        cout << "Es muy tarde (o muy temprano)" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 4. OPERADORES DE COMPARACIÓN
    // ==========================================
    cout << "4. OPERADORES DE COMPARACIÓN:" << endl;
    
    int a = 10, b = 20;
    cout << "a = " << a << ", b = " << b << endl;
    
    cout << "a == b: " << (a == b) << " (igual)" << endl;
    cout << "a != b: " << (a != b) << " (diferente)" << endl;
    cout << "a < b: " << (a < b) << " (menor que)" << endl;
    cout << "a > b: " << (a > b) << " (mayor que)" << endl;
    cout << "a <= b: " << (a <= b) << " (menor o igual)" << endl;
    cout << "a >= b: " << (a >= b) << " (mayor o igual)" << endl;
    
    cout << endl;
    
    // ==========================================
    // 5. OPERADORES LÓGICOS
    // ==========================================
    cout << "5. OPERADORES LÓGICOS:" << endl;
    
    bool es_estudiante = true;
    int edad_usuario = 20;
    double promedio = 8.5;
    
    cout << "es_estudiante: " << es_estudiante << endl;
    cout << "edad: " << edad_usuario << endl;
    cout << "promedio: " << promedio << endl;
    
    // AND (&&) - Ambas condiciones deben ser verdaderas
    if (es_estudiante && edad_usuario >= 18) {
        cout << "Es un estudiante mayor de edad" << endl;
    }
    
    // OR (||) - Al menos una condición debe ser verdadera
    if (promedio >= 9.0 || es_estudiante) {
        cout << "Califica para la beca (buen promedio O es estudiante)" << endl;
    }
    
    // NOT (!) - Invierte el valor de la condición
    if (!es_estudiante) {
        cout << "No es estudiante" << endl;
    } else {
        cout << "Sí es estudiante" << endl;
    }
    
    // Combinaciones complejas
    if ((es_estudiante && promedio >= 8.0) || edad_usuario < 18) {
        cout << "Condición compleja cumplida" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 6. SWITCH-CASE
    // ==========================================
    cout << "6. SWITCH-CASE:" << endl;
    
    int dia_semana = 3;
    cout << "Día de la semana (número): " << dia_semana << endl;
    
    switch (dia_semana) {
        case 1:
            cout << "Lunes" << endl;
            break;
        case 2:
            cout << "Martes" << endl;
            break;
        case 3:
            cout << "Miércoles" << endl;
            break;
        case 4:
            cout << "Jueves" << endl;
            break;
        case 5:
            cout << "Viernes" << endl;
            break;
        case 6:
        case 7:
            cout << "Fin de semana" << endl;
            break;
        default:
            cout << "Día inválido" << endl;
            break;
    }
    
    cout << endl;
    
    // Switch con caracteres
    char calificacion = 'B';
    cout << "Calificación: " << calificacion << endl;
    
    switch (calificacion) {
        case 'A':
        case 'a':
            cout << "Excelente trabajo" << endl;
            break;
        case 'B':
        case 'b':
            cout << "Buen trabajo" << endl;
            break;
        case 'C':
        case 'c':
            cout << "Trabajo aceptable" << endl;
            break;
        case 'D':
        case 'd':
            cout << "Necesitas mejorar" << endl;
            break;
        case 'F':
        case 'f':
            cout << "Trabajo insuficiente" << endl;
            break;
        default:
            cout << "Calificación no válida" << endl;
            break;
    }
    
    cout << endl;
    
    // ==========================================
    // 7. OPERADOR TERNARIO (? :)
    // ==========================================
    cout << "7. OPERADOR TERNARIO (? :):" << endl;
    
    int x = 15, y = 10;
    cout << "x = " << x << ", y = " << y << endl;
    
    // Sintaxis: condición ? valor_si_verdadero : valor_si_falso
    int mayor = (x > y) ? x : y;
    cout << "El mayor es: " << mayor << endl;
    
    // Con strings
    string resultado = (x % 2 == 0) ? "par" : "impar";
    cout << x << " es " << resultado << endl;
    
    // Ternario anidado (no recomendado para casos complejos)
    string categoria = (x > 20) ? "grande" : (x > 10) ? "mediano" : "pequeño";
    cout << x << " es " << categoria << endl;
    
    cout << endl;
    
    // ==========================================
    // 8. CONDICIONALES ANIDADAS
    // ==========================================
    cout << "8. CONDICIONALES ANIDADAS:" << endl;
    
    bool es_miembro = true;
    double monto_compra = 150.0;
    string tipo_miembro = "premium";
    
    cout << "es_miembro: " << es_miembro << endl;
    cout << "monto_compra: $" << monto_compra << endl;
    cout << "tipo_miembro: " << tipo_miembro << endl;
    
    if (es_miembro) {
        cout << "Cliente es miembro" << endl;
        
        if (tipo_miembro == "premium") {
            cout << "Descuento premium aplicado" << endl;
            
            if (monto_compra > 100) {
                cout << "Descuento adicional por compra mayor a $100" << endl;
            }
        } else {
            cout << "Descuento básico aplicado" << endl;
        }
    } else {
        cout << "Sin descuentos (no es miembro)" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 9. EJEMPLOS PRÁCTICOS
    // ==========================================
    cout << "9. EJEMPLOS PRÁCTICOS:" << endl;
    
    // Calculadora simple
    cout << "\n--- CALCULADORA SIMPLE ---" << endl;
    double num1 = 10, num2 = 5;
    char operador = '+';
    
    cout << "Operación: " << num1 << " " << operador << " " << num2 << endl;
    
    switch (operador) {
        case '+':
            cout << "Resultado: " << (num1 + num2) << endl;
            break;
        case '-':
            cout << "Resultado: " << (num1 - num2) << endl;
            break;
        case '*':
            cout << "Resultado: " << (num1 * num2) << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << "Resultado: " << (num1 / num2) << endl;
            } else {
                cout << "Error: División por cero" << endl;
            }
            break;
        default:
            cout << "Operador no válido" << endl;
    }
    
    // Validación de edad para votar
    cout << "\n--- VALIDACIÓN PARA VOTAR ---" << endl;
    int edad_votante = 17;
    bool tiene_cedula = true;
    
    cout << "Edad: " << edad_votante << ", Tiene cédula: " << tiene_cedula << endl;
    
    if (edad_votante >= 18) {
        if (tiene_cedula) {
            cout << "✅ Puede votar" << endl;
        } else {
            cout << "❌ No puede votar (necesita cédula)" << endl;
        }
    } else {
        cout << "❌ No puede votar (menor de edad)" << endl;
    }
    
    // Clasificación de IMC
    cout << "\n--- CLASIFICACIÓN DE IMC ---" << endl;
    double peso = 70.0;  // kg
    double altura_m = 1.75;  // metros
    double imc = peso / (altura_m * altura_m);
    
    cout << std::fixed << std::setprecision(1);
    cout << "Peso: " << peso << "kg, Altura: " << altura_m << "m" << endl;
    cout << "IMC: " << imc << endl;
    
    if (imc < 18.5) {
        cout << "Clasificación: Bajo peso" << endl;
    } else if (imc < 25.0) {
        cout << "Clasificación: Peso normal" << endl;
    } else if (imc < 30.0) {
        cout << "Clasificación: Sobrepeso" << endl;
    } else {
        cout << "Clasificación: Obesidad" << endl;
    }
    
    cout << std::setprecision(6); // Restaurar precisión por defecto
    cout << endl;
    
    // ==========================================
    // 10. VALIDACIÓN DE ENTRADA
    // ==========================================
    cout << "10. VALIDACIÓN DE ENTRADA:" << endl;
    
    // Simulamos entrada del usuario
    string entrada_usuario = "25";
    
    // Validar si es un número
    bool es_numero = true;
    for (char c : entrada_usuario) {
        if (!isdigit(c)) {
            es_numero = false;
            break;
        }
    }
    
    if (es_numero && !entrada_usuario.empty()) {
        int numero_convertido = std::stoi(entrada_usuario);
        cout << "Entrada válida: " << numero_convertido << endl;
        
        if (numero_convertido >= 0 && numero_convertido <= 100) {
            cout << "Número en rango válido (0-100)" << endl;
        } else {
            cout << "Número fuera de rango" << endl;
        }
    } else {
        cout << "Entrada no válida (no es un número)" << endl;
    }
    
    cout << endl;
    
    // ==========================================
    // 11. COMPARACIÓN DE ESTRUCTURAS
    // ==========================================
    cout << "11. COMPARACIÓN DE ESTRUCTURAS CONDICIONALES:" << endl;
    cout << "┌─────────────┬────────────────────────────────────────┐" << endl;
    cout << "│ ESTRUCTURA  │               CUÁNDO USAR              │" << endl;
    cout << "├─────────────┼────────────────────────────────────────┤" << endl;
    cout << "│     if      │ Una sola condición simple             │" << endl;
    cout << "├─────────────┼────────────────────────────────────────┤" << endl;
    cout << "│   if-else   │ Dos alternativas mutuamente excluyentes│" << endl;
    cout << "├─────────────┼────────────────────────────────────────┤" << endl;
    cout << "│ if-else if  │ Múltiples condiciones relacionadas    │" << endl;
    cout << "├─────────────┼────────────────────────────────────────┤" << endl;
    cout << "│ switch-case │ Múltiples valores de una variable     │" << endl;
    cout << "│             │ Valores discretos (int, char, enum)   │" << endl;
    cout << "├─────────────┼────────────────────────────────────────┤" << endl;
    cout << "│ Ternario ?  │ Asignación simple basada en condición │" << endl;
    cout << "│             │ Expresiones cortas                    │" << endl;
    cout << "└─────────────┴────────────────────────────────────────┘" << endl;
    cout << endl;
    
    // ==========================================
    // 12. BUENAS PRÁCTICAS
    // ==========================================
    cout << "12. BUENAS PRÁCTICAS:" << endl;
    cout << "✅ HACER:" << endl;
    cout << "• Usar paréntesis para clarificar condiciones complejas" << endl;
    cout << "• Manejar todos los casos posibles (incluyendo default)" << endl;
    cout << "• Usar nombres descriptivos para variables booleanas" << endl;
    cout << "• Mantener condiciones simples y legibles" << endl;
    cout << "• Usar switch para múltiples valores de una variable" << endl;
    cout << "• Validar entrada del usuario" << endl;
    cout << "• Usar const para valores que no cambian" << endl;
    
    cout << "\n❌ EVITAR:" << endl;
    cout << "• Condiciones demasiado complejas en una línea" << endl;
    cout << "• Anidar demasiados niveles de if" << endl;
    cout << "• Comparar flotantes con == (usar rangos)" << endl;
    cout << "• Olvidar break en switch-case" << endl;
    cout << "• Ternarios anidados complejos" << endl;
    cout << "• Asumir entrada válida sin validar" << endl;
    
    cout << endl;
    
    // ==========================================
    // EJEMPLOS DE ERRORES COMUNES
    // ==========================================
    cout << "ERRORES COMUNES Y CÓMO EVITARLOS:" << endl;
    
    cout << "\n1. Asignación en lugar de comparación:" << endl;
    cout << "❌ if (x = 5)     // Asigna 5 a x" << endl;
    cout << "✅ if (x == 5)    // Compara x con 5" << endl;
    
    cout << "\n2. Olvidar break en switch:" << endl;
    cout << "❌ switch(x) { case 1: cout << \"uno\"; case 2: cout << \"dos\"; }" << endl;
    cout << "✅ switch(x) { case 1: cout << \"uno\"; break; case 2: cout << \"dos\"; break; }" << endl;
    
    cout << "\n3. Comparación de flotantes:" << endl;
    cout << "❌ if (precio == 19.99)                    // Puede fallar" << endl;
    cout << "✅ if (abs(precio - 19.99) < 0.01)        // Usar tolerancia" << endl;
    
    cout << "\n4. Precedencia de operadores:" << endl;
    cout << "❌ if (x > 5 && y > 10 || z < 2)          // Confuso" << endl;
    cout << "✅ if ((x > 5 && y > 10) || z < 2)        // Claro" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE SINTAXIS
    // ==========================================
    cout << "RESUMEN DE SINTAXIS:" << endl;
    cout << "if (condición) { ... }" << endl;
    cout << "if (condición) { ... } else { ... }" << endl;
    cout << "if (condición1) { ... } else if (condición2) { ... } else { ... }" << endl;
    cout << "switch (variable) { case valor: ...; break; default: ...; }" << endl;
    cout << "variable = (condición) ? valor_true : valor_false;" << endl;
    
    return 0;
}