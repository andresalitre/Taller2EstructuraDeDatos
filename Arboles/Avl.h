#pragma once

#include <string>
#include "NodoAVL.h"

using namespace std;

class AVL {
private:
    NodoAVL* raiz;
    int cantidad;

    int altura(NodoAVL* nodo);
    int factorBalance(NodoAVL* nodo);
    void actualizarAltura(NodoAVL* nodo);

    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* rotarIzquierdaDerecha(NodoAVL* nodo);
    NodoAVL* rotarDerechaIzquierda(NodoAVL* nodo);
    NodoAVL* rebalancear(NodoAVL* nodo);

    NodoAVL* insertar(NodoAVL* nodo, Patient* p, bool& insertado);
    NodoAVL* eliminar(NodoAVL* nodo, const string& id, bool& eliminado);
    NodoAVL* nodoMinimo(NodoAVL* nodo);
    Patient* buscarPorNombre(NodoAVL* nodo, const string& nombre);
    void inorden(NodoAVL* nodo, string& salida);
    void preorden(NodoAVL* nodo, string& salida);
    void postorden(NodoAVL* nodo, string& salida);
    void factoresBalance(NodoAVL* nodo, string& salida);
    void destruir(NodoAVL* nodo);

public:
    AVL();
    ~AVL();
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    bool insertar(Patient* p);
    Patient* buscar(const string& id, string& ruta);
    Patient* buscarPorNombre(const string& nombre);
    bool eliminar(const string& id);

    string inorden();
    string preorden();
    string postorden();
    string factoresBalance();

    int altura();
    int tamano();
    bool estaVacio();
};