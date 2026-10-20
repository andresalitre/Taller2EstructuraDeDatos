#pragma once

#include "../Dominio/Patient.h"

class NodoAVL {
private:
    Patient* paciente;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

public:
    NodoAVL(Patient* paciente) {
        this->paciente = paciente;
        this->izquierdo = nullptr;
        this->derecho = nullptr;
        this->altura = 1;
    }

    Patient* getPaciente() { return paciente; }
    void setPaciente(Patient* paciente) { this->paciente = paciente; }

    NodoAVL* getIzquierdo() { return izquierdo; }
    void setIzquierdo(NodoAVL* izquierdo) { this->izquierdo = izquierdo; }

    NodoAVL* getDerecho() { return derecho; }
    void setDerecho(NodoAVL* derecho) { this->derecho = derecho; }

    int getAltura() { return altura; }
    void setAltura(int altura) { this->altura = altura; }
};