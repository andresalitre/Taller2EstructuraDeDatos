#include "ArbolDecision.h"

static bool esNino(Patient* p)            { return p->getAge() < 14; }
static bool tieneTrauma(Patient* p)       { return p->getTrauma() == 1; }
static bool requiereCirugia(Patient* p)   { return p->getRequiresSurgery() == 1; }
static bool tieneSintomasNeuro(Patient* p) { return p->getNeuroSymptoms() == 1; }
static bool tieneDolorPecho(Patient* p)   { return p->getPainType() == "pecho"; }
static bool tieneSignosGraves(Patient* p) { return p->getTemperature() >= 38.5 || p->getPain() >= 8; }
static bool estadiaLarga(Patient* p)      { return p->getHospitalDays() >= 2; }

ArbolDecision::ArbolDecision() {
    NodoDecision* pediatria = new NodoDecision("Pediatria");
    NodoDecision* cirugia = new NodoDecision("Cirugia");
    NodoDecision* traumatologia = new NodoDecision("Traumatologia");
    NodoDecision* neurologia = new NodoDecision("Neurologia");
    NodoDecision* cardiologia = new NodoDecision("Cardiologia");
    NodoDecision* urgencias = new NodoDecision("Urgencias");
    NodoDecision* hospitalizacion = new NodoDecision("Hospitalizacion");
    NodoDecision* medicinaGeneral = new NodoDecision("Medicina General");

    NodoDecision* preguntaDias = new NodoDecision("DiasHospitalizacion >= 2?",
        "DiasHospitalizacion >= 2", "DiasHospitalizacion < 2", estadiaLarga);
    preguntaDias->setSi(hospitalizacion);
    preguntaDias->setNo(medicinaGeneral);

    NodoDecision* preguntaGrave = new NodoDecision("Temperatura >= 38.5 o Dolor >= 8?",
        "Temperatura >= 38.5 o Dolor >= 8", "Temperatura < 38.5 y Dolor < 8", tieneSignosGraves);
    preguntaGrave->setSi(urgencias);
    preguntaGrave->setNo(preguntaDias);

    NodoDecision* preguntaPecho = new NodoDecision("TipoDolor == pecho?",
        "TipoDolor == pecho", "TipoDolor != pecho", tieneDolorPecho);
    preguntaPecho->setSi(cardiologia);
    preguntaPecho->setNo(preguntaGrave);

    NodoDecision* preguntaNeuro = new NodoDecision("SintomasNeurologicos == 1?",
        "SintomasNeurologicos == 1", "SintomasNeurologicos == 0", tieneSintomasNeuro);
    preguntaNeuro->setSi(neurologia);
    preguntaNeuro->setNo(preguntaPecho);

    NodoDecision* preguntaCirugia = new NodoDecision("RequiereCirugia == 1?",
        "RequiereCirugia == 1", "RequiereCirugia == 0", requiereCirugia);
    preguntaCirugia->setSi(cirugia);
    preguntaCirugia->setNo(traumatologia);

    NodoDecision* preguntaTrauma = new NodoDecision("Trauma == 1?",
        "Trauma == 1", "Trauma == 0", tieneTrauma);
    preguntaTrauma->setSi(preguntaCirugia);
    preguntaTrauma->setNo(preguntaNeuro);

    raiz = new NodoDecision("Edad < 14?", "Edad < 14", "Edad >= 14", esNino);
    raiz->setSi(pediatria);
    raiz->setNo(preguntaTrauma);
}

ArbolDecision::~ArbolDecision() {
    destruir(raiz);
}

void ArbolDecision::destruir(NodoDecision* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->getSi());
    destruir(nodo->getNo());
    delete nodo;
}

bool ArbolDecision::esValido(Patient* p) {
    if (p == nullptr) return false;
    if (p->getAge() < 0 || p->getAge() > 120) return false;
    if (p->getTemperature() < 30.0 || p->getTemperature() > 45.0) return false;
    if (p->getBloodPressure() < 0) return false;
    if (p->getPain() < 0 || p->getPain() > 10) return false;
    if (p->getTrauma() != 0 && p->getTrauma() != 1) return false;
    if (p->getNeuroSymptoms() != 0 && p->getNeuroSymptoms() != 1) return false;
    if (p->getRequiresSurgery() != 0 && p->getRequiresSurgery() != 1) return false;
    if (p->getHospitalDays() < 0) return false;
    string tipo = p->getPainType();
    return tipo == "pecho" || tipo == "cabeza" || tipo == "abdomen" || tipo == "extremidad" || tipo == "otro";
}

string ArbolDecision::evaluar(Patient* p, string& ruta) {
    ruta = "";
    if (!esValido(p)) {
        ruta = "Datos invalidos";
        return "Urgencias";
    }
    NodoDecision* actual = raiz;
    while (!actual->esHoja()) {
        bool respuesta = actual->evaluar(p);
        if (!ruta.empty()) ruta += " -> ";
        ruta += respuesta ? actual->getTextoSi() : actual->getTextoNo();
        actual = respuesta ? actual->getSi() : actual->getNo();
    }
    return actual->getServicio();
}

static string etiqueta(NodoDecision* nodo) {
    return nodo->esHoja() ? "[" + nodo->getServicio() + "]" : nodo->getPregunta();
}

static void agregar(string& salida, const string& texto) {
    if (!salida.empty()) salida += ", ";
    salida += texto;
}

void ArbolDecision::preorden(NodoDecision* nodo, string& salida) {
    if (nodo == nullptr) return;
    agregar(salida, etiqueta(nodo));
    preorden(nodo->getSi(), salida);
    preorden(nodo->getNo(), salida);
}

void ArbolDecision::inorden(NodoDecision* nodo, string& salida) {
    if (nodo == nullptr) return;
    inorden(nodo->getSi(), salida);
    agregar(salida, etiqueta(nodo));
    inorden(nodo->getNo(), salida);
}

void ArbolDecision::postorden(NodoDecision* nodo, string& salida) {
    if (nodo == nullptr) return;
    postorden(nodo->getSi(), salida);
    postorden(nodo->getNo(), salida);
    agregar(salida, etiqueta(nodo));
}

string ArbolDecision::preorden()  { string salida; preorden(raiz, salida);  return salida; }
string ArbolDecision::inorden()   { string salida; inorden(raiz, salida);   return salida; }
string ArbolDecision::postorden() { string salida; postorden(raiz, salida); return salida; }