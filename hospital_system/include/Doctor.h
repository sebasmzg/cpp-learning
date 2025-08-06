#ifndef DOCTOR_H
#define DOCTOR_H

#include "PersonalMedico.h"

class Doctor : public PersonalMedico {
    private:
        int pacientes_atendidos;
        bool es_jefe_servicio;

        // constante
        static constexpr double bono_por_paciente = 50.0;
        static constexpr double bono_jefe_servicio = 2000.0;

        // contador estático
        static int total_doctores;

    public:
        Doctor(const string& nombre, int id, const string& especialidad, double salario, int experiencia, int pacientes, bool jefe);

        virtual ~Doctor();

        double calcular_salario() const override;
        void realizar_tarea() const override;

        static int get_total_doctores();

        int get_pacientes_atendidos() const;
        bool es_jefe() const;

};

#endif