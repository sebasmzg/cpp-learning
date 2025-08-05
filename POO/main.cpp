#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// ==========================================
// 1. CLASES Y OBJETOS BÁSICOS
// ==========================================
// Ejemplo de clase con atributos privados, constructores, destructores,
// getters, setters y métodos para operaciones bancarias.
class CuentaBancaria {
private:
    string titular;
    double saldo;
    string numero_cuenta;

public:
    // Constructor
    CuentaBancaria(string t, double s, string num)
        : titular(t), saldo(s), numero_cuenta(num) {
        cout << "Cuenta creada para " << titular
             << " con saldo inicial de " << saldo << "\n";
    }

    // Destructor
    ~CuentaBancaria() {
        cout << "Cuenta de " << titular << " cerrada.\n";
    }

    // Métodos públicos (getters)
    string get_titular() const { return titular; }
    double get_saldo() const { return saldo; }
    string get_numero_cuenta() const { return numero_cuenta; }

    // Métodos públicos (operaciones)
    void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
            cout << "Depósito de " << cantidad
                 << " realizado. Nuevo saldo: " << saldo << "\n";
        } else {
            cout << "Cantidad inválida para depósito.\n";
        }
    }

    bool retirar(double cantidad) {
        if (cantidad > 0 && cantidad <= saldo) {
            saldo -= cantidad;
            cout << "Retiro de " << cantidad
                 << " realizado. Nuevo saldo: " << saldo << "\n";
            return true;
        } else {
            cout << "Cantidad inválida para retiro.\n";
            return false;
        }
    }

    void mostrar_info() const {
        cout << "Titular: " << titular << "\n";
        cout << "Número de cuenta: " << numero_cuenta << "\n";
        cout << "Saldo actual: " << saldo << "\n";
    }
};

// ==========================================
// 2. ENCAPSULACIÓN Y CONTROL DE ACCESO
// ==========================================
// Ejemplo de clase con atributos privados y protegidos,
// validación interna y métodos virtuales.
class Persona {
private:
    string nombre;
    int edad;
    string email;

    // Método privado de validación
    bool validar_email(const string& email) {
        return email.find('@') != string::npos; // Verifica si contiene '@'
        // string::npos indica que no se encontró el carácter
    }

protected:
    // La diferencia entre private y protected es que los miembros protected
    // pueden ser accedidos por clases derivadas (herencia)
    string documento_id;

public:
    // Constructor
    Persona(string n, int e, string em, string doc)
        : nombre(n), edad(e), email(em), documento_id(doc) {
        set_email(em); // usa setter para validar email
    }

    // Getters
    string get_nombre() const { return nombre; }
    int get_edad() const { return edad; }
    string get_email() const { return email; }
    string get_documento_id() const { return documento_id; }

    // Setters con validación
    void set_nombre(const string& n) {
        if (!n.empty()) {
            nombre = n;
        } else {
            cout << "Nombre no puede estar vacío.\n";
        }
    }

    void set_edad(int e) {
        if (e >= 0) {
            edad = e;
        } else {
            cout << "Edad no puede ser negativa.\n";
        }
    }

    void set_email(const string& em) {
        if (validar_email(em)) {
            email = em;
        } else {
            cout << "Email inválido. no se pudo actualizar\n";
        }
    }

    void set_documento_id(const string& doc) { documento_id = doc; }

    virtual void mostrar_info() const { // virtual para permitir polimorfismo
        cout << "Nombre: " << nombre << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Email: " << email << "\n";
        cout << "Documento ID: " << documento_id << "\n";
    }
};

// ==========================================
// 3. HERENCIA
// ==========================================
// Clase base con métodos virtuales para permitir polimorfismo.
class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio;
    double precio;

public:
    Vehiculo(string m, string mod, int a, double p)
        : marca(m), modelo(mod), anio(a), precio(p) {}

    virtual void mostrar_info() const {
        cout << "Marca: " << marca << "\n";
        cout << "Modelo: " << modelo << "\n";
        cout << "Año: " << anio << "\n";
        cout << "Precio: " << precio << "\n";
    }

    virtual void arrancar() const {
        cout << "El vehículo está arrancando...\n";
    }

    virtual ~Vehiculo() { // Destructor virtual para liberar recursos
        cout << "Vehículo destruido.\n";
    }
};

// Clase derivada: Automóvil
class Automovil : public Vehiculo {
private:
    int numero_puertas;
    bool es_automatico;

public:
    Automovil(string m, string mod, int a, double p, int puertas, bool automatico)
        : Vehiculo(m, mod, a, p), numero_puertas(puertas), es_automatico(automatico) {}

    void mostrar_info() const override {
        Vehiculo::mostrar_info();
        cout << "Número de puertas: " << numero_puertas << "\n";
        cout << "Transmisión: " << (es_automatico ? "Automático" : "Manual") << "\n";
    }

    void arrancar() const override {
        cout << "El automóvil " << marca << " " << modelo << " está arrancando...\n";
    }

    void abrir_cajuela() const {
        cout << "Abriendo la cajuela del automóvil " << marca << " " << modelo << "\n";
    }
};

// Clase derivada: Motocicleta
class Motocicleta : public Vehiculo {
private:
    int cilindrada;
    bool tiene_sidecar;

public:
    Motocicleta(string ma, string mo, int a, double p, int cc, bool sidecar)
        : Vehiculo(ma, mo, a, p), cilindrada(cc), tiene_sidecar(sidecar) {}

    void mostrar_info() const override {
        Vehiculo::mostrar_info();
        cout << "Cilindrada: " << cilindrada << "cc" << "\n";
        cout << "Sidecar: " << (tiene_sidecar ? "Sí" : "No") << "\n";
    }

    void arrancar() const override {
        cout << "La motocicleta " << marca << " " << modelo
             << " arranca con botón de encendido" << "\n";
    }

    void hacer_caballito() const {
        cout << "¡Haciendo caballito!" << "\n";
    }
};

// ==========================================
// 5. CLASES ABSTRACTAS Y FUNCIONES VIRTUALES PURAS
// ==========================================
// Clase abstracta (no se puede instanciar)
class Figura {
protected:
    string color;

public:
    Figura(string c) : color(c) {}

    // función virtual pura = clase abstracta
    virtual double calcular_area() const = 0;
    virtual double calcular_perimetro() const = 0;
    virtual void dibujar() const = 0;

    // función virtual normal
    virtual void mostrar_color() const {
        cout << "Color de la figura: " << color << "\n";
    }

    virtual ~Figura() = default; // Destructor virtual por defecto
};

// Clase derivada: Círculo
class Circulo : public Figura {
private:
    double radio;
    static const double PI; // constante de clase en tiempo de compilación

public:
    Circulo(string c, double r) : Figura(c), radio(r) {}

    double calcular_area() const override {
        return PI * radio * radio;
    }

    double calcular_perimetro() const override {
        return 2 * PI * radio;
    }

    void dibujar() const override {
        cout << "Dibujando un círculo de radio " << radio << endl;
    }
};

const double Circulo::PI = 3.14159;

// Clase derivada: Rectángulo
class Rectangulo : public Figura {
private:
    double ancho;
    double alto;

public:
    Rectangulo(string c, double a, double h) : Figura(c), ancho(a), alto(h) {}

    double calcular_area() const override {
        return ancho * alto;
    }

    double calcular_perimetro() const override {
        return 2 * (ancho + alto);
    }

    void dibujar() const override {
        cout << "Dibujando un rectángulo de " << ancho << "x" << alto << endl;
    }
};

// ==========================================
// 6. SOBRECARGA DE OPERADORES
// ==========================================
// Ejemplo de sobrecarga para operaciones vectoriales.
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Getters
    double get_x() const { return x; }
    double get_y() const { return y; }

    // Sobrecarga del operador +
    Vector2D operator+(const Vector2D& otro) const {
        return Vector2D(x + otro.x, y + otro.y);
    }

    // Sobrecarga del operador -
    Vector2D operator-(const Vector2D& otro) const {
        return Vector2D(x - otro.x, y - otro.y);
    }

    // Sobrecarga del operador * (por escalar)
    Vector2D operator*(double escalar) const {
        return Vector2D(x * escalar, y * escalar);
    }

    // Sobrecarga del operador ==
    bool operator==(const Vector2D& otro) const {
        return (x == otro.x) && (y == otro.y);
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Sobrecarga del operador +=
    Vector2D& operator+=(const Vector2D& otro) {
        x += otro.x;
        y += otro.y;
        return *this;
    }

    double magnitud() const {
        return std::sqrt(x * x + y * y);
    }
};

// ==========================================
// 7. COMPOSICIÓN Y AGREGACIÓN
// ==========================================
// Ejemplo de composición: un coche "tiene" un motor.
class Motor {
    private:
        int potencia;
        string tipo;
        
    public:
        Motor(int p, string t) : potencia(p), tipo(t) {}
        
        void encender() {
            cout << "Motor " << tipo << " de " << potencia << "HP encendido" << endl;
        }
        
        void mostrar_info() const {
            cout << "Motor: " << tipo << ", " << potencia << "HP" << endl;
        }
};

class Coche {
    private:
        string marca;
        Motor motor;  // Composición: el coche "tiene" un motor
        
    public:
        Coche(string m, int potencia_motor, string tipo_motor) 
            : marca(m), motor(potencia_motor, tipo_motor) {}
        
        void arrancar() {
            cout << "Arrancando " << marca << endl;
            motor.encender();
        }
        
        void mostrar_info() const {
            cout << "Coche: " << marca << endl;
            motor.mostrar_info();
        }
};

// ==========================================
// 8. MÉTODOS Y VARIABLES ESTÁTICAS
// ==========================================
// Ejemplo de clase con miembros estáticos para contar instancias.
// Los miembros estáticos son compartidos por todas las instancias de la clase.
class Contador {
    private:
        static int total_objetos;  // Variable estática
        int id;
        
    public:
        Contador() {
            id = ++total_objetos;  // Incrementar contador global
            cout << "Objeto " << id << " creado" << endl;
        }
        
        ~Contador() {
            --total_objetos;
            cout << "Objeto " << id << " destruido" << endl;
        }
        
        static int get_total() {  // Método estático
            return total_objetos;
        }
        
        int get_id() const {
            return id;
        }
        
        static void mostrar_info() {
            cout << "Total de objetos creados: " << total_objetos << endl;
        }
    };
// Inicializar variable estática
int Contador::total_objetos = 0;

// ==========================================
// 9. EJEMPLO PRÁCTICO: SISTEMA DE EMPLEADOS
// ==========================================
class Empleado {
    protected:
        string nombre;
        int id;
        double salario_base;
        
    public:
        Empleado(string n, int i, double s) : nombre(n), id(i), salario_base(s) {}
        
        virtual double calcular_salario() const {
            return salario_base;
        }
        
        virtual void mostrar_info() const {
            cout << "ID: " << id << " | Nombre: " << nombre 
                 << " | Salario: $" << calcular_salario() << endl;
        }
        
        string get_nombre() const { return nombre; }
        int get_id() const { return id; }
        
        virtual ~Empleado() = default;

        //Virtual permite que se pueda redefinir este método en clases derivadas
        // default permite que el compilador genere un destructor por defecto
    };
    
class EmpleadoTiempoCompleto : public Empleado {
private:
    double bono_anual;
    
public:
    EmpleadoTiempoCompleto(string n, int i, double s, double b) 
        : Empleado(n, i, s), bono_anual(b) {}
        
    double calcular_salario() const override {
        return salario_base + (bono_anual / 12);  // Bono mensualizado
    }
    
    void mostrar_info() const override {
        cout << "[TIEMPO COMPLETO] ";
        Empleado::mostrar_info();
        cout << "  Bono anual: $" << bono_anual << endl;
    }
};

class EmpleadoPorHoras : public Empleado {
private:
    int horas_trabajadas;
    double tarifa_por_hora;
    
public:
    EmpleadoPorHoras(string n, int i, double tarifa, int horas) 
        : Empleado(n, i, 0), tarifa_por_hora(tarifa), horas_trabajadas(horas) {}
        
    double calcular_salario() const override {
        double salario_regular = std::min(40, horas_trabajadas) * tarifa_por_hora;
        double salario_extra = std::max(0, horas_trabajadas - 40) * tarifa_por_hora * 1.5;
        return salario_regular + salario_extra;
    }
    
    void mostrar_info() const override {
        cout << "[POR HORAS] ";
        Empleado::mostrar_info();
        cout << "  Horas: " << horas_trabajadas << " | Tarifa: $" << tarifa_por_hora << "/h" << endl;
    }
};
    
class Empresa {
private:
    string nombre;
    vector<std::unique_ptr<Empleado>> empleados;
    // Usamos punteros inteligentes para manejar memoria automáticamente 
    
public:
    Empresa(string n) : nombre(n) {}
    
    void agregar_empleado(std::unique_ptr<Empleado> emp) {
        empleados.push_back(std::move(emp));
        // std::move porque unique_ptr no se puede copiar
        // std::move permite transferir la propiedad del puntero sin copiar

    }
    
    void mostrar_nomina() const {
        cout << "\n=== NÓMINA DE " << nombre << " ===" << endl;
        cout << string(50, '=') << endl;
        
        double total_nomina = 0;
        for (const auto& emp : empleados) {
            emp->mostrar_info();
            total_nomina += emp->calcular_salario();
            cout << endl;
        }
        
        cout << string(50, '-') << endl;
        cout << "TOTAL NÓMINA: $" << std::fixed << std::setprecision(2) 
                << total_nomina << endl;
    }
    
    Empleado* buscar_empleado(int id) {
        for (const auto& emp : empleados) {
            if (emp->get_id() == id) {
                return emp.get();
            }
        }
        return nullptr;
    }
};


// ==========================================
// MAIN
// ==========================================
int main() {
    cout << "=== PROGRAMACIÓN ORIENTADA A OBJETOS EN C++ ===" << endl << endl;

    // ==========================================
    // 1. CLASES Y OBJETOS BÁSICOS
    // ==========================================
    cout << "1. CLASES Y OBJETOS BÁSICOS:" << "\n";
    CuentaBancaria cuenta1("Ana García", 1500.0, "001-2345");
    cuenta1.mostrar_info();
    cuenta1.depositar(500.0);
    cuenta1.retirar(200.0);
    cout << "\n";

    // ==========================================
    // 2. ENCAPSULACIÓN Y CONTROL DE ACCESO
    // ==========================================
    cout << "2. ENCAPSULACIÓN Y CONTROL DE ACCESO:" << "\n";
    Persona persona1("María López", 28, "maria@email.com", "12345678");
    persona1.mostrar_info();
    persona1.set_email("email_malo");
    cout << "Email después de validación: " << persona1.get_email() << "\n\n";

    // ==========================================
    // 3. HERENCIA
    // ==========================================
    cout << "3. HERENCIA:" << "\n";
    Automovil auto1("Toyota", "Corolla", 2022, 25000, 4, true);
    Motocicleta moto1("Honda", "CBR600", 2021, 12000, 600, false);
    auto1.mostrar_info();
    auto1.arrancar();
    auto1.abrir_cajuela();
    moto1.mostrar_info();
    moto1.arrancar();
    moto1.hacer_caballito();
    cout << "\n";

    // ==========================================
    // 4. POLIMORFISMO
    // ==========================================
    cout << "4. POLIMORFISMO:" << "\n";
    vector<std::unique_ptr<Vehiculo>> garage;
    garage.push_back(std::make_unique<Automovil>("BMW", "X5", 2023, 65000, 4, true));
    garage.push_back(std::make_unique<Motocicleta>("Yamaha", "R1", 2022, 18000, 1000, false));
    for (const auto& vehiculo : garage) {
        cout << string(40, '-') << "\n";
        vehiculo->mostrar_info();
        vehiculo->arrancar();
    }
    cout << "\n";

    // ==========================================
    // 5. CLASES ABSTRACTAS
    // ==========================================
    cout << "5. CLASES ABSTRACTAS:" << "\n";
    vector<std::unique_ptr<Figura>> figuras;
    figuras.push_back(std::make_unique<Circulo>("rojo", 5.0));
    figuras.push_back(std::make_unique<Rectangulo>("azul", 4.0, 6.0));
    for (const auto& figura : figuras) {
        cout << string(30, '-') << "\n";
        figura->mostrar_color();
        figura->dibujar();
        cout << "Área: " << std::fixed << std::setprecision(2) << figura->calcular_area() << "\n";
        cout << "Perímetro: " << std::fixed << std::setprecision(2) << figura->calcular_perimetro() << "\n\n";
    }

    // ==========================================
    // 6. SOBRECARGA DE OPERADORES
    // ==========================================
    cout << "6. SOBRECARGA DE OPERADORES:" << "\n";
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    Vector2D v3 = v1 + v2;
    Vector2D v4 = v1 - v2;
    Vector2D v5 = v1 * 2;
    cout << "v1 = " << v1 << "\n";
    cout << "v2 = " << v2 << "\n";
    cout << "v1 + v2 = " << v3 << "\n";
    cout << "v1 - v2 = " << v4 << "\n";
    cout << "v1 * 2 = " << v5 << "\n";
    cout << "v1 == v2: " << (v1 == v2 ? "Sí" : "No") << "\n";
    cout << "Magnitud de v1: " << v1.magnitud() << "\n";
    v1 += v2;
    cout << "v1 después de += v2: " << v1 << "\n\n";

    // ==========================================
    // 7. COMPOSICIÓN Y AGREGACIÓN
    // ==========================================
    cout << "7. COMPOSICIÓN Y AGREGACIÓN:" << "\n";
    Coche mi_coche("Tesla Model 3", 350, "Eléctrico");
    mi_coche.mostrar_info();
    mi_coche.arrancar();

    cout << "\n";

    // ==========================================
    // 8. MÉTODOS Y VARIABLES ESTÁTICAS
    // ==========================================
    cout << "8. MÉTODOS Y VARIABLES ESTÁTICAS:" << endl;
    
    
    cout << "Creando objetos Contador:" << endl;
    Contador::mostrar_info();
    
    {
        Contador c1;
        Contador c2;
        Contador c3;
        
        cout << "Total actual: " << Contador::get_total() << endl;
        cout << "ID del objeto c2: " << c2.get_id() << endl;
    }  // Los objetos se destruyen aquí
    
    cout << "Después de destruir objetos:" << endl;
    Contador::mostrar_info();
    
    cout << "\n";

    // ==========================================
    // 9. EJEMPLO PRÁCTICO: SISTEMA DE EMPLEADOS
    // ==========================================
    cout << "9. EJEMPLO PRÁCTICO - SISTEMA DE EMPLEADOS:" << "\n";

    Empresa mi_empresa("TechCorp Solutions");
    
    mi_empresa.agregar_empleado(
        std::make_unique<EmpleadoTiempoCompleto>("Ana Rodríguez", 1001, 4500, 6000)
    );
    mi_empresa.agregar_empleado(
        std::make_unique<EmpleadoPorHoras>("Carlos Pérez", 1002, 25, 45)
    );
    mi_empresa.agregar_empleado(
        std::make_unique<EmpleadoTiempoCompleto>("Luis García", 1003, 5200, 8000)
    );
    mi_empresa.agregar_empleado(
        std::make_unique<EmpleadoPorHoras>("María Torres", 1004, 30, 35)
    );
    
    mi_empresa.mostrar_nomina();
    
    // Buscar empleado
    Empleado* emp_encontrado = mi_empresa.buscar_empleado(1002);
    if (emp_encontrado) {
        cout << "\nEmpleado encontrado: " << emp_encontrado->get_nombre() << endl;
    }
    
    cout << endl;

    // ==========================================
    // 10. PRINCIPIOS DE LA POO
    // ==========================================
    cout << "10. PRINCIPIOS FUNDAMENTALES DE LA POO:" << endl;
    cout << string(50, '=') << endl;
    
    cout << "🔒 ENCAPSULACIÓN:" << endl;
    cout << "  • Ocultar detalles internos de implementación" << endl;
    cout << "  • Controlar acceso a través de métodos públicos" << endl;
    cout << "  • Usar private/protected para datos sensibles" << endl;
    cout << "  • Validar datos en setters" << endl << endl;
    
    cout << "🧬 HERENCIA:" << endl;
    cout << "  • Reutilizar código de clases existentes" << endl;
    cout << "  • Crear jerarquías de clases relacionadas" << endl;
    cout << "  • Especializar comportamiento en clases derivadas" << endl;
    cout << "  • Usar 'is-a' relationship" << endl << endl;
    
    cout << "🎭 POLIMORFISMO:" << endl;
    cout << "  • Un mismo interfaz, múltiples implementaciones" << endl;
    cout << "  • Usar funciones virtuales para late binding" << endl;
    cout << "  • Permite escribir código genérico" << endl;
    cout << "  • Facilita extensibilidad del código" << endl << endl;
    
    cout << "🎨 ABSTRACCIÓN:" << endl;
    cout << "  • Simplificar sistemas complejos" << endl;
    cout << "  • Mostrar solo lo esencial al usuario" << endl;
    cout << "  • Usar clases abstractas para contratos" << endl;
    cout << "  • Definir interfaces claras" << endl << endl;
    
    // ==========================================
    // BUENAS PRÁCTICAS
    // ==========================================
    cout << "BUENAS PRÁCTICAS EN POO:" << endl;
    cout << "✅ DISEÑO:" << endl;
    cout << "• Una clase, una responsabilidad (SRP)" << endl;
    cout << "• Favorecer composición sobre herencia" << endl;
    cout << "• Usar nombres descriptivos para clases y métodos" << endl;
    cout << "• Mantener interfaces simples y cohesivas" << endl;
    
    cout << "\n✅ IMPLEMENTACIÓN:" << endl;
    cout << "• Inicializar en lista de inicialización" << endl;
    cout << "• Usar const para métodos que no modifican" << endl;
    cout << "• Implementar destructor virtual en clases base" << endl;
    cout << "• Usar smart pointers para gestión automática" << endl;
    
    cout << "\n✅ MANTENIMIENTO:" << endl;
    cout << "• Documentar interfaces públicas" << endl;
    cout << "• Escribir tests unitarios para clases" << endl;
    cout << "• Refactorizar cuando sea necesario" << endl;
    cout << "• Seguir principios SOLID" << endl;
    
    cout << endl;
    
    // ==========================================
    // RESUMEN DE SINTAXIS
    // ==========================================
    cout << "RESUMEN DE SINTAXIS POO:" << endl;
    cout << "class Nombre {" << endl;
    cout << "private: // Solo accesible desde la misma clase" << endl;
    cout << "    tipo miembro;" << endl;
    cout << "protected: // Accesible por clases derivadas" << endl;
    cout << "    tipo miembro;" << endl;
    cout << "public: // Accesible desde cualquier lugar" << endl;
    cout << "    Nombre(); // Constructor" << endl;
    cout << "    ~Nombre(); // Destructor" << endl;
    cout << "    virtual tipo metodo() = 0; // Función virtual pura" << endl;
    cout << "    tipo metodo() const; // Método const" << endl;
    cout << "};" << endl;
    cout << endl;
    cout << "class Derivada : public Base { ... }; // Herencia" << endl;
    cout << "objeto.metodo(); // Llamada a método" << endl;
    cout << "auto ptr = std::make_unique<Clase>(); // Smart pointer" << endl;
    
    return 0;
}