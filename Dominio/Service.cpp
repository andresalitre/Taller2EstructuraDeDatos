#include "Service.h"

Service::Service(string name) { // Constructor
    this->name = name;
}

// Getters
string Service::getName() {
    return name;
}

void Service::addPatient(Patient* p) {
    patients.insertLast(p);
}

List<Patient*>& Service::getPatients() {
    return patients;
}

int Service::patientsCount() {
    return patients.size();
}

// Destructor
Service::~Service()
{
    for (int i = 0; i < patients.size(); i++)
    {
        delete patients.get(i);
    }
    patients.clear();
}