#ifndef PERSONAL_MEDICO_H
#define PERSONAL_MEDICO_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class PersonalMedico {
    protected:
        string nombre;
        int id;
        string especialidad;
        double salario_base;
        int anios_experiencia;
    
    private:
        static int total_personal;

    public:
        // Constructor 
        explicit PersonalMedico(const string& nombre, int id, const string& especialidad, double salario, int experiencia);

        // Destructor
        virtual ~PersonalMedico();

        // Métodos virtuales
        virtual double calcular_salario() const;
        virtual void mostrar_info() const;
        virtual void realizar_tarea() const = 0;

        // Getters
        string get_nombre() const;
        int get_id() const;
        string get_especialidad() const;
        static int get_total_personal();

        // Operadores sobrecargados
        // comparar salario
        bool operator<(const PersonalMedico& otro) const;
        // comparar por id
        bool operator==(const PersonalMedico& otro) const;
        // mostrar info básica
        friend ostream& operator<<(ostream& os, const PersonalMedico& persona);
};

#endif 