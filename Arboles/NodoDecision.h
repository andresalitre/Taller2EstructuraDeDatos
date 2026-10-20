#pragma once

#include <string>
#include "../Dominio/Patient.h"

using namespace std;

class NodoDecision {
private:
    string pregunta;
    string textoSi;
    string textoNo;
    bool (*condicion)(Patient*);
    string servicio;
    NodoDecision* si;
    NodoDecision* no;

public:
    NodoDecision(string pregunta, string textoSi, string textoNo, bool (*condicion)(Patient*)) {
        this->pregunta = pregunta;
        this->textoSi = textoSi;
        this->textoNo = textoNo;
        this->condicion = condicion;
        this->servicio = "";
        this->si = nullptr;
        this->no = nullptr;
    }

    NodoDecision(string servicio) {
        this->pregunta = "";
        this->textoSi = "";
        this->textoNo = "";
        this->condicion = nullptr;
        this->servicio = servicio;
        this->si = nullptr;
        this->no = nullptr;
    }

    bool esHoja() { return condicion == nullptr; }
    bool evaluar(Patient* p) { return condicion(p); }

    string getPregunta() { return pregunta; }
    string getTextoSi() { return textoSi; }
    string getTextoNo() { return textoNo; }
    string getServicio() { return servicio; }

    NodoDecision* getSi() { return si; }
    void setSi(NodoDecision* si) { this->si = si; }

    NodoDecision* getNo() { return no; }
    void setNo(NodoDecision* no) { this->no = no; }
};