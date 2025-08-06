#include "../include/Doctor.h"

using namespace std;

int Doctor::total_doctores = 0;

Doctor::Doctor( const string& nombre, int id, const string& especialidad, double salario, int experiencia, int pacientes, bool jefe) : PersonalMedico(nombre, id, especialidad, salario, experiencia), pacientes_atendidos(pacientes), es_jefe_servicio(jefe) {
    if(pacientes < 0)
        throw invalid_argument("Los pacientes atendidos, no pueden ser negativo");
    
    ++total_doctores;
}

Doctor::~Doctor(){
    --total_doctores;
}

double Doctor::calcular_salario() const {
    double bono_pacientes = pacientes_atendidos * bono_por_paciente;
    double bono_jefe = es_jefe_servicio ? bono_jefe_servicio : 0.0;
    return salario_base + bono_pacientes + bono_jefe;
}

void Doctor::realizar_tarea() const {
    cout << "Diagnosticando y tratando pacientes";
}

int Doctor::get_total_doctores(){
    return total_doctores;
}

int Doctor::get_pacientes_atendidos() const {
    return pacientes_atendidos;
}

bool Doctor::es_jefe() const {
    return es_jefe_servicio;
}