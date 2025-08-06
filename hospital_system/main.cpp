#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

// Incluir todos los headers del sistema
#include "include/Hospital.h"
#include "include/Doctor.h"
#include "include/Enfermero.h"
#include "include/Administrativo.h"

using namespace std;

int main() {
    try {
        // ==========================================
        // CREAR HOSPITAL
        // ==========================================
        cout << "=== SISTEMA DE GESTIÓN HOSPITALARIA ===" << endl;
        cout << string(60, '=') << endl;
        
        Hospital hospital("Hospital General Medellín");
        
        cout << "\n" << string(60, '-') << endl;
        cout << "AGREGANDO PERSONAL AL HOSPITAL..." << endl;
        cout << string(60, '-') << endl;
        
        // ==========================================
        // AGREGAR DOCTORES
        // ==========================================
        cout << "\n🩺 AGREGANDO DOCTORES:" << endl;
        
        hospital.agregar_personal(
            make_unique<Doctor>("Dr. Ana García", 1001, "Cardiología", 8000, 10, 25, true)
        );
        
        hospital.agregar_personal(
            make_unique<Doctor>("Dr. Luis Pérez", 1002, "Pediatría", 7500, 5, 30, false)
        );
        
        hospital.agregar_personal(
            make_unique<Doctor>("Dr. María Torres", 1003, "Neurología", 9000, 15, 20, true)
        );
        
        hospital.agregar_personal(
            make_unique<Doctor>("Dr. Carlos Ruiz", 1004, "Cardiología", 7800, 8, 28, false)
        );
        
        // ==========================================
        // AGREGAR ENFERMEROS
        // ==========================================
        cout << "\n👩‍⚕️ AGREGANDO ENFERMEROS:" << endl;
        
        hospital.agregar_personal(
            make_unique<Enfermero>("Carmen López", 2001, "Cuidados Intensivos", 
                                 4000, 8, Enfermero::Turno::NOCHE, true)
        );
        
        hospital.agregar_personal(
            make_unique<Enfermero>("José Martín", 2002, "Emergencias", 
                                 3800, 3, Enfermero::Turno::MAÑANA, false)
        );
        
        hospital.agregar_personal(
            make_unique<Enfermero>("Ana Ruiz", 2003, "Pediatría", 
                                 4200, 12, Enfermero::Turno::TARDE, true)
        );
        
        hospital.agregar_personal(
            make_unique<Enfermero>("Pedro Silva", 2004, "Cardiología", 
                                 3900, 6, Enfermero::Turno::NOCHE, false)
        );
        
        // ==========================================
        // AGREGAR PERSONAL ADMINISTRATIVO
        // ==========================================
        cout << "\n📋 AGREGANDO PERSONAL ADMINISTRATIVO:" << endl;
        
        hospital.agregar_personal(
            make_unique<Administrativo>("María Fernández", 3001, "Recursos Humanos", 
                                      3500, 12, "RRHH", true)
        );
        
        hospital.agregar_personal(
            make_unique<Administrativo>("Roberto González", 3002, "Contabilidad", 
                                      3200, 4, "Finanzas", false)
        );
        
        hospital.agregar_personal(
            make_unique<Administrativo>("Laura Morales", 3003, "Administración", 
                                      3800, 8, "Dirección", true)
        );
        
        // ==========================================
        // MOSTRAR PLANTILLA COMPLETA
        // ==========================================
        hospital.mostrar_plantilla();
        
        // ==========================================
        // CALCULAR NÓMINA TOTAL
        // ==========================================
        hospital.calcular_nomina_total();
        
        // ==========================================
        // MOSTRAR PERSONAL POR TIPO
        // ==========================================
        hospital.mostrar_por_tipo();
        
        // ==========================================
        // MOSTRAR ESTADÍSTICAS
        // ==========================================
        hospital.mostrar_estadisticas();
        
        // ==========================================
        // BUSCAR PERSONAL POR ID
        // ==========================================
        cout << "\n" << string(60, '=') << endl;
        cout << "PRUEBAS DE BÚSQUEDA" << endl;
        cout << string(60, '=') << endl;
        
        cout << "\n🔍 BÚSQUEDA POR ID:" << endl;
        
        int ids_buscar[] = {1001, 2003, 3002, 9999};
        for (int id : ids_buscar) {
            PersonalMedico* encontrado = hospital.buscar_por_id(id);
            if (encontrado) {
                cout << "✅ ID " << id << " encontrado: " 
                     << encontrado->get_nombre() 
                     << " (" << encontrado->get_especialidad() << ")" << endl;
            } else {
                cout << "❌ ID " << id << " no encontrado" << endl;
            }
        }
        
        // ==========================================
        // BUSCAR POR ESPECIALIDAD
        // ==========================================
        cout << "\n🔍 BÚSQUEDA POR ESPECIALIDAD:" << endl;
        
        vector<string> especialidades_buscar = {
            "Cardiología", "Pediatría", "Oncología", "Recursos Humanos"
        };
        
        for (const auto& especialidad : especialidades_buscar) {
            auto personal_esp = hospital.obtener_personal_por_especialidad(especialidad);
            cout << "\n📋 " << especialidad << " (" << personal_esp.size() << " personas):" << endl;
            
            if (!personal_esp.empty()) {
                for (auto* persona : personal_esp) {
                    cout << "   - " << persona->get_nombre() 
                         << " (ID: " << persona->get_id() 
                         << ", Salario: $" << persona->calcular_salario() << ")" << endl;
                }
            } else {
                cout << "   No hay personal en esta especialidad." << endl;
            }
        }
        
        // ==========================================
        // DEMOSTRAR POLIMORFISMO
        // ==========================================
        cout << "\n" << string(60, '=') << endl;
        cout << "DEMOSTRACIÓN DE POLIMORFISMO" << endl;
        cout << string(60, '=') << endl;
        
        cout << "\n🔄 TAREAS DEL PERSONAL (Polimorfismo en acción):" << endl;
        
        // Obtener algunos empleados para demostrar polimorfismo
        auto cardiologos = hospital.obtener_personal_por_especialidad("Cardiología");
        auto enfermeros_icu = hospital.obtener_personal_por_especialidad("Cuidados Intensivos");
        auto admin_rrhh = hospital.obtener_personal_por_especialidad("Recursos Humanos");
        
        if (!cardiologos.empty()) {
            cout << "\n👨‍⚕️ " << cardiologos[0]->get_nombre() << " (Cardiólogo): ";
            cardiologos[0]->realizar_tarea();
            cout << endl;
        }
        
        if (!enfermeros_icu.empty()) {
            cout << "👩‍⚕️ " << enfermeros_icu[0]->get_nombre() << " (Enfermero ICU): ";
            enfermeros_icu[0]->realizar_tarea();
            cout << endl;
        }
        
        if (!admin_rrhh.empty()) {
            cout << "📋 " << admin_rrhh[0]->get_nombre() << " (RRHH): ";
            admin_rrhh[0]->realizar_tarea();
            cout << endl;
        }
        
        // ==========================================
        // PRUEBA DE OPERADORES SOBRECARGADOS
        // ==========================================
        cout << "\n" << string(60, '=') << endl;
        cout << "PRUEBA DE OPERADORES SOBRECARGADOS" << endl;
        cout << string(60, '=') << endl;
        
        // Buscar dos empleados para comparar
        PersonalMedico* emp1 = hospital.buscar_por_id(1001);
        PersonalMedico* emp2 = hospital.buscar_por_id(2001);
        
        if (emp1 && emp2) {
            cout << "\n⚖️ COMPARACIÓN DE EMPLEADOS:" << endl;
            cout << "Empleado 1: " << *emp1 << endl;
            cout << "Empleado 2: " << *emp2 << endl;
            
            if (*emp1 == *emp2) {
                cout << "✅ Los empleados son iguales (mismo ID)" << endl;
            } else {
                cout << "❌ Los empleados son diferentes" << endl;
            }
            
            if (*emp1 < *emp2) {
                cout << "💰 " << emp1->get_nombre() << " gana menos que " << emp2->get_nombre() << endl;
            } else {
                cout << "💰 " << emp1->get_nombre() << " gana más que " << emp2->get_nombre() << endl;
            }
        }
        
        // ==========================================
        // INTENTAR AGREGAR PERSONAL CON ID DUPLICADO
        // ==========================================
        cout << "\n" << string(60, '=') << endl;
        cout << "PRUEBA DE VALIDACIÓN - ID DUPLICADO" << endl;
        cout << string(60, '=') << endl;
        
        try {
            cout << "\n⚠️  Intentando agregar personal con ID duplicado (1001)..." << endl;
            hospital.agregar_personal(
                make_unique<Doctor>("Dr. Juan Pérez", 1001, "Medicina General", 6000, 3, 15, false)
            );
        } catch (const runtime_error& e) {
            cout << "🚫 Error capturado correctamente: " << e.what() << endl;
        }
        
        // ==========================================
        // RESUMEN FINAL
        // ==========================================
        cout << "\n" << string(60, '=') << endl;
        cout << "RESUMEN FINAL DEL SISTEMA" << endl;
        cout << string(60, '=') << endl;
        
        cout << "\n📊 INFORMACIÓN GENERAL:" << endl;
        cout << "Hospital: " << hospital.get_nombre() << endl;
        cout << "Total de empleados: " << hospital.get_total_empleados() << endl;
        
        cout << "\n📈 CONTADORES ESTÁTICOS:" << endl;
        cout << "Total PersonalMedico creado: " << PersonalMedico::get_total_personal() << endl;
        cout << "Total Doctores creados: " << Doctor::get_total_doctores() << endl;
        
        cout << "\n✅ FUNCIONALIDADES PROBADAS:" << endl;
        cout << "   ✓ Creación de hospital y personal" << endl;
        cout << "   ✓ Herencia (Doctor, Enfermero, Administrativo)" << endl;
        cout << "   ✓ Polimorfismo (realizar_tarea, calcular_salario)" << endl;
        cout << "   ✓ Encapsulación (validaciones y getters)" << endl;
        cout << "   ✓ Sobrecarga de operadores (==, <, <<)" << endl;
        cout << "   ✓ Smart pointers (unique_ptr)" << endl;
        cout << "   ✓ Manejo de excepciones" << endl;
        cout << "   ✓ Búsqueda y filtrado" << endl;
        cout << "   ✓ Reportes y estadísticas" << endl;
        cout << "   ✓ Variables y métodos estáticos" << endl;
        
        cout << "\n🎉 SISTEMA HOSPITALARIO FUNCIONANDO CORRECTAMENTE!" << endl;
        
    } catch (const exception& e) {
        cerr << "\n❌ ERROR CRÍTICO: " << e.what() << endl;
        cerr << "El programa se cerrará." << endl;
        return 1;
    }
    
    cout << "\n" << string(60, '=') << endl;
    cout << "FIN DEL PROGRAMA" << endl;
    cout << string(60, '=') << endl;
    
    return 0;
}