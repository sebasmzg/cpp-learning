#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

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
        explicit PersonalMedico(const string& nombre, int id, const string& especialidad, double salario, int experiencia) : nombre(nombre), id(id), especialidad(especialidad), salario_base(salario), anios_experiencia(experiencia) {
            if(nombre.empty()) throw invalid_argument("El nombre no puede estar vacío");
            if(id <= 0) throw invalid_argument("El ID debe ser un número positivo");
            if(salario <= 0) throw invalid_argument("El salario debe ser un número positivo");
            if(experiencia < 0) throw invalid_argument("Los años de experiencia no pueden ser negativos");
            if(especialidad.empty()) throw invalid_argument("La especialidad no puede estar vacía");
            if(anios_experiencia < 0) throw invalid_argument("Los años de experiencia no pueden ser negativos");
            if(id < 1000 || id > 9999) throw invalid_argument("El ID debe estar entre 1000 y 9999");
            
            ++total_personal;
        }

        virtual double calcular_salario() const {
            return salario_base;
        }

        virtual void mostrar_info() const {
            cout << "Id: " << setw(8) << id << " | Nombre: " << setw(20) << nombre 
                 << " | Especialidad: " << setw(20) << especialidad 
                 << " | Salario: $" << setw(8) << calcular_salario() << endl;
        }

        virtual void realizar_tarea() const {
            cout << nombre << " está realizando una tarea.";
        }

        string get_nombre() const { return nombre; }
        int get_id() const { return id; }
        string get_especialidad() const { return especialidad; }
        static int get_total_personal() { return total_personal; }

        // comparar salario
        bool operator<(const PersonalMedico& otro) const {
            return this->calcular_salario() < otro.calcular_salario();
        }
        // comparar por id
        bool operator==(const PersonalMedico& otro) const {
            return this->id == otro.id;
        }
        // mostrar info básica
        friend ostream& operator<<(ostream& os, const PersonalMedico& persona) {
            os << "[" << persona.id << "] " << persona.nombre << " - " << persona.especialidad << " - $" << fixed << setprecision(2) << persona.calcular_salario();
            return os;
        }
        
        virtual ~PersonalMedico() {
            --total_personal;
        };
};

int PersonalMedico::total_personal = 0;

class Doctor : public PersonalMedico {
    private:
        int pacientes_atendidos;
        bool es_jefe_servicio;
        int bono_por_pacientes = 50;
        int bono_jefe_servicio = 2000;
        static int total_doctores;

    public:
        Doctor(string nombre, int id, string especialidad, double salario, int experiencia, int pacientes, bool jefe) : PersonalMedico(nombre, id, especialidad, salario, experiencia), pacientes_atendidos(pacientes), es_jefe_servicio(jefe) {
            ++total_doctores;
        }

        virtual ~Doctor(){
            --total_doctores;
        }

        double calcular_salario() const override {
            return salario_base + (pacientes_atendidos * bono_por_pacientes) + (es_jefe_servicio ? bono_jefe_servicio : 0);
        }

        void realizar_tarea() const override {
            cout << "diagnosticando y tratando";
        }

        static int get_total_doctores(){ return total_doctores; }

};

class Enfermero : public PersonalMedico {
    public:
        enum class Turno {
            AM,
            PM,
            NOCHE
        };

    private:
        Turno m_turno;
        bool tiene_especializacion;

    public:
        Enfermero(string nombre, int id, string especialidad, double salario, int experiencia, Turno turno, bool especializacion) : PersonalMedico(nombre, id, especialidad, salario, experiencia), m_turno(turno), tiene_especializacion(especializacion) {}

        virtual ~Enfermero() = default;

        double calcular_salario() const override {
            return salario_base + (m_turno == Turno::NOCHE ? 500 : 0) + (tiene_especializacion ? 800 : 0);
        }

        void realizar_tarea() const override {
            cout << "Cuidando pacientes y administrando medicamentos";
        }
};

class Administrativo : public PersonalMedico {
    private:
        string departamento;
        bool maneja_presupuesto;

    public:
        Administrativo(string nombre, int id, string especialidad, double salario, int experiencia, string departamento, bool presupuesto) : PersonalMedico(nombre, id, especialidad, salario, experiencia), departamento(departamento), maneja_presupuesto(presupuesto) {}

        virtual ~Administrativo() = default;

        double calcular_salario() const override {
            return salario_base + (maneja_presupuesto ? 1000 : 0);
        }

        void realizar_tarea() const override {
            cout << "Gestionando documentos y procesos administrativos";
        }
};

class Hospital {
    private:
        string nombre;
        vector<unique_ptr<PersonalMedico>> personal;

    public:
        Hospital(string n) : nombre(n) {}

        void agregar_personal(unique_ptr<PersonalMedico> persona){
            personal.push_back(move(persona));
        }

        void mostrar_plantilla() const {
            cout << "\nPlantilla de personal médico de " << nombre << "\n";
            cout << string(100,'=') << "\n";

            for(const auto& persona : personal){
                persona->mostrar_info();
            }
            cout << "\n\n";
        }

        void calcular_nomina_total() const {
            cout << "\nNómina de personal médico de " << nombre << "\n";
            cout << string(100,'=') << "\n";

            double total_nomina = 0;
            for(const auto& persona : personal){
                persona->mostrar_info();
                total_nomina += persona->calcular_salario();
                cout << "\n";
            }

            cout << string(100,'=') << "\n";
            cout << "TOTAL NÓMINA: $" << fixed << setprecision(2) << total_nomina << "\n\n";
        };

        vector<PersonalMedico*> get_personal() const {
            vector<PersonalMedico*> resultado;
            for(const auto& persona : personal){
                resultado.push_back(persona.get());
            }
            return resultado;
        }

        PersonalMedico* buscar_por_id(int id){
            for(const auto& persona : personal){
                if(persona->get_id() == id){
                    return persona.get();
                }
            }
            return nullptr;
        }

        vector<PersonalMedico*> obtener_personal_por_especialidad(const string& esp){
            vector<PersonalMedico*> resultado;
            for(const auto& persona : personal){
                if(persona->get_especialidad() == esp){
                    resultado.push_back(persona.get());
                }
            }
            return resultado;
        }
        
        void mostrar_por_tipo() const {
        cout << "\n=== PERSONAL POR TIPO ===\n";
        
        cout << "\n🩺 DOCTORES:\n";
        for (const auto& p : personal) {
            if (auto doctor = dynamic_cast<Doctor*>(p.get())) {
                cout << *doctor << "\n";
            }
        }
        
        cout << "\n👩‍⚕️ ENFERMEROS:\n";
        for (const auto& p : personal) {
            if (auto enfermero = dynamic_cast<Enfermero*>(p.get())) {
                cout << *enfermero << "\n";
            }
        }
        
        cout << "\n📋 ADMINISTRATIVOS:\n";
        for (const auto& p : personal) {
            if (auto admin = dynamic_cast<Administrativo*>(p.get())) {
                cout << *admin << "\n";
            }
        }
}

};

int main(){
    Hospital hospital("Hospital General de Medellín");

    //Doctores
    hospital.agregar_personal(
        make_unique<Doctor>("Dr. Ana García", 1001, "Cardiología", 8000, 10, 25, true)
    );
    hospital.agregar_personal(
        make_unique<Doctor>("Dr. Luis Pérez", 1002, "Pediatría", 7500, 5, 30, false)
    );

    // Enfermeros
    hospital.agregar_personal(
        make_unique<Enfermero>("Carmen López", 2001, "Cuidados Intensivos", 4000, 8, Enfermero::Turno::NOCHE, true)
    );
    hospital.agregar_personal(
        make_unique<Enfermero>("José Martín", 2002, "Emergencias", 3800, 3, Enfermero::Turno::AM, false)
    );
    

    //administrativos
    hospital.agregar_personal(
        make_unique<Administrativo>("María Torres", 3001, "Recursos Humanos", 3500, 12, "RRHH", true)
    );
    hospital.agregar_personal(
        make_unique<Administrativo>("Laura Giraldo", 3002, "Recursos Humanos", 4500, 12, "RRHH", false)
    );

    // personal
    hospital.mostrar_plantilla();
    // nomina
    hospital.calcular_nomina_total();
    // por especialidad
    const auto cardiologos = hospital.obtener_personal_por_especialidad("Cardiología");
    for (auto p : cardiologos) {
        p->mostrar_info();
    }

    // buscar por id
    int id_buscar = 2002;
    PersonalMedico* persona = hospital.buscar_por_id(2001);
    if (persona) {
        cout << "\nPersona encontrada:\n";
        persona->mostrar_info();
        cout << "Tarea: ";
        persona->realizar_tarea();
        cout << "\n";
    } else {
        cout << "No se encontró personal con ID " << id_buscar << "\n";
    }

    //polimorfismo
    hospital.mostrar_por_tipo();

    // operadores
    Doctor d1("Dr. Ana García", 1001, "Cardiología", 8000, 10, 25, true);
    Doctor d2("Dr. Luis Pérez", 1002, "Pediatría", 7500, 5, 30, false);

    // Comparar por ID
    if (d1 == d2) {
        cout << "Mismo ID\n";
    } else {
        cout << "IDs diferentes\n";
    }

    // Comparar por salario
    if (d1 < d2) {
        cout << d1.get_nombre() << " gana menos que " << d2.get_nombre() << "\n";
    } else {
        cout << d1.get_nombre() << " gana igual o más que " << d2.get_nombre() << "\n";
    }

    // total personal
    cout << "\n=== ESTADÍSTICAS ===\n";
    cout << "Total personal: " << PersonalMedico::get_total_personal() << "\n";
    cout << "Total doctores: " << Doctor::get_total_doctores() << "\n";
    
    return 0;
};