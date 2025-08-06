#ifndef ADMINISTRATIVO_H
#define ADMINISTRATIVO_H

#include "PersonalMedico.h"

using namespace std;

class Administrativo : public PersonalMedico {
    private:
        string departamento;
        bool maneja_presupuesto;

        // constantes
        static constexpr double bono_presupuesto = 1000.0;

    public:
        Administrativo(const string& nombre, int id, const string& especialidad, double salario, int experiencia, const string& departamento, bool presupuesto);

        virtual ~Administrativo() = default;

        double calcular_salario() const override;
        void realizar_tarea() const override;
        void mostrar_info() const override;
};

#endif