#pragma once

#include <string>
#include "Patient.h"
#include "../containers/List.h"

using namespace std;

class Service // Servicio del hospital
{
    private:
        string name;
        List<Patient*> patients;

    public:
        Service(string name);

        string getName();
        void addPatient(Patient* p);
        List<Patient*>& getPatients(); // Lista poor referencia
        int patientsCount();

        ~Service();
};