// PILAS
// Estructura LIFO (Last In, First Out)
// Operaciones restringidas a un extremo (tope)

// Operaciones básicas:
// - push: agregar un elemento al tope
// - pop: eliminar el elemento del tope
// - top: obtener el elemento del tope sin eliminarlo
// - isEmpty: verificar si la pila está vacía
// - size: obtener el tamaño de la pila
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <chrono>
using namespace std;

// IMPLEMENTACIONES

// --- Array

class PilaArray {
    private: 
        int* elementos; // Array dinámico para almacenar los elementos
        int capacidad; // Capacidad del array
        int cima; // Índice del tope de la pila
    public:
        PilaArray(int cap) : capacidad(cap), cima(-1) {
            elementos = new int[capacidad]; // Inicializar el array dinámico
        }

        bool isEmpty() { return cima == -1; } // Verifica si la pila está vacía
        bool isFull() { return cima == capacidad - 1; } // Verifica si la pila está llena

        void push(int dato) {
            if(isFull()) throw "Desbordamiento de pila"; // Lanza excepción si la pila está llena
            elementos[++cima] = dato; // Incrementa el índice y agrega el elemento
        }

        int pop(){
            if(isEmpty()) throw "Pila vacía"; // Lanza excepción si la pila está vacía
            return elementos[cima--]; // Retorna el elemento del tope y decrementa el índice
        }

        int top() {
            if(isEmpty()) throw "Pila vacía"; // Lanza excepción si la pila está vacía
            return elementos[cima]; // Retorna el elemento del tope sin eliminarlo
        }

        ~PilaArray() {
            delete[] elementos; // Liberar memoria del array dinámico
        }
};

// --- Lista Enlazada
class PilaLista {
    private:
        struct Nodo {
            int dato;
            Nodo* siguiente;
            Nodo(int d) : dato(d), siguiente(nullptr) {}
        };
        Nodo* cima; // Puntero al tope de la pila
    public:
        PilaLista() : cima(nullptr) {}

        bool isEmpty() { return cima == nullptr; }

        void push(int dato) {
            Nodo* nuevo = new Nodo(dato);
            nuevo->siguiente = cima;
            cima = nuevo;
        }

        int pop() {
            if (isEmpty()) throw "Pila vacía";
            int dato = cima->dato;
            Nodo* temp = cima;
            cima = cima->siguiente;
            delete temp;
            return dato;
        }

        int top() {
            if (isEmpty()) throw "Pila vacía";
            return cima->dato;
        }

        ~PilaLista() {
            while (!isEmpty()) pop();
        }
};

// Apliciones prácticas:

// evaluacion de expresiones aritméticas (postfijas, prefijas)
int evaluarPostFija(string expr){
    stack<int> pila; // Usando stack de la STL
    for(char c : expr) {
        if(isdigit(c)){
            pila.push(c - '0'); // Convertir de char a int
        } else {
            int b = pila.top(); pila.pop(); // Obtener el segundo operando
            int a = pila.top(); pila.pop(); // Obtener el primer operando
            switch(c) {
                case '+': pila.push(a + b); break;
                case '-': pila.push(a - b); break;
                case '*': pila.push(a * b); break;
                case '/': 
                    if(b == 0) throw "División por cero";
                    pila.push(a / b); 
                    break;
                default: throw "Operador desconocido";
            }
        }
    }
    return pila.top(); 
}

int evaluarPrefija(string expr) {
    stack<int> pila; // Usando stack de la STL
    for (int i = expr.size() - 1; i >= 0; --i) {
        char c = expr[i];
        if (isdigit(c)) {
            pila.push(c - '0'); // Convertir de char a int
        } else {
            int a = pila.top(); pila.pop(); // Obtener el primer operando
            int b = pila.top(); pila.pop(); // Obtener el segundo operando
            switch (c) {
                case '+': pila.push(a + b); break;
                case '-': pila.push(a - b); break;
                case '*': pila.push(a * b); break;
                case '/':
                    if (b == 0) throw "División por cero";
                    pila.push(a / b);
                    break;
                default: throw "Operador desconocido";
            }
        }
    }
    return pila.top(); 
}

// Conversion de expresiones infijas a postfijas (Shunting Yard Algorithm)
string infijaAPostfija(const string& expr) {
    stack<char> operadores;
    string salida;
    for (char c : expr) {
        if (isdigit(c)) {
            salida += c; // Agregar operandos directamente a la salida
        } else if (c == '(') {
            operadores.push(c); // Push '(' en la pila
        } else if (c == ')') {
            while (!operadores.empty() && operadores.top() != '(') {
                salida += operadores.top(); // Pop hasta encontrar '('
                operadores.pop();
            }
            operadores.pop(); // Eliminar '(' de la pila
        } else { // Operador
            while (!operadores.empty() && operadores.top() != '(' &&
                   ((c == '+' || c == '-') || (c == '*' || c == '/' && (operadores.top() == '*' || operadores.top() == '/')))) {
                salida += operadores.top(); // Pop operadores de mayor o igual precedencia
                operadores.pop();
            }
            operadores.push(c); // Push el operador actual
        }
    }
    while (!operadores.empty()) {
        salida += operadores.top(); // Pop todos los operadores restantes
        operadores.pop();
    }
    return salida;
}

string postfijaAInfija(const string& expr) {
    stack<string> pila;
    for (char c : expr) {
        if (isdigit(c)) {
            pila.push(string(1, c)); // Convertir char a string y push
        } else { // Operador
            string b = pila.top(); pila.pop(); // Segundo operando
            string a = pila.top(); pila.pop(); // Primer operando
            string subExpr = "(" + a + c + b + ")"; // Formar sub-expresión
            pila.push(subExpr); // Push la sub-expresión de vuelta a la pila
        }
    }
    return pila.top(); // La expresión completa está en la cima de la pila
}

// Verificar paréntesis balanceados
bool parentesisBalanceados(const string& expr) {
    stack<char> pila;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pila.empty()) return false;
            char ultimo = pila.top();
            pila.pop();
            if ((c == ')' && ultimo != '(') ||
                (c == ']' && ultimo != '[') ||
                (c == '}' && ultimo != '{')) {
                return false;
            }
        }
    }
    return pila.empty(); // Si la pila está vacía, los paréntesis están balanceados
}

// Verificar si una cadena es palíndromo usando pila
bool esPalindromoConPila(const string& str) {
    stack<char> pila;
    string limpia = "";
    
    // Limpiar string y convertir a minúsculas
    for (char c : str) {
        if (isalnum(c)) {
            limpia += tolower(c);
        }
    }
    
    // Llenar la pila con la primera mitad
    int mitad = limpia.length() / 2;
    for (int i = 0; i < mitad; i++) {
        pila.push(limpia[i]);
    }
    
    // Comparar segunda mitad con la pila
    int inicio = (limpia.length() % 2 == 0) ? mitad : mitad + 1;
    for (int i = inicio; i < limpia.length(); i++) {
        if (pila.empty() || pila.top() != limpia[i]) {
            return false;
        }
        pila.pop();
    }
    
    return pila.empty();
}

// Conversión de decimal a binario usando pila
string decimalABinario(int numero) {
    if (numero == 0) return "0";
    
    stack<int> pila;
    while (numero > 0) {
        pila.push(numero % 2);
        numero /= 2;
    }
    
    string resultado = "";
    while (!pila.empty()) {
        resultado += to_string(pila.top());
        pila.pop();
    }
    
    return resultado;
}

// Invertir string usando pila
string invertirString(const string& str) {
    stack<char> pila;
    for (char c : str) {
        pila.push(c);
    }
    
    string resultado = "";
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }
    
    return resultado;
}

// Siguiente elemento mayor (Next Greater Element)
vector<int> siguienteElementoMayor(const vector<int>& arr) {
    vector<int> resultado(arr.size(), -1);
    stack<int> pila; // Stack de índices
    
    for (int i = 0; i < arr.size(); i++) {
        while (!pila.empty() && arr[pila.top()] < arr[i]) {
            resultado[pila.top()] = arr[i];
            pila.pop();
        }
        pila.push(i);
    }
    
    return resultado;
}

// Evaluar expresión con paréntesis (calcula primero lo que está en paréntesis)
int evaluarConParentesis(const string& expr) {
    // Primero convertir a postfija y luego evaluar
    string postfija = infijaAPostfija(expr);
    return evaluarPostFija(postfija);
}

// ======================= FUNCIÓN MAIN COMPLETA =======================
int main() {
    cout << "=== PRUEBAS COMPLETAS DE PILAS ===\n\n";
    
    try {
        // 1. PRUEBAS DE IMPLEMENTACIONES
        cout << "1. PRUEBAS DE IMPLEMENTACIONES:\n";
        cout << "================================\n";
        
        // Pila con Array
        cout << "PILA CON ARRAY:\n";
        PilaArray pilaArray(5);
        pilaArray.push(10);
        pilaArray.push(20);
        pilaArray.push(30);
        cout << "Top: " << pilaArray.top() << endl;
        cout << "Pop: " << pilaArray.pop() << endl;
        cout << "Top después de pop: " << pilaArray.top() << endl;
        cout << "¿Está vacía? " << (pilaArray.isEmpty() ? "Sí" : "No") << endl;
        
        // Pila con Lista Enlazada
        cout << "\nPILA CON LISTA ENLAZADA:\n";
        PilaLista pilaLista;
        pilaLista.push(100);
        pilaLista.push(200);
        pilaLista.push(300);
        cout << "Top: " << pilaLista.top() << endl;
        cout << "Pop: " << pilaLista.pop() << endl;
        cout << "Top después de pop: " << pilaLista.top() << endl;
        cout << "¿Está vacía? " << (pilaLista.isEmpty() ? "Sí" : "No") << endl;
        
        // 2. EVALUACIÓN DE EXPRESIONES
        cout << "\n\n2. EVALUACIÓN DE EXPRESIONES:\n";
        cout << "==============================\n";
        
        // Postfija
        string postfija1 = "23+4*";  // (2+3)*4 = 20
        string postfija2 = "234*+";  // 2+(3*4) = 14
        string postfija3 = "15+26-*"; // (1+5)*(2-6) = 6*(-4) = -24
        
        cout << "Postfija '" << postfija1 << "' = " << evaluarPostFija(postfija1) << " (esperado: 20)" << endl;
        cout << "Postfija '" << postfija2 << "' = " << evaluarPostFija(postfija2) << " (esperado: 14)" << endl;
        cout << "Postfija '" << postfija3 << "' = " << evaluarPostFija(postfija3) << " (esperado: -24)" << endl;
        
        // Prefija
        string prefija1 = "*+234";   // (2+3)*4 = 20
        string prefija2 = "+2*34";   // 2+(3*4) = 14
        string prefija3 = "*+15-26"; // (1+5)*(2-6) = 6*(-4) = -24
        
        cout << "\nPrefija '" << prefija1 << "' = " << evaluarPrefija(prefija1) << " (esperado: 20)" << endl;
        cout << "Prefija '" << prefija2 << "' = " << evaluarPrefija(prefija2) << " (esperado: 14)" << endl;
        cout << "Prefija '" << prefija3 << "' = " << evaluarPrefija(prefija3) << " (esperado: -24)" << endl;
        
        // 3. CONVERSIONES
        cout << "\n\n3. CONVERSIONES DE EXPRESIONES:\n";
        cout << "================================\n";
        
        string infija1 = "2+3*4";
        string infija2 = "(2+3)*4";
        string infija3 = "1+2*3-4";
        
        cout << "Infija: " << infija1 << " → Postfija: " << infijaAPostfija(infija1) << endl;
        cout << "Infija: " << infija2 << " → Postfija: " << infijaAPostfija(infija2) << endl;
        cout << "Infija: " << infija3 << " → Postfija: " << infijaAPostfija(infija3) << endl;
        
        // Postfija a Infija
        cout << "\nPostfija: " << postfija1 << " → Infija: " << postfijaAInfija(postfija1) << endl;
        cout << "Postfija: " << postfija2 << " → Infija: " << postfijaAInfija(postfija2) << endl;
        
        // 4. PARÉNTESIS BALANCEADOS
        cout << "\n\n4. VERIFICACIÓN DE PARÉNTESIS:\n";
        cout << "===============================\n";
        
        vector<string> expresiones = {
            "(())",
            "(()",
            "())",
            "(()())",
            "((()))",
            "()()(",
            "([{}])",
            "([)]",
            "{[()]}",
            "{[(])}"
        };
        
        for (const string& expr : expresiones) {
            cout << "'" << expr << "' → Balanceado: " << (parentesisBalanceados(expr) ? "Sí" : "No");
            cout << " | Extendido: " << (parentesisBalanceados(expr) ? "Sí" : "No") << endl;
        }
        
        // 5. APLICACIONES ADICIONALES
        cout << "\n\n5. APLICACIONES ADICIONALES:\n";
        cout << "=============================\n";
        
        // Palíndromo
        vector<string> palabras = {"radar", "hello", "level", "world", "A man a plan a canal Panama"};
        cout << "VERIFICACIÓN DE PALÍNDROMOS:\n";
        for (const string& palabra : palabras) {
            cout << "'" << palabra << "' → Palíndromo: " << (esPalindromoConPila(palabra) ? "Sí" : "No") << endl;
        }
        
        // Conversión decimal a binario
        cout << "\nCONVERSIÓN DECIMAL A BINARIO:\n";
        vector<int> numeros = {10, 25, 64, 128, 255};
        for (int num : numeros) {
            cout << num << " → " << decimalABinario(num) << endl;
        }
        
        // Invertir strings
        cout << "\nINVERTIR STRINGS:\n";
        vector<string> strings = {"hello", "world", "pila", "stack"};
        for (const string& str : strings) {
            cout << "'" << str << "' → '" << invertirString(str) << "'" << endl;
        }
        
        // Siguiente elemento mayor
        cout << "\nSIGUIENTE ELEMENTO MAYOR:\n";
        vector<int> arr = {4, 5, 2, 25, 7, 8};
        vector<int> nge = siguienteElementoMayor(arr);
        
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << "\nNGE:   ";
        for (int x : nge) cout << x << " ";
        cout << endl;
        
        // 6. PRUEBAS DE RENDIMIENTO
        cout << "\n\n6. PRUEBAS DE RENDIMIENTO:\n";
        cout << "==========================\n";
        
        // Medir tiempo de operaciones en pila grande
        const int N = 100000;
        
        auto inicio = chrono::high_resolution_clock::now();
        stack<int> pilaSTL;
        for (int i = 0; i < N; i++) {
            pilaSTL.push(i);
        }
        for (int i = 0; i < N; i++) {
            pilaSTL.pop();
        }
        auto fin = chrono::high_resolution_clock::now();
        
        auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
        cout << "Operaciones en pila STL con " << N << " elementos: " << duracion.count() << " ms" << endl;
        
        // 7. CASOS EXTREMOS Y MANEJO DE ERRORES
        cout << "\n\n7. MANEJO DE ERRORES:\n";
        cout << "=====================\n";
        
        try {
            cout << "Intentando evaluar expresión vacía..." << endl;
            evaluarPostFija("");
        } catch (const char* error) {
            cout << "Error capturado: " << error << endl;
        }
        
        try {
            cout << "Intentando división por cero en postfija..." << endl;
            evaluarPostFija("10/");
        } catch (const char* error) {
            cout << "Error capturado: " << error << endl;
        }
        
        // 8. EXPRESIONES COMPLEJAS
        cout << "\n\n8. EXPRESIONES COMPLEJAS:\n";
        cout << "=========================\n";
        
        vector<string> expresionesComplejas = {
            "1+2*3+4",
            "(1+2)*(3+4)",
            "1+2*3-4/2",
            "((1+2)*3-4)/5"
        };
        
        for (const string& expr : expresionesComplejas) {
            string postf = infijaAPostfija(expr);
            int resultado = evaluarConParentesis(expr);
            cout << "Infija: " << expr << " → Postfija: " << postf << " → Resultado: " << resultado << endl;
        }
        
        cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE ===\n";
        
    } catch (const char* error) {
        cout << "Error durante las pruebas: " << error << endl;
        return 1;
    } catch (const exception& e) {
        cout << "Excepción capturada: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}