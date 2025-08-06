#include "../include/Administrativo.h" 

using namespace std;

Administrativo::Administrativo(const string& nombre, int id, const string& especialidad, double salario, int experiencia, const string& departamento, bool presupuesto) : PersonalMedico(nombre, id, especialidad, salario, experiencia), departamento(departamento), maneja_presupuesto(presupuesto) {
    if(departamento.empty()){
        throw invalid_argument("Departamento no debe estar vacío");
    }
}

double Administrativo::calcular_salario() const {
    double bono = maneja_presupuesto ? bono_presupuesto : 0.0;
    return salario_base + bono;
}

void Administrativo::mostrar_info() const {
    PersonalMedico::mostrar_info();

    cout << " | Maneja presupuesto: " << (maneja_presupuesto ? "Sí" : "No");
}

void Administrativo::realizar_tarea() const {
    cout << "Gestionando documentos y procesos administrativos";
}