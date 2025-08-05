#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(){
    // ========================================
    // ESTRUCTURAS, ENUMS, UNIONS Y MÁS EN C++
    // ========================================
    
    cout << "=== ESTRUCTURAS, ENUMS, UNIONS Y MÁS EN C++ ===" << "\n" << "\n";
    
    // Las estructuras de datos personalizadas permiten agrupar diferentes tipos
    // de datos bajo un mismo nombre, creando tipos de datos más complejos y útiles
    
    // ==========================================
    // 1. ESTRUCTURAS (STRUCT)
    // ==========================================
    cout << "1. ESTRUCTURAS (STRUCT):" << "\n";

    // Definición de una estructura
    struct Persona {
        string nombre;
        int edad;
        double altura;
        bool es_estudiante;
    };

    // Crear instancias de la estructura
    Persona persona1; 
    persona1.nombre = "Vanessa";
    persona1.edad = 28;
    persona1.altura = 1.60;
    persona1.es_estudiante = true;

    // Inicialización directa
    Persona persona2 = {"Pedro", 30, 1.75, false};

    // Inicializacón con lista o constructor (C+11)
    Persona persona3{"Ana", 22, 1.65, true};

    cout << "Persona 1:" << "\n";
    cout << "Nombre: " << persona1.nombre << "\n";
    cout << "Edad: " << persona1.edad << "\n";
    cout << "Altura: " << persona1.altura << "\n";
    cout << "Es estudiante: " << (persona1.es_estudiante ? "Sí" : "No") << "\n" << "\n";
    
    cout << "Persona 2:" << "\n";
    cout << "Nombre: " << persona2.nombre << ", " << "Edad: " << persona2.edad << ", "
         << "Altura: " << persona2.altura << ", "
         << "Es estudiante: " << (persona2.es_estudiante ? "Sí" : "No") << "\n" << "\n";

    cout << "Persona 3:" << "\n";
    cout << "Nombre: " << persona3.nombre << ", " << "Edad: " << persona3.edad << ", "
         << "Altura: " << persona3.altura << ", "
         << "Es estudiante: " << (persona3.es_estudiante ? "Sí" : "No") << "\n" << "\n";

    cout << "Tamaño de la estructura Persona: " << sizeof(Persona) << " bytes" << "\n" << "\n";

    // ==========================================
    // 2. ESTRUCTURAS CON FUNCIONES MIEMBRO
    // ==========================================
    cout << "2. ESTRUCTURAS CON FUNCIONES MIEMBRO:" << "\n";

    struct Rectangulo {
        double ancho;
        double alto;
        // función miembro para calcular el área
        double calcular_area() {
            return ancho*alto;
        }
        // calcular perimetro
        double calcular_perimetro() {
            return 2 * (ancho + alto);
        }

        // constructor (función especial para inicializar)
        Rectangulo(double a, double h) : ancho(a), alto(h) {}

        // constructor por defecto
        Rectangulo() : ancho(0), alto(0) {}
    };

    Rectangulo rect1(5.0, 3.0); // Crear un rectángulo con base 5.0 y altura 3.0
    Rectangulo rect2; // Crear un rectángulo usando el constructor por defecto
    rect2.ancho = 4.0; // Asignar base y altura después
    rect2.alto = 2.0;

    cout << "Rectángulo 1 (" << rect1.ancho << "x" << rect1.alto << "):" << endl;
    cout << "  Área: " << rect1.calcular_area() << endl;
    cout << "  Perímetro: " << rect1.calcular_perimetro() << endl;
    
    cout << "Rectángulo 2 (" << rect2.ancho << "x" << rect2.alto << "):" << endl;
    cout << "  Área: " << rect2.calcular_area() << endl;
    cout << "  Perímetro: " << rect2.calcular_perimetro() << endl;
    
    cout << "\n";

    // ==========================================
    // 3. ENUMERACIONES (ENUM)
    // ==========================================
    cout << "3. ENUMERACIONES (ENUM):" << endl;

    // Los enum permiten definir un tipo de dato que puede tener un conjunto limitado de valores
    // Son útiles para representar estados, opciones, etc.
    // ocupan en memoria el tamaño del tipo de dato más pequeño que pueda contener todos sus valores
    
    // Enum tradicional (C-style)
    enum Color {
        ROJO,
        VERDE,
        AZUL,
        AMARILLO
    };

    Color color_favorito = AZUL;
    cout << "Color favorito (valor numérico): " << color_favorito << "\n";

    enum DiaSemana {
        // Enum con valores personalizados
        LUNES = 1,
        MARTES = 2,
        MIERCOLES = 3,
        JUEVES = 4,
        VIERNES = 5,
        SABADO = 6,
        DOMINGO = 7
    };

    DiaSemana hoy = MIERCOLES;
    cout << "Hoy es día número: " << hoy << "\n";
    
    // Switch con enum
    cout << "Información del día: ";
    switch (hoy) {
        case LUNES:
            cout << "Inicio de semana laboral" << "\n";
            break;
        case MARTES:
        case MIERCOLES:
        case JUEVES:
            cout << "Día laboral en el medio de la semana" << "\n";
            break;
        case VIERNES:
            cout << "Último día laboral" << "\n";
            break;
        case SABADO:
        case DOMINGO:
            cout << "Fin de semana" << "\n";
            break;
    }
    
    cout << "\n";

    // ==========================================
    // 4. ENUM CLASS (C++11) - MÁS SEGURO
    // ==========================================
    cout << "4. ENUM CLASS (C++11):" << endl;

    enum class Estado {
        ACTIVO,
        INACTIVO,
        PENDIENTE,
        CANCELADO
    };

    enum class Tamano {
        PEQUENO,
        MEDIANO,
        GRANDE
    };

    Estado estado_actual = Estado::ACTIVO;
    //Tamano tamano_actual = Tamano::MEDIANO;

    cout << "Estado actual: ";
    switch (estado_actual) {
        case Estado::ACTIVO:
            cout << "Sistema funcionando correctamente" << endl;
            break;
        case Estado::INACTIVO:
            cout << "Sistema desactivado" << endl;
            break;
        case Estado::PENDIENTE:
            cout << "Esperando confirmación" << endl;
            break;
        case Estado::CANCELADO:
            cout << "Operación cancelada" << endl;
            break;
    }
    
    // No hay conflicto de nombres entre diferentes enum class
    // Estado::ACTIVO vs Tamaño::PEQUEÑO están en espacios diferentes

    cout << "\n";

    // ==========================================
    // 5. UNIONS
    // ==========================================
    cout << "5. UNIONS:" << endl;
    
    // Un union permite almacenar diferentes tipos en la misma ubicación de memoria
    // Solo se puede usar un miembro a la vez, ya que comparten la misma memoria
    // Ocupa el tamaño del miembro más grande

    union Dato {
        int entero;
        float flotante;
        char caracter;
        bool booleano;
    };

    Dato mi_dato;

    cout << "Tamaño de la union Dato: " << sizeof(Dato) << " bytes" << " es equivalente al tamaño del miembro más grande, en este caso, un float de 4 bytes.\n";

    // solo se usa un miembro a la vez
    mi_dato.entero = 42;
    cout << "Valor entero: " << mi_dato.entero << "\n";
    mi_dato.flotante = 3.14f; // Sobrescribe el entero
    cout << "Valor flotante: " << mi_dato.flotante << "\n";
    cout << "Valor entero después de usar flotante: " << mi_dato.entero << " ahora contiene basura.\n"; // Valor no válido

    cout << "\n";

    // ==========================================
    // 6. UNIONS ETIQUETADAS (TAGGED UNIONS)
    // ==========================================
    cout << "6. UNIONS ETIQUETADAS:" << endl;
    
    enum class TipoDato {
        ENTERO,
        FLOTANTE,
        CADENA
    };

    struct DatoEtiquetado {
        TipoDato tipo;
        union {
            int valor_entero;
            double valor_flotante;
            char valor_cadena[50]; // Cadena de caracteres con tamaño fijo
        };

        // constructor para entero
        DatoEtiquetado(int val) : tipo(TipoDato::ENTERO), valor_entero(val){}

        DatoEtiquetado(double val) : tipo(TipoDato::FLOTANTE), valor_flotante(val) {}

        // imprimir valor
        void imprimir(){
            switch (tipo){
                case TipoDato::ENTERO:
                    cout << "Valor entero: " << valor_entero << "\n";
                    break;
                case TipoDato::FLOTANTE:
                    cout << "Valor flotante: " << valor_flotante << "\n";
                    break;
                case TipoDato::CADENA:
                    cout << "Valor cadena: " << valor_cadena << "\n";
                    break;
            }
        }

    };

    DatoEtiquetado dato1(100); // Crear un dato entero
    DatoEtiquetado dato2(3.14); // Crear un dato flotante

    cout << "Datos etiquetados:" << "\n";
    dato1.imprimir();
    dato2.imprimir();

    cout << "\n";

    // ==========================================
    // 7. ESTRUCTURAS ANIDADAS
    // ==========================================
    cout << "7. ESTRUCTURAS ANIDADAS:" << "\n";
    
    struct Direccion {
        string calle;
        string ciudad;
        string codigo_postal;
        string pais;
    };

    struct Empleado {
        string nombre;
        int id;
        double salario;
        Direccion direccion; // Estructura anidada

        void mostrar_info() {
            cout << "Empleado: " << nombre << " (ID: " << id << ")" << "\n";
            cout << "Salario: $" << salario << "\n";
            cout << "Dirección: " << direccion.calle << ", " 
                 << direccion.ciudad << ", " << direccion.pais << "\n";
        }
    };

    Empleado emp1;
    emp1.nombre = "Carlos Rodríguez";
    emp1.id = 1001;
    emp1.salario = 55000.0;
    emp1.direccion = {"Av. Principal 123", "Madrid", "28001", "España"};
    
    emp1.mostrar_info();
    
    cout << "\n";


    // ==========================================
    // 8. ARRAYS DE ESTRUCTURAS
    // ==========================================
    cout << "8. ARRAYS DE ESTRUCTURAS:" << "\n";
    
    struct Producto {
        string nombre;
        double precio;
        int stock;
        
        void mostrar() {
            cout << std::setw(15) << nombre 
                 << " | $" << std::setw(8) << std::fixed << std::setprecision(2) << precio
                 << " | Stock: " << std::setw(3) << stock << "\n";
        }
    };

    Producto inventario[]={
        {"Laptop", 999.99, 10},
        {"Smartphone", 499.99, 25},
        {"Tablet", 299.99, 15},
        {"Monitor", 199.99, 5}
    };

    int num_productos = sizeof(inventario) / sizeof(Producto);

    cout << "INVENTARIO DE PRODUCTOS:" << "\n";
    cout << std::setw(15) << "Producto" << " | " << std::setw(8) << "Precio" 
         << " | " << "Stock" << std::setw(3) << "\n";
    cout << string(40, '-') << "\n";
    
    for (int i = 0; i < num_productos; i++) {
        inventario[i].mostrar();
    }

    // ==========================================
    // 9. VECTOR DE ESTRUCTURAS
    // ==========================================
    cout << "9. VECTOR DE ESTRUCTURAS:" << "\n";

    struct Estudiante {
        string nombre;
        int edad;
        vector<double> calificaciones;

        double calcular_promedio() const { // se marca como const porque no modifica el objeto
            if(calificaciones.empty()) return 0.0;
            double suma = 0.0;
            for(double calificacion : calificaciones){
                suma += calificacion;
            }
            return suma / calificaciones.size();
        }
    };

    vector<Estudiante> clase;

    // Agregar estudiantes al vector
    clase.push_back({"Ana Pérez", 20, {8.5, 9.0, 7.5, 8.8}});
    clase.push_back({"Juan Silva", 21, {7.0, 8.5, 9.2, 8.0}});
    clase.push_back({"María Torres", 19, {9.5, 9.8, 9.0, 9.3}});
    
    cout << "REPORTE DE CALIFICACIONES:" << "\n";
    cout << string(50, '=') << "\n";
    
    for (const auto& estudiante : clase) {
        cout << "Estudiante: " << estudiante.nombre 
             << " (Edad: " << estudiante.edad << ")" << "\n";
        cout << "Calificaciones: ";
        for (double cal : estudiante.calificaciones) {
            cout << cal << " ";
        }
        cout << "\n";
        cout << "Promedio: " << std::fixed << std::setprecision(2) 
             << estudiante.calcular_promedio() << "\n" << "\n";
    };


    // ==========================================
    // 10. TYPEDEF Y USING
    // ==========================================
    cout << "10. TYPEDEF Y USING:" << "\n";
    // typedef permite crear un alias para un tipo de dato
    // typedef (estilo C)
    typedef struct {
        double x, y;
    } Punto2D;

    // using (estilo C++)
    using Punto3D = struct {
        double x, y, z;
    };

    // Alias para tipos complejos 
    using ListaEnteros = vector<int>;
    // using MapaNombres = vector<string>;

    Punto2D p1 = {3.0, 4.0};
    Punto3D p2 = {1.0, 2.0, 3.0};

    cout << "Punto 2D: (" << p1.x << ", " << p1.y << ")" << "\n";
    cout << "Punto 3D: (" << p2.x << ", " << p2.y << ", " << p2.z << ")" << "\n";
    
    ListaEnteros numeros = {1, 2, 3, 4, 5};
    cout << "Lista de enteros: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << "\n" << "\n";

    // ==========================================
    // 11. ESTRUCTURAS COMO PARÁMETROS DE FUNCIONES
    // ==========================================
    cout << "11. ESTRUCTURAS COMO PARÁMETROS:" << "\n";

    // Paso por valor
    auto mostrar_persona_copia = [](Persona p) { // Función lambda que recibe una copia de Persona
        cout << "Copia - Nombre: " << p.nombre << ", Edad: " << p.edad << "\n";
        p.edad = 100;  // No afecta el original
    };

    // Paso por referencia
    auto mostrar_persona_referencia = [](const Persona& p){ // Función lambda que recibe una referencia constante de Persona
        cout << "Referencia - Nombre: " << p.nombre << ", Edad: " << p.edad << "\n";
        // p.edad = 100; // No se puede modificar porque es const
    };

    // Paso por referencia modificable
    auto cumpleanos = [](Persona& p){
        p.edad++; // Incrementa la edad
        cout << "Feliz cumpleaños " << p.nombre << "! Ahora tienes " << p.edad << " años." << "\n";
    };

    Persona test_persona{"Laura", 30, 1.70, false};

    cout << "Original: " << test_persona.nombre << ", " << test_persona.edad << " años" << "\n";
    mostrar_persona_copia(test_persona);
    cout << "Después de copia: " << test_persona.edad << " años" << "\n";
    
    mostrar_persona_referencia(test_persona);
    cumpleanos(test_persona);
    
    cout << "\n";

    // ==========================================
    // 12. EJEMPLO PRÁCTICO: SISTEMA DE BIBLIOTECA
    // ==========================================
    cout << "12. EJEMPLO PRÁCTICO - SISTEMA DE BIBLIOTECA:" << endl;

    enum class EstadoLibro {
        DISPONIBLE,
        PRESTADO,
        RESERVADO,
        MANTENIMIENTO
    };

    struct libro {
        string titulo;
        string autor;
        string isbn;
        int anio_publicacion;
        EstadoLibro estado;

        void mostrar_estado() const {
            cout << "\"" << titulo << "\" por " << autor << " - ";
            switch (estado) {
                case EstadoLibro::DISPONIBLE:
                    cout << "DISPONIBLE" << endl;
                    break;
                case EstadoLibro::PRESTADO:
                    cout << "PRESTADO" << endl;
                    break;
                case EstadoLibro::RESERVADO:
                    cout << "RESERVADO" << endl;
                    break;
                case EstadoLibro::MANTENIMIENTO:
                    cout << "EN MANTENIMIENTO" << endl;
                    break;
            }
        }
    };

    struct Biblioteca {
        string nombre;
        vector<libro> libros;

        void agregar_libro(const libro& nuevo_libro) {
            libros.push_back(nuevo_libro);
        }

        void mostrar_catalogo() {
            cout << "Catálogo de " << nombre << ":\n";
            for (const auto& lib : libros) {
                cout << "- " << lib.titulo << " (" << lib.anio_publicacion << ") - ";
                lib.mostrar_estado();
            }
        }

        int contar_disponibles() {
            int count = 0;
            for(const auto& lib : libros) {
                if(lib.estado == EstadoLibro::DISPONIBLE) {
                    count++;
                }
            }
            return count;
        }
    };

    Biblioteca biblioteca_central;
    biblioteca_central.nombre = "BIBLIOTECA CENTRAL";
    
    biblioteca_central.agregar_libro({"El Quijote", "Miguel de Cervantes", "123-456", 1605, EstadoLibro::DISPONIBLE});
    biblioteca_central.agregar_libro({"Cien Años de Soledad", "Gabriel García Márquez", "789-012", 1967, EstadoLibro::PRESTADO});
    biblioteca_central.agregar_libro({"1984", "George Orwell", "345-678", 1949, EstadoLibro::DISPONIBLE});
    biblioteca_central.agregar_libro({"El Principito", "Antoine de Saint-Exupéry", "901-234", 1943, EstadoLibro::RESERVADO});
    
    biblioteca_central.mostrar_catalogo();
    cout << "\nLibros disponibles: " << biblioteca_central.contar_disponibles() << endl;
    
    cout << endl;

    // ==========================================
    // 13. BUENAS PRÁCTICAS Y CONSEJOS
    // ==========================================
    cout << "13. BUENAS PRÁCTICAS:" << endl;
    cout << "✅ ESTRUCTURAS:" << endl;
    cout << "• Usar nombres descriptivos para miembros" << endl;
    cout << "• Agrupar datos relacionados lógicamente" << endl;
    cout << "• Considerar constructores para inicialización" << endl;
    cout << "• Usar const para parámetros de solo lectura" << endl;
    cout << "• Preferir paso por referencia para estructuras grandes" << endl;
    
    cout << "\n✅ ENUMS:" << endl;
    cout << "• Usar enum class en lugar de enum tradicional" << endl;
    cout << "• Nombres en MAYÚSCULAS para valores de enum" << endl;
    cout << "• Asignar valores específicos cuando sea importante" << endl;
    cout << "• Usar switch para manejar todos los casos" << endl;
    
    cout << "\n✅ UNIONS:" << endl;
    cout << "• Usar tagged unions para seguridad de tipos" << endl;
    cout << "• Recordar que solo un miembro es válido a la vez" << endl;
    cout << "• Considerar std::variant (C++17) como alternativa moderna" << endl;
    
    cout << endl;
    
    // ==========================================
    // 14. COMPARACIÓN STRUCT VS CLASS
    // ==========================================
    cout << "14. STRUCT VS CLASS:" << endl;
    cout << "┌─────────────────┬─────────────────┬─────────────────┐" << endl;
    cout << "│    ASPECTO      │     STRUCT      │      CLASS      │" << endl;
    cout << "├─────────────────┼─────────────────┼─────────────────┤" << endl;
    cout << "│ Acceso default  │     public      │     private     │" << endl;
    cout << "│ Herencia def.   │     public      │     private     │" << endl;
    cout << "│ Uso típico      │ Datos simples   │ Objetos OOP     │" << endl;
    cout << "│ Constructores   │ Sí (permitido)  │ Sí (común)      │" << endl;
    cout << "│ Funciones miemb.│ Sí (permitido)  │ Sí (común)      │" << endl;
    cout << "└─────────────────┴─────────────────┴─────────────────┘" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE SINTAXIS
    // ==========================================
    cout << "RESUMEN DE SINTAXIS:" << endl;
    cout << "// Estructura" << endl;
    cout << "struct Nombre { tipo miembro; };" << endl;
    cout << "Nombre instancia = {valor};" << endl;
    cout << endl;
    cout << "// Enum tradicional" << endl;
    cout << "enum Color { ROJO, VERDE, AZUL };" << endl;
    cout << endl;
    cout << "// Enum class (C++11)" << endl;
    cout << "enum class Estado { ACTIVO, INACTIVO };" << endl;
    cout << "Estado s = Estado::ACTIVO;" << endl;
    cout << endl;
    cout << "// Union" << endl;
    cout << "union Dato { int i; float f; };" << endl;
    cout << endl;
    cout << "// Typedef/Using" << endl;
    cout << "typedef struct { ... } Alias;" << endl;
    cout << "using Alias = struct { ... };" << endl;

    return 0;
}