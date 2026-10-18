// Taller 2 estructura de datos | Integrante: Andrés Rojas Tejada | 22.065.446-k

#include <iostream>
#include <string>
#include "containers/Queue.h"
#include "containers/List.h"
#include "Dominio/Patient.h"
#include "Dominio/Service.h"

using namespace std;

Queue<Patient*> pacientes; // Cola de pacientes en espera
List<Service*> servicios;  // Lista de servicios del hospital

void crearServicios() // Crea los 8 servicios del hospital
{
    servicios.insertLast(new Service("Urgencias"));
    servicios.insertLast(new Service("Medicina General"));
    servicios.insertLast(new Service("Cardiologia"));
    servicios.insertLast(new Service("Neurologia"));
    servicios.insertLast(new Service("Traumatologia"));
    servicios.insertLast(new Service("Cirugia"));
    servicios.insertLast(new Service("Pediatria"));
    servicios.insertLast(new Service("Hospitalizacion"));
}

void leerArchivo(string nombre) // Lee el archivo de pacientes y los agrega a la cola
{

}

void atender() // Opcion 1
{

}

void departamentos() // Opcion 2
{

}

void buscarPaciente() // Opcion 3
{

}

void liberarMemoria() // Libera la cola y los servicios (cada servicio libera su AVL)
{
    while (!pacientes.empty())
    {
        delete pacientes.front();
        pacientes.pop();
    }
    for (int i = 0; i < servicios.size(); i++)
    {
        delete servicios.get(i);
    }
    servicios.clear();
}

void menu() // Menu principal
{
    string opcion = "0";
    do {
        cout << "=== HOSPITAL MARMAJA ===\n1. Atender pacientes\n2. Ver departamentos\n3. Buscar paciente\n4. Salir\n\nSeleccionar opcion: ";
        cin >> opcion;

        if (opcion == "1")
        {
            atender();
        }
        else if (opcion == "2")
        {
            departamentos();
        }
        else if (opcion == "3")
        {
            buscarPaciente();
        }
        else if (opcion == "4")
        {
            cout << "\nHasta luego :D.\n";
        }
        else
        {
            cout << "\nOpcion invalida.\n\n";
        }

    } while (opcion != "4");
}

int main()
{
    crearServicios();
    leerArchivo("pacientes.txt");
    menu();
    liberarMemoria();
    return 0;
}