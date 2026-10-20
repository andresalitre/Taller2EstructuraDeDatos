#pragma once

#include <string>
#include "NodoDecision.h"

using namespace std;

class ArbolDecision {
private:
    NodoDecision* raiz;

    void preorden(NodoDecision* nodo, string& salida);
    void inorden(NodoDecision* nodo, string& salida);
    void postorden(NodoDecision* nodo, string& salida);
    void destruir(NodoDecision* nodo);

public:
    ArbolDecision();
    ~ArbolDecision();
    ArbolDecision(const ArbolDecision&) = delete;
    ArbolDecision& operator=(const ArbolDecision&) = delete;

    static bool esValido(Patient* p);

    string evaluar(Patient* p, string& ruta);

    string preorden();
    string inorden();
    string postorden();
};