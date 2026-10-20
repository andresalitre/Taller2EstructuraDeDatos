#include "Service.h"

Service::Service(string name) {
    this->name = name;
}

string Service::getName() {
    return name;
}

bool Service::addPatient(Patient* p) {
    return patients.insertar(p);
}

AVL& Service::getPatients() {
    return patients;
}

int Service::patientsCount() {
    return patients.tamano();
}

Service::~Service() {}