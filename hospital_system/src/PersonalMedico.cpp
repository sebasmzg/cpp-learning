#include "../include/PersonalMedico.h"
#include <stdexcept>

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// variable estática para contar el total de personal médico
int PersonalMedico::total_personal = 0;

PersonalMedico::PersonalMedico(const string& nombre, int id, const string& especialidad, double salario, int experiencia) : nombre(nombre), id(id), especialidad(especialidad), salario_base(salario), anios_experiencia(experiencia) {
    // Validaciones básicas
    if(nombre.empty()) throw invalid_argument("El nombre no puede estar vacío");
    if(id <= 0) throw invalid_argument("El ID debe ser un número positivo");
    if(salario <= 0) throw invalid_argument("El salario debe ser un número positivo");
    if(experiencia < 0) throw invalid_argument("Los años de experiencia no pueden ser negativos");
    if(especialidad.empty()) throw invalid_argument("La especialidad no puede estar vacía");
    if(anios_experiencia < 0) throw invalid_argument("Los años de experiencia no pueden ser negativos");
    if(id < 1000 || id > 9999) throw invalid_argument("El ID debe estar entre 1000 y 9999");
    
    ++total_personal;
}

PersonalMedico::~PersonalMedico() {
    --total_personal;
}

double PersonalMedico::calcular_salario() const {
    return salario_base;
}

void PersonalMedico::mostrar_info() const {
    cout << "Id: " << setw(8) << id << " | Nombre: " << setw(20) << nombre 
            << " | Especialidad: " << setw(20) << especialidad 
            << " | Salario: $" << setw(8) << calcular_salario() << endl;
}

// Getters
std::string PersonalMedico::get_nombre() const { return nombre; }
int PersonalMedico::get_id() const { return id; }
std::string PersonalMedico::get_especialidad() const { return especialidad; }
int PersonalMedico::get_total_personal() { return total_personal; }

// Operadores
bool PersonalMedico::operator<(const PersonalMedico& otro) const {
    return this->calcular_salario() < otro.calcular_salario();
}

bool PersonalMedico::operator==(const PersonalMedico& otro) const {
    return this->id == otro.id;
}

std::ostream& operator<<(std::ostream& os, const PersonalMedico& persona) {
    os << "[" << persona.id << "] " << persona.nombre 
       << " - " << persona.especialidad 
       << " - $" << std::fixed << std::setprecision(2) << persona.calcular_salario();
    return os;
}