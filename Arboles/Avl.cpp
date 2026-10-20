#include "AVL.h"

AVL::AVL() {
    raiz = nullptr;
    cantidad = 0;
}

AVL::~AVL() {
    destruir(raiz);
}

void AVL::destruir(NodoAVL* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->getIzquierdo());
    destruir(nodo->getDerecho());
    delete nodo->getPaciente();
    delete nodo;
}

int AVL::altura(NodoAVL* nodo) {
    return nodo == nullptr ? 0 : nodo->getAltura();
}

int AVL::factorBalance(NodoAVL* nodo) {
    return nodo == nullptr ? 0 : altura(nodo->getIzquierdo()) - altura(nodo->getDerecho());
}

void AVL::actualizarAltura(NodoAVL* nodo) {
    int ai = altura(nodo->getIzquierdo());
    int ad = altura(nodo->getDerecho());
    nodo->setAltura(1 + (ai > ad ? ai : ad));
}

NodoAVL* AVL::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->getIzquierdo();
    y->setIzquierdo(x->getDerecho());
    x->setDerecho(y);
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

NodoAVL* AVL::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->getDerecho();
    x->setDerecho(y->getIzquierdo());
    y->setIzquierdo(x);
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

NodoAVL* AVL::rotarIzquierdaDerecha(NodoAVL* nodo) {
    nodo->setIzquierdo(rotarIzquierda(nodo->getIzquierdo()));
    return rotarDerecha(nodo);
}

NodoAVL* AVL::rotarDerechaIzquierda(NodoAVL* nodo) {
    nodo->setDerecho(rotarDerecha(nodo->getDerecho()));
    return rotarIzquierda(nodo);
}

NodoAVL* AVL::rebalancear(NodoAVL* nodo) {
    actualizarAltura(nodo);
    int fb = factorBalance(nodo);
    if (fb > 1) {
        if (factorBalance(nodo->getIzquierdo()) >= 0) return rotarDerecha(nodo);
        return rotarIzquierdaDerecha(nodo);
    }
    if (fb < -1) {
        if (factorBalance(nodo->getDerecho()) <= 0) return rotarIzquierda(nodo);
        return rotarDerechaIzquierda(nodo);
    }
    return nodo;
}

NodoAVL* AVL::insertar(NodoAVL* nodo, Patient* p, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(p);
    }
    string id = p->getId();
    string idNodo = nodo->getPaciente()->getId();
    if (id < idNodo) {
        nodo->setIzquierdo(insertar(nodo->getIzquierdo(), p, insertado));
    } else if (id > idNodo) {
        nodo->setDerecho(insertar(nodo->getDerecho(), p, insertado));
    } else {
        insertado = false;
        return nodo;
    }
    return rebalancear(nodo);
}

bool AVL::insertar(Patient* p) {
    if (p == nullptr) return false;
    bool insertado = false;
    raiz = insertar(raiz, p, insertado);
    if (insertado) cantidad++;
    return insertado;
}

Patient* AVL::buscar(const string& id, string& ruta) {
    ruta = "";
    NodoAVL* actual = raiz;
    while (actual != nullptr) {
        string idActual = actual->getPaciente()->getId();
        if (!ruta.empty()) ruta += " -> ";
        ruta += idActual;
        if (id == idActual) return actual->getPaciente();
        actual = (id < idActual) ? actual->getIzquierdo() : actual->getDerecho();
    }
    return nullptr;
}

Patient* AVL::buscarPorNombre(NodoAVL* nodo, const string& nombre) {
    if (nodo == nullptr) return nullptr;
    if (nodo->getPaciente()->getName() == nombre) return nodo->getPaciente();
    Patient* encontrado = buscarPorNombre(nodo->getIzquierdo(), nombre);
    if (encontrado != nullptr) return encontrado;
    return buscarPorNombre(nodo->getDerecho(), nombre);
}

Patient* AVL::buscarPorNombre(const string& nombre) {
    return buscarPorNombre(raiz, nombre);
}

NodoAVL* AVL::nodoMinimo(NodoAVL* nodo) {
    while (nodo->getIzquierdo() != nullptr) nodo = nodo->getIzquierdo();
    return nodo;
}

NodoAVL* AVL::eliminar(NodoAVL* nodo, const string& id, bool& eliminado) {
    if (nodo == nullptr) return nullptr;
    string idNodo = nodo->getPaciente()->getId();
    if (id < idNodo) {
        nodo->setIzquierdo(eliminar(nodo->getIzquierdo(), id, eliminado));
    } else if (id > idNodo) {
        nodo->setDerecho(eliminar(nodo->getDerecho(), id, eliminado));
    } else {
        eliminado = true;
        if (nodo->getIzquierdo() == nullptr || nodo->getDerecho() == nullptr) {
            NodoAVL* hijo = nodo->getIzquierdo() != nullptr ? nodo->getIzquierdo() : nodo->getDerecho();
            delete nodo->getPaciente();
            delete nodo;
            return hijo;
        }
        NodoAVL* sucesor = nodoMinimo(nodo->getDerecho());
        Patient* antiguo = nodo->getPaciente();
        nodo->setPaciente(sucesor->getPaciente());
        sucesor->setPaciente(antiguo);
        nodo->setDerecho(eliminar(nodo->getDerecho(), antiguo->getId(), eliminado));
    }
    return rebalancear(nodo);
}

bool AVL::eliminar(const string& id) {
    bool eliminado = false;
    raiz = eliminar(raiz, id, eliminado);
    if (eliminado) cantidad--;
    return eliminado;
}

static void agregarItem(string& salida, Patient* p) {
    if (!salida.empty()) salida += ", ";
    salida += p->getName() + " (" + p->getId() + ")";
}

void AVL::inorden(NodoAVL* nodo, string& salida) {
    if (nodo == nullptr) return;
    inorden(nodo->getIzquierdo(), salida);
    agregarItem(salida, nodo->getPaciente());
    inorden(nodo->getDerecho(), salida);
}

void AVL::preorden(NodoAVL* nodo, string& salida) {
    if (nodo == nullptr) return;
    agregarItem(salida, nodo->getPaciente());
    preorden(nodo->getIzquierdo(), salida);
    preorden(nodo->getDerecho(), salida);
}

void AVL::postorden(NodoAVL* nodo, string& salida) {
    if (nodo == nullptr) return;
    postorden(nodo->getIzquierdo(), salida);
    postorden(nodo->getDerecho(), salida);
    agregarItem(salida, nodo->getPaciente());
}

void AVL::factoresBalance(NodoAVL* nodo, string& salida) {
    if (nodo == nullptr) return;
    factoresBalance(nodo->getIzquierdo(), salida);
    if (!salida.empty()) salida += ", ";
    salida += nodo->getPaciente()->getId() + ": " + to_string(factorBalance(nodo));
    factoresBalance(nodo->getDerecho(), salida);
}

string AVL::inorden()   { string salida; inorden(raiz, salida);   return salida; }
string AVL::preorden()  { string salida; preorden(raiz, salida);  return salida; }
string AVL::postorden() { string salida; postorden(raiz, salida); return salida; }
string AVL::factoresBalance() { string salida; factoresBalance(raiz, salida); return salida; }

int AVL::altura() { return altura(raiz); }
int AVL::tamano() { return cantidad; }
bool AVL::estaVacio() { return raiz == nullptr; }