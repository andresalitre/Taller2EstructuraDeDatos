#pragma once

#include <string>
#include "Person.h"

using namespace std;

class Patient : public Person { // Paciente del hospital
private:
    string id;
    double temperature;
    int bloodPressure;
    int pain; // Escala 0 a 10
    string painType; // pecho, cabeza, abdomen, extremidad u otro
    int trauma; // 0 = no, 1 = si
    int neuroSymptoms; // 0 = no, 1 = si
    int requiresSurgery; // 0 = no, 1 = si
    int hospitalDays; // Dias
    string service;// Se asigna despues con el arbol de decision

public:
    Patient(string id, string name, int age, double temperature, int bloodPressure,
    int pain, string painType, int trauma, int neuroSymptoms,
    int requiresSurgery, int hospitalDays);

    // Getters
    string getId();
    double getTemperature();
    int getBloodPressure();
    int getPain();
    string getPainType();
    int getTrauma();
    int getNeuroSymptoms();
    int getRequiresSurgery();
    int getHospitalDays();
    string getService();

    // Setter
    void setService(string service);

    ~Patient();
};