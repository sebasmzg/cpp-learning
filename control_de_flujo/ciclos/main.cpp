#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // para manipuladores de formato 
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main(){
    // ========================================
    // CICLOS (BUCLES) EN C++
    // ========================================
    
    cout << "=== CICLOS (BUCLES) EN C++ ===" << endl << endl;

    // Los ciclos permiten repetir un bloque de código múltiples veces
    // C++ tiene 3 tipos principales de ciclos:
    // 1. for (para u núumero conocido de iteraciones)
    // 2. while (mientras una condición sea verdadera)
    // 3. do-while (ejecutar al menos una vez, mientras sea verdadera)

    // ==========================================
    // 1. CICLO FOR TRADICIONAL
    // ==========================================
    cout << "1. CICLO FOR TRADICIONAL:" << endl;

    cout << "Números del 1 al 5:" << endl;
    for(int i = 1; i <= 5; ++i){
        cout << "i = " << i << endl;
    }

    cout << "\nConteo regresivo del 10 al 1:" << endl;
    for(int i = 10; i >= 0; --i){
        cout << i << " ";
    }
    cout << "\nDespegue!" << "\n\n";

    cout << "Números pares del 0 al 10:" << "\n";
    for(int i = 0; i <= 10; i += 2){
        cout << i << " ";
    }
    cout << "\n\n";

    // Múltiples variables en el for
    cout << "For con múltiples variables:" << "\n";
    for (int i = 0, j = 10; i <= j; ++i, --j){
        cout << "i = " << i << ", j = " << j << "\n";
    }

    cout << endl;

    // ==========================================
    // 2. CICLO WHILE
    // ==========================================
    cout << "2. CICLO WHILE:" << endl;

    int contador = 1;
    cout << "conteo con while (1 a 5)" << "\n";
    while (contador <= 5) {
        cout << "contador = " << contador << "\n";
        ++contador; // No olvidar el incremento, porque entraría en bucle infinito
        // no habría condición de salida
    }

    cout << "\n\n";

    // While con condición más compleja
    int numero = 1024;
    int divisiones = 0;
    cout << "Dividiendo " << numero << " entre 2 hasta llegar a 1:" << "\n";
    while(numero > 1){
        cout << numero << " ";
        numero /= 2;
        ++divisiones;
    }
    cout << numero << "\n";
    cout << "Total divisiones: " << divisiones << "\n\n";

    // ==========================================
    // 3. CICLO DO-WHILE
    // ==========================================
    cout << "3. CICLO DO-WHILE:" << endl;

    // int opcion;
    // do {
    //     cout << "\n--- MENÚ ---" << "\n";
    //     cout << "\n1. Opción 1" << "\n";
    //     cout << "\n2. Opción 2" << "\n";
    //     cout << "\n3. Salir" << "\n";
    //     cout << "\nIngresa tu opcion" << "\n";
    //     cin >> opcion;

    //     switch (opcion) {
    //         case 1:
    //             cout << "Seleccionaste Opción 1" << "\n";
    //             break;
    //         case 2:
    //             cout << "Seleccionaste Opción 2" << "\n";
    //             break;
    //         case 3:
    //             cout << "chaito" << "\n";
    //             break;
    //         default:
    //             cout << "Opción inválida. Intenta de nuevo." << "\n";
    //     }
    // } while (opcion != 3); // Se ejecuta al menos una vez

    cout << endl;

    // ==========================================
    // 4. RANGE-BASED FOR (C++11)
    // ==========================================
    cout << "4. RANGE-BASED FOR (C++11):" << endl;

    // El range based permite iterar sobre contenedores como vectores, listas, etc.
    // Es más limpio y evita errores comunes de índices

    // Con arrays
    int numeros[] = {10, 20, 30, 40, 50};
    cout << "Array con range-based for:" << "\n";
    for(int num : numeros){
        cout << num << " ";
    }
    cout << "\n";

    // Con vectores
    vector<string> nombres = {"Ana", "Luis", "Maria", "Carlos"};
    cout << "Vector de nombres:" << "\n";
    for(const string& nombre : nombres){ // const& para evitar copias innecesarias
        cout << nombre << " ";
    }

    cout << "\n\n";

    // Modificar elementos con referencia
    vector<int> valores = {1,2,3,4,5};
    cout << "Valores originales: ";
    for(int val : valores){
        cout << val << " ";
    }

    cout << "\n";

    // Duplicar cada valor
    for(int& val : valores) { // int& val = valores[i]; // Usar referencia para modificar el original
        val *= 2;
    }
    // se accede a cada elemento por referencia para modificarlo directamente
    // el puntero val apunta al elemento original en el vector
    cout << "\n";

    cout << "Valores duplicados: ";
    for(int val : valores){
        cout << val << " ";
    }
    cout << "\n\n";

    // ==========================================
    // 5. CICLOS ANIDADOS
    // ==========================================
    cout << "5. CICLOS ANIDADOS:" << endl;

    // Tabla de multiplicar
    cout << "Tabla de multiplicar (3x3):" << "\n";
    cout << std::setw(4) << "*";
    for(int j = 1; j <= 3; ++j){
        cout << std::setw(4) << j; // Encabezado de columnas
    }
    cout << "\n";

    for(int i = 1; i <= 3; ++i){
        cout << std::setw(4) << i; // Encabezado de filas
        for (int j = 1; j <= 3; ++j){
            cout << std::setw(4) << (i * j); // Producto
        }
        cout << "\n"; // Nueva línea al final de cada fila
    }
    cout << "\n";

    // Patrón de asteriscos
    cout << "Triangulo de asteriscos:" << "\n";
    for (int i = 1; i <= 5; ++i){
        for (int j = 1; j <= i; ++j){
            cout << "* "; 
        }
        cout << "\n";
    }
    cout << "\n\n";

    // ==========================================
    // 6. CONTROL DE FLUJO: BREAK Y CONTINUE
    // ==========================================
    cout << "6. CONTROL DE FLUJO - BREAK Y CONTINUE:" << endl;

    // break: sale del ciclo inmediatamente
    // continue: salta a la siguiente iteración del ciclo

    // BREAK - Salir del ciclo completamente
    cout << "Buscar el primer número divisible por 7:" << endl;
    for (int i = 1; i <= 50; i++) {
        if (i % 7 == 0) {
            cout << "Encontrado: " << i << endl;
            break;  // Salir del ciclo
        }
    }
    cout << endl;
    
    // CONTINUE - Saltar a la siguiente iteración
    cout << "Números del 1 al 10, omitiendo los pares:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Saltar números pares
        }
        cout << i << " ";
    }
    cout << endl << endl;
    
    // Break en ciclos anidados (solo afecta al ciclo interno)
    cout << "Break en ciclos anidados:" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "Fila " << i << ": ";
        for (int j = 1; j <= 5; j++) {
            if (j == 4) {
                break;  // Solo sale del for interno
            }
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

    // ==========================================
    // 7. CICLOS INFINITOS Y COMO EVITARLOS
    // ==========================================
    cout << "7. CICLOS INFINITOS:" << endl;
    
    cout << "Ejemplo de ciclo controlado (simula infinito pero con límite):" << endl;
    int limite = 0;
    while (true) {  // Ciclo infinito controlado
        cout << "Iteración: " << limite << endl;
        limite++;
        
        if (limite >= 5) {
            cout << "Saliendo del ciclo infinito..." << endl;
            break;
        }
    }
    cout << endl;
    
    // Ejemplo de ciclo que PODRÍA ser infinito
    cout << "CUIDADO: Condiciones que pueden causar ciclos infinitos:" << endl;
    cout << "• Olvidar incrementar la variable de control" << endl;
    cout << "• Condición que nunca se vuelve falsa" << endl;
    cout << "• Modificar incorrectamente la variable de control" << endl;
    cout << endl;
    
    // ==========================================
    // 8. EJEMPLOS PRÁCTICOS
    // ==========================================
    cout << "8. EJEMPLOS PRÁCTICOS:" << endl;

    // Calcular factorial
    int n = 5;
    long long factorial = 1; // long long permite manejar números grandes
    cout << "Factorial de " << n << ":\n";
    for(int i = 1; i < n; ++i){
        factorial *= i;
        cout << i << "! = " << factorial << endl;
    }
    cout << "\n";

    // Buscar primos
    int limite_primos = 20;
    cout << "Números primos hasta " << limite_primos << ":\n";
    for(int num = 2; num <= limite_primos; ++num){
        bool es_primo = true;

        for(int divisor = 2; divisor * divisor <= num; ++divisor){
            if(num % divisor == 0){
                es_primo = false; // No es primo si es divisible por otro número
                break; // Salir del ciclo interno
            }
        }
        // es primo si solo es divisible por 1 y por sí mismo
        if (es_primo) {
            cout << num << " ";
        }
    }
    cout << endl << endl;

    // Suma de elementos en un vector
    vector<int> lista_numeros = {1,2,3,4,6};
    int suma = 0;
    cout << "Suma de elementos en el vector: ";
    for(int num : lista_numeros){
        cout << num << " ";
        suma += num; // Acumular la suma
    }
    cout << "\nSuma total: " << suma << endl << endl;

    // contar caracteres en un string
    string texto = "Hola, mundo!";
    int vocales = 0, consonante = 0, espacios = 0;

    cout << "Analizando el texto: '"<< texto << "'\n";
    for(char c : texto){
        if(c == ' '){
            ++espacios;
        } else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                  c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            ++vocales;
        } else {
            ++consonante;
        }
    }
    cout << "Vocales: " << vocales << ", Consonantes: " << consonante 
         << ", Espacios: " << espacios << endl;
    cout << endl;

    // ==========================================
    // 9. COMPARACIÓN DE CICLOS
    // ==========================================
    cout << "9. COMPARACIÓN DE CICLOS:" << endl;
    cout << "┌────────────┬─────────────────────────────────────────┐" << endl;
    cout << "│    TIPO    │               CUÁNDO USAR               │" << endl;
    cout << "├────────────┼─────────────────────────────────────────┤" << endl;
    cout << "│    for     │ Número conocido de iteraciones          │" << endl;
    cout << "│            │ Recorrer arrays/vectores con índices    │" << endl;
    cout << "├────────────┼─────────────────────────────────────────┤" << endl;
    cout << "│   while    │ Condición al inicio                     │" << endl;
    cout << "│            │ Número desconocido de iteraciones       │" << endl;
    cout << "├────────────┼─────────────────────────────────────────┤" << endl;
    cout << "│ do-while   │ Ejecutar al menos una vez               │" << endl;
    cout << "│            │ Menús, validaciones                     │" << endl;
    cout << "├────────────┼─────────────────────────────────────────┤" << endl;
    cout << "│range-based │ Recorrer contenedores completos         │" << endl;
    cout << "│    for     │ Cuando no necesitas el índice           │" << endl;
    cout << "└────────────┴─────────────────────────────────────────┘" << endl;
    cout << endl;
    
    // ==========================================
    // 10. OPTIMIZACIÓN Y BUENAS PRÁCTICAS
    // ==========================================
    cout << "10. OPTIMIZACIÓN Y BUENAS PRÁCTICAS:" << endl;
    
    // Pre-incremento vs Post-incremento
    cout << "Optimización: Pre-incremento vs Post-incremento" << endl;
    vector<int> datos = {1, 2, 3, 4, 5};
    
    cout << "Prefiere ++i sobre i++ en bucles:" << endl;
    for (size_t i = 0; i < datos.size(); ++i) {  // Pre-incremento (más eficiente)
        cout << datos[i] << " ";
    }
    cout << endl;
    
    // Usar auto para simplificar
    cout << "\nUsar 'auto' para simplificar:" << endl;
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Mejor aún: range-based for
    cout << "\nMejor aún: range-based for:" << endl;
    for (const auto& elemento : datos) {
        cout << elemento << " ";
    }
    cout << endl << endl;
    
    // ==========================================
    // CONSEJOS FINALES
    // ==========================================
    cout << "CONSEJOS Y BUENAS PRÁCTICAS:" << endl;
    cout << "• Inicializa siempre las variables de control" << endl;
    cout << "• Verifica que la condición pueda volverse falsa" << endl;
    cout << "• Usa nombres descriptivos para variables de control" << endl;
    cout << "• Prefiere range-based for para recorrer contenedores" << endl;
    cout << "• Usa const& en range-based for para objetos grandes" << endl;
    cout << "• Evita modificar la variable de control dentro del ciclo" << endl;
    cout << "• Usa break y continue con moderación" << endl;
    cout << "• Comenta ciclos complejos o anidados" << endl;
    cout << "• Considera extraer lógica compleja a funciones" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE SINTAXIS
    // ==========================================
    cout << "RESUMEN DE SINTAXIS:" << endl;
    cout << "for(init; condición; incremento) { ... }" << endl;
    cout << "while(condición) { ... }" << endl;
    cout << "do { ... } while(condición);" << endl;
    cout << "for(tipo variable : contenedor) { ... }" << endl;
    cout << "break;     // Salir del ciclo" << endl;
    cout << "continue;  // Siguiente iteración" << endl;
    
    return 0;
}