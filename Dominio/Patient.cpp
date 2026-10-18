#include "Patient.h"

Patient::Patient(string id, string name, int age, double temperature, int bloodPressure,
    int pain, string painType, int trauma, int neuroSymptoms,
    int requiresSurgery, int hospitalDays) : Person(name, age) {
    this->id = id;
    this->temperature = temperature;
    this->bloodPressure = bloodPressure;
    this->pain = pain;
    this->painType = painType;
    this->trauma = trauma;
    this->neuroSymptoms = neuroSymptoms;
    this->requiresSurgery = requiresSurgery;
    this->hospitalDays = hospitalDays;
    this->service = "";
}

// Getters
string Patient::getId() { return id; }
double Patient::getTemperature() { return temperature; }
int Patient::getBloodPressure() { return bloodPressure; }
int Patient::getPain() { return pain; }
string Patient::getPainType() { return painType; }
int Patient::getTrauma() { return trauma; }
int Patient::getNeuroSymptoms() { return neuroSymptoms; }
int Patient::getRequiresSurgery() { return requiresSurgery; }
int Patient::getHospitalDays() { return hospitalDays; }
string Patient::getService() { return service; }

// Setter
void Patient::setService(string service) {
    this->service = service;
}

// Destructor
Patient::~Patient() {}