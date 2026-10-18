#pragma once
#include "List.h"

template <class T>
class Stack {
private:
    List<T> datos;

public:
    bool empty() { // true si la pila está vacía
        return datos.isEmpty();
    }

    void push(T value) { // Inserta un dato en el tope
        datos.insertFirst(value);
    }

    void pop() { // Remueve el tope (lanza excepción si está vacía)
        datos.remove(0);
    }

    T top() { // Retorna el tope (lanza excepción si está vacía)
        return datos.getFirst();
    }

    void clear() { // Vacía la pila
        datos.clear();
    }

    int size() { // Cantidad de datos
        return datos.size();
    }
};