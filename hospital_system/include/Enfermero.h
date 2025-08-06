#ifndef ENFERMERO_H
#define ENFERMERO_H

#include "PersonalMedico.h"

using namespace std;

class Enfermero : public PersonalMedico {
    public:
        enum class Turno {
            MAÑANA,
            TARDE,
            NOCHE
        };

    private:
        Turno turno;
        bool tiene_especializacion;

        // constantes
        static constexpr double bono_noche = 500.0;
        static constexpr double bono_especializacion = 800.0;

        // helper
        string turno_to_string() const;


    public:
        Enfermero(const string& nombre, int id, const string& especialidad, double salario, int experiencia, Turno turno, bool especializacion);

        virtual ~Enfermero() = default;


        double calcular_salario() const override;
        void realizar_tarea() const override;
        void mostrar_info() const override;

        Turno get_turno() const;
        bool tiene_especializacion_medica() const;
};

#endif