#include "../include/Hospital.h"
#include "../include/Doctor.h"
#include "../include/Enfermero.h"
#include "../include/Administrativo.h"
#include <iostream>
#include <iomanip>   
#include <algorithm>

using namespace std;

Hospital::Hospital(const string& nombre):nombre(nombre){
    if(nombre.empty()){
        throw invalid_argument("La clase hospital debe tener un nombre");
    }
};

void Hospital::agregar_personal(unique_ptr<PersonalMedico> persona){
    if(!persona){
        throw invalid_argument("No se puede agregar personal nulo");
    }
    if(buscar_por_id(persona->get_id()) != nullptr){
        throw runtime_error("Ya existe personal con id: " + to_string(persona->get_id()));
    }
    cout << "Personal agregado:\n" << persona->get_nombre() << "[ID: " << persona->get_id() << "]\n";
    personal.push_back(move(persona));
}

PersonalMedico* Hospital::buscar_por_id(int id){
    auto it = find_if(personal.begin(), personal.end(),[id](const unique_ptr<PersonalMedico>&p){
        return p->get_id() ==id;
    });
    return (it!= personal.end()) ? it->get() : nullptr;
}

vector<PersonalMedico*> Hospital::obtener_personal_por_especialidad(const string& especialidad) const {
    vector<PersonalMedico*> resultado;
    for(const auto& persona : personal){
        if(persona->get_especialidad() == especialidad){
            resultado.push_back(persona.get());
        }
    }
    return resultado;
}

void Hospital::mostrar_plantilla() const {
    if(personal.empty()){
        cout << "No hay personal registrado en el hospital\n";
        return;
    }

    cout << "\n" << string(ANCHO_LINEA,'=') << "\n";
    cout << "PLANTILLA DE " << nombre << "\n";
    cout << string(ANCHO_LINEA, '=') << "\n";
    cout << left 
              << std::setw(8) << "ID" 
              << std::setw(20) << "NOMBRE" 
              << std::setw(20) << "ESPECIALIDAD" 
              << std::setw(10) << "SALARIO" 
              << std::setw(15) << "TIPO"
              << "DETALLES" << "\n";

    for(const auto& persona : personal){
        persona->mostrar_info();
    }

    cout << std::string(ANCHO_LINEA, '-') << "\n";
    cout << "Total de empleados: " << personal.size() << "\n";
}

void Hospital::calcular_nomina_total() const {
    
    if (personal.empty()) {
        std::cout << "No hay personal para calcular nómina." << std::endl;
        return;
    }

    std::cout << "\n" << std::string(ANCHO_LINEA, '=') << std::endl;
    std::cout << "REPORTE DE NÓMINA - " << nombre << std::endl;
    std::cout << std::string(ANCHO_LINEA, '=') << std::endl;

    double total_nomina = 0.0;
    int count_doctores = 0, count_enfermeros = 0, count_administrativos = 0;
    double suma_doctores = 0, suma_enfermeros=0, suma_administrativos = 0;

    for(const auto& persona : personal){
        double salario = persona->calcular_salario();
        total_nomina += salario;

        if(dynamic_cast<Doctor*>(persona.get())){
            ++count_doctores;
            suma_doctores += salario;
        } else if(dynamic_cast<Enfermero*>(persona.get())){
            ++count_enfermeros;
            suma_enfermeros += salario;
        } else if(dynamic_cast<
        Administrativo*>(persona.get())){
            ++count_administrativos;
            suma_administrativos += salario;
        }
    }

    cout << fixed << setprecision(2);
    
    if (count_doctores > 0) {
        cout << "👨‍⚕️ Doctores (" << count_doctores << "): $" 
                  << suma_doctores << " (Promedio: $" 
                  << suma_doctores / count_doctores << ")" << endl;
    }
    
    if (count_enfermeros > 0) {
        cout << "👩‍⚕️ Enfermeros (" << count_enfermeros << "): $" 
                  << suma_enfermeros << " (Promedio: $" 
                  << suma_enfermeros / count_enfermeros << ")" << endl;
    }
    
    if (count_administrativos > 0) {
        cout << "📋 Administrativos (" << count_administrativos << "): $" 
                  << suma_administrativos << " (Promedio: $" 
                  << suma_administrativos / count_administrativos << ")" << endl;
    }
    
    cout << string(50, '-') << endl;
    cout << "💰 NÓMINA TOTAL MENSUAL: $" << total_nomina << endl;
    cout << "💼 Total de empleados: " << personal.size() << endl;
    cout << "📊 Salario promedio general: $" << (total_nomina / personal.size()) << endl;
}

void Hospital::mostrar_por_tipo() const {
    cout << "\n" << string(ANCHO_LINEA, '=') << endl;
    cout << "PERSONAL AGRUPADO POR TIPO - " << nombre << endl;
    cout << string(ANCHO_LINEA, '=') << endl;
    
    // Doctores
    cout << "\n🩺 DOCTORES:" << endl;
    cout << string(60, '-') << endl;
    bool hay_doctores = false;
    for (const auto& p : personal) {
        if (auto doctor = dynamic_cast<Doctor*>(p.get())) {
            doctor->mostrar_info();
            cout << "   Tarea: ";
            doctor->realizar_tarea();
            cout << endl;
            hay_doctores = true;
        }
    }
    if (!hay_doctores) {
        cout << "No hay doctores registrados." << endl;
    }
    
    // Enfermeros
    cout << "\n👩‍⚕️ ENFERMEROS:" << endl;
    cout << string(60, '-') << endl;
    bool hay_enfermeros = false;
    for (const auto& p : personal) {
        if (auto enfermero = dynamic_cast<Enfermero*>(p.get())) {
            enfermero->mostrar_info();
            cout << "   Tarea: ";
            enfermero->realizar_tarea();
            cout << endl;
            hay_enfermeros = true;
        }
    }
    if (!hay_enfermeros) {
        cout << "No hay enfermeros registrados." << endl;
    }
    
    // Administrativos
    cout << "\n📋 PERSONAL ADMINISTRATIVO:" << endl;
    cout << string(60, '-') << endl;
    bool hay_administrativos = false;
    for (const auto& p : personal) {
        if (auto admin = dynamic_cast<Administrativo*>(p.get())) {
            admin->mostrar_info();
            cout << "   Tarea: ";
            admin->realizar_tarea();
            cout << endl;
            hay_administrativos = true;
        }
    }
    if (!hay_administrativos) {
        cout << "No hay personal administrativo registrado." << endl;
    }
}

void Hospital::mostrar_estadisticas() const {
    std::cout << "\n" << std::string(ANCHO_LINEA, '=') << std::endl;
    std::cout << "ESTADÍSTICAS GENERALES - " << nombre << std::endl;
    std::cout << std::string(ANCHO_LINEA, '=') << std::endl;
    
    if (personal.empty()) {
        std::cout << "No hay datos para mostrar estadísticas." << std::endl;
        return;
    }
    
    // Contar por tipo
    int doctores = 0, enfermeros = 0, administrativos = 0;
    for (const auto& p : personal) {
        if (dynamic_cast<Doctor*>(p.get())) doctores++;
        else if (dynamic_cast<Enfermero*>(p.get())) enfermeros++;
        else if (dynamic_cast<Administrativo*>(p.get())) administrativos++;
    }
    
    // Encontrar salarios máximo y mínimo
    auto minmax_salarios = std::minmax_element(personal.begin(), personal.end(),
        [](const std::unique_ptr<PersonalMedico>& a, const std::unique_ptr<PersonalMedico>& b) {
            return a->calcular_salario() < b->calcular_salario();
        });
    
    double salario_min = (*minmax_salarios.first)->calcular_salario();
    double salario_max = (*minmax_salarios.second)->calcular_salario();
    std::string nombre_min = (*minmax_salarios.first)->get_nombre();
    std::string nombre_max = (*minmax_salarios.second)->get_nombre();
    
    // Mostrar estadísticas
    std::cout << "📊 DISTRIBUCIÓN DEL PERSONAL:" << std::endl;
    std::cout << "   Doctores: " << doctores << " (" 
              << std::fixed << std::setprecision(1) 
              << (doctores * 100.0 / personal.size()) << "%)" << std::endl;
    std::cout << "   Enfermeros: " << enfermeros << " (" 
              << (enfermeros * 100.0 / personal.size()) << "%)" << std::endl;
    std::cout << "   Administrativos: " << administrativos << " (" 
              << (administrativos * 100.0 / personal.size()) << "%)" << std::endl;
    
    std::cout << "\n💰 INFORMACIÓN SALARIAL:" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "   Salario más alto: $" << salario_max << " (" << nombre_max << ")" << std::endl;
    std::cout << "   Salario más bajo: $" << salario_min << " (" << nombre_min << ")" << std::endl;
    
    std::cout << "\n📈 CONTADORES GLOBALES:" << std::endl;
    std::cout << "   Total personal médico: " << PersonalMedico::get_total_personal() << std::endl;
    std::cout << "   Total doctores (estático): " << Doctor::get_total_doctores() << std::endl;
    
    // Especialidades únicas
    std::vector<std::string> especialidades;
    for (const auto& p : personal) {
        std::string esp = p->get_especialidad();
        if (std::find(especialidades.begin(), especialidades.end(), esp) == especialidades.end()) {
            especialidades.push_back(esp);
        }
    }
    
    std::cout << "\n🏥 ESPECIALIDADES DISPONIBLES (" << especialidades.size() << "):" << std::endl;
    for (const auto& esp : especialidades) {
        auto personal_esp = obtener_personal_por_especialidad(esp);
        std::cout << "   " << esp << ": " << personal_esp.size() << " profesional(es)" << std::endl;
    }
}

// Getters
std::string Hospital::get_nombre() const {
    return nombre;
}

size_t Hospital::get_total_empleados() const {
    return personal.size();
}

std::vector<PersonalMedico*> Hospital::buscar_por_salario_minimo(double salario_min) const {
    std::vector<PersonalMedico*> resultado;
    
    for (const auto& persona : personal) {
        if (persona->calcular_salario() >= salario_min) {
            resultado.push_back(persona.get());
        }
    }
    
    // Ordenar por salario descendente
    std::sort(resultado.begin(), resultado.end(),
        [](PersonalMedico* a, PersonalMedico* b) {
            return a->calcular_salario() > b->calcular_salario();
        });
    
    return resultado;
}