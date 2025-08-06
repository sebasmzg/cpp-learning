#include "../include/Enfermero.h"

using namespace std;

Enfermero::Enfermero(const string& nombre, int id, const string& especialidad, double salario, int experiencia, Turno turno, bool especializacion) : PersonalMedico(nombre, id, especialidad, salario, experiencia), turno(turno), tiene_especializacion(especializacion) {}

string Enfermero::turno_to_string() const {
    switch(turno) {
        case Turno::MAÑANA: return "Mañana";
        case Turno::TARDE: return "Tarde";
        case Turno::NOCHE: return "Noche";
        default: return "Desconocido";
    }
};

double Enfermero::calcular_salario() const {
    double bono_turno = (turno == Turno::NOCHE) ? bono_noche : 0.0;
    double bono_esp = tiene_especializacion ?  bono_especializacion: 0.0;

    return salario_base + bono_esp + bono_turno;
}

void Enfermero::realizar_tarea() const {
    cout << "Cuidando paciente y administrando medicamentos";
}

void Enfermero::mostrar_info() const {
    PersonalMedico::mostrar_info();

    cout << " | Turno: " << setw(8) << turno_to_string() << " | Especialización " << setw(3) << (tiene_especializacion ? "Sí" : "No");
}

bool Enfermero::tiene_especializacion_medica() const {
    return tiene_especializacion;
}

Enfermero::Turno Enfermero::get_turno() const {
    return turno;
}