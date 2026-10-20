#pragma once

#include <string>
#include "Patient.h"
#include "../Arboles/AVL.h"

using namespace std;

class Service // Servicio del hospital
{
    private:
        string name;
        AVL patients;

    public:
        Service(string name);

        string getName();
        bool addPatient(Patient* p);
        AVL& getPatients();
        int patientsCount();

        ~Service();
};