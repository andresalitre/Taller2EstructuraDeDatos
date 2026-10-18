#pragma once
#include "List.h"

template <class T>
class Queue {
private:
    List<T> datos;

public:
    bool empty() { // true si la cola está vacía
        return datos.isEmpty();
    }

    void push(T value) { // Coloca el dato al final de la cola
        datos.insertLast(value);
    }

    void pop() { // Remueve el primer dato (lanza excepción si está vacía)
        datos.remove(0);
    }

    T front() { // Retorna el primer dato (lanza excepción si está vacía)
        return datos.getFirst();
    }

    void clear() { // Vacía la cola
        datos.clear();
    }

    int size() { // Cantidad de datos
        return datos.size();
    }
};