#include "Person.h"

// Constructor
Person::Person(string name, int age) {
    this->name = name;
    this->age = age;
}

// Getters
string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

// Destructor
Person::~Person() {}