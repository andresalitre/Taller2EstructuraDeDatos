// Taller 2 estructura de datos | Integrante: Andrés Rojas Tejada | 22.065.446-k

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "containers/Queue.h"
#include "containers/List.h"
#include "Dominio/Patient.h"
#include "Dominio/Service.h"
#include "Arboles/ArbolDecision.h"

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

bool pacienteDuplicado(string id) // Verifica si un paciente ya existe en la cola de espera
{
    Queue<Patient*> temp; // Cola temporal para no perder el orden
    bool encontrado = false;

    while (!pacientes.empty())
    {
        Patient* p = pacientes.front();
        pacientes.pop();

        if (p->getId() == id)
        {
            encontrado = true;
        }

        temp.push(p);
    }

    while (!temp.empty()) // Restaurar la cola original
    {
        pacientes.push(temp.front());
        temp.pop();
    }
    return encontrado;
}

// Crea un paciente a partir de una linea
// ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion
// Devuelve nullptr (con motivo) si la linea es invalida
Patient* crearPaciente(string linea, string& motivo)
{
    string campos[11];
    int cantidad = 0;
    string campo;
    stringstream ss(linea);

    while (getline(ss, campo, ';'))
    {
        if (cantidad < 11) campos[cantidad] = campo;
        cantidad++;
    }

    if (cantidad != 11)
    {
        motivo = "cantidad de campos incorrecta";
        return nullptr;
    }

    if (campos[0].empty() || campos[1].empty())
    {
        motivo = "ID o nombre vacio";
        return nullptr;
    }

    int edad, presion, dolor, trauma, neuro, cirugia, dias;
    double temperatura;

    try
    {
        edad = stoi(campos[2]);
        temperatura = stod(campos[3]);
        presion = stoi(campos[4]);
        dolor = stoi(campos[5]);
        trauma = stoi(campos[7]);
        neuro = stoi(campos[8]);
        cirugia = stoi(campos[9]);
        dias = stoi(campos[10]);
    }
    catch (...) // Texto que no es un numero
    {
        motivo = "valor no numerico";
        return nullptr;
    }

    Patient* p = new Patient(campos[0], campos[1], edad, temperatura, presion, dolor,
                             campos[6], trauma, neuro, cirugia, dias);

    if (!ArbolDecision::esValido(p)) // Rangos o tipo de dolor invalidos
    {
        delete p;
        motivo = "datos fuera de rango";
        return nullptr;
    }

    return p;
}

void leerArchivo(string nombre) // Lee el archivo de pacientes y los agrega a la cola
{
    ifstream archivo(nombre);

    if (!archivo.is_open()) // Archivo inexistente
    {
        cout << "Error: no se pudo abrir el archivo de pacientes.\n\n";
        return;
    }

    string linea;
    int numeroLinea = 0;
    while (getline(archivo, linea))
    {
        numeroLinea++;

        if (linea.empty()) continue; // Linea vacia
        if (numeroLinea == 1 && linea.rfind("ID;", 0) == 0) continue; // Encabezado

        string motivo;
        Patient* p = crearPaciente(linea, motivo);

        if (p == nullptr) // Linea invalida
        {
            cout << "Linea " << numeroLinea << " invalida (" << motivo << "): " << linea << endl;
            continue;
        }

        if (pacienteDuplicado(p->getId())) // ID ya presente en la cola
        {
            cout << "Linea " << numeroLinea << " invalida (paciente duplicado): " << linea << endl;
            delete p;
            continue;
        }

        pacientes.push(p);
    }
    cout << endl;
}

Service* buscarServicio(string nombre) // Busca un servicio de la lista por su nombre
{
    for (int i = 0; i < servicios.size(); i++)
    {
        if (servicios.get(i)->getName() == nombre)
        {
            return servicios.get(i);
        }
    }
    return nullptr;
}

void atender() // Opcion 1
{
    if (pacientes.empty())
    {
        cout << "\nNo hay pacientes en espera.\n\n";
        return;
    }

    ArbolDecision arbol;

    cout << "\n=== ATENDIENDO PACIENTES ===\n" << endl;

    while (!pacientes.empty()) // Se procesa respetando el orden de la cola
    {
        Patient* p = pacientes.front();
        pacientes.pop();

        string ruta;
        string nombreServicio = arbol.evaluar(p, ruta);
        Service* servicio = buscarServicio(nombreServicio);

        cout << "ID: " << p->getId() << "\nNombre: " << p->getName() << "\nEdad: " << p->getAge() << "\nTemperatura: "
             << fixed << setprecision(1) << p->getTemperature()
             << "\nDolor: " << p->getPain() << "\nTipoDolor: " << p->getPainType()
             << "\nTrauma: " << p->getTrauma() << "\nSintomasNeurologicos: " << p->getNeuroSymptoms()
             << "\nRequiereCirugia: " << p->getRequiresSurgery() << "\nDiasHospitalizacion: " << p->getHospitalDays() << "\n" << endl;

        cout << "Ruta: " << ruta << "\n" << endl;

        p->setService(nombreServicio);

        if (!servicio->addPatient(p)) // ID repetido en el AVL del servicio
        {
            cout << "No se pudo insertar: ya existe un paciente con el ID " << p->getId() << " en " << nombreServicio << ".\n" << endl;
            delete p;
            continue;
        }

        cout << "Servicio asignado: " << nombreServicio << endl;
        cout << "Paciente insertado en el AVL de " << nombreServicio << ".\n" << endl;
    }
}

void departamentos() // Opcion 2
{
    cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===\n" << endl;

    for (int i = 0; i < servicios.size(); i++)
    {
        Service* s = servicios.get(i);
        AVL& arbol = s->getPatients(); // AVL del servicio

        cout << s->getName() << endl;

        if (arbol.estaVacio())
        {
            cout << "Sin pacientes\n" << endl;
            continue;
        }

        cout << "Pacientes: " << arbol.inorden() << "\n" << endl;
    }
}

void buscarPaciente() // Opcion 3
{
    string entrada;

    cout << "\n=== BUSCAR PACIENTE ===\n" << endl;
    cout << "Indique el ID o Nombre del paciente: ";
    getline(cin, entrada);

    cout << "\nBuscando en AVL...\n" << endl;

    Patient* encontrado = nullptr;
    Service* servicioEncontrado = nullptr;
    string ruta;

    for (int i = 0; i < servicios.size() && encontrado == nullptr; i++) // Primero se busca por ID
    {
        Service* s = servicios.get(i);
        encontrado = s->getPatients().buscar(entrada, ruta);
        if (encontrado != nullptr)
        {
            servicioEncontrado = s;
        }
    }

    for (int i = 0; i < servicios.size() && encontrado == nullptr; i++) // Si no esta, se busca por nombre
    {
        Service* s = servicios.get(i);
        encontrado = s->getPatients().buscarPorNombre(entrada);
        if (encontrado != nullptr)
        {
            servicioEncontrado = s;
            s->getPatients().buscar(encontrado->getId(), ruta); // Ruta para llegar al paciente por su ID
        }
    }

    if (encontrado == nullptr)
    {
        cout << "Paciente no encontrado.\n" << endl;
        return;
    }

    cout << "Paciente encontrado:\n-------" << endl;
    cout << "ID: " << encontrado->getId() << "\nNombre: " << encontrado->getName() << "\nEdad: " << encontrado->getAge() << "\nDepartamento: " << servicioEncontrado->getName() << endl;

    cout << "T: " << fixed << setprecision(1) << encontrado->getTemperature() << "° | D: " << encontrado->getPain() << " | TD: " << encontrado->getPainType() 
    << " | T: " << (encontrado->getTrauma() == 1 ? "Si" : "No") << " | SN: " << (encontrado->getNeuroSymptoms() == 1 ? "Si" : "No") << " | RC: " << (encontrado->getRequiresSurgery() == 1 ? "Si" : "No") << " | DH: " 
    << (encontrado->getHospitalDays() == 0 ? "Ninguno" : to_string(encontrado->getHospitalDays())) << endl;
    
    cout << "-------\n" << endl;

    cout << "Ruta de busqueda:\n" << ruta << "\n" << endl;
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
        if (!getline(cin, opcion)) break;

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