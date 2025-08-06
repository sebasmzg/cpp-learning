#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "PersonalMedico.h"
#include <vector>
#include <memory>

using namespace std;

class Hospital {
private:
    string nombre;
    vector<unique_ptr<PersonalMedico>> personal;
    
    static constexpr int ANCHO_LINEA = 100;

public:
    explicit Hospital(const string& nombre);
    
    // Gestión de personal
    void agregar_personal(unique_ptr<PersonalMedico> persona);
    PersonalMedico* buscar_por_id(int id);
    vector<PersonalMedico*> obtener_personal_por_especialidad(const std::string& especialidad) const;

    vector<PersonalMedico*> buscar_por_salario_minimo(double salario_min) const;

    // Reportes
    void mostrar_plantilla() const;
    void calcular_nomina_total() const;
    void mostrar_por_tipo() const;
    void mostrar_estadisticas() const;
    
    // Getters
    string get_nombre() const;
    size_t get_total_empleados() const;
};

#endif