#pragma once
#include <stdexcept>
#include "Node.h"

template <class T>
class List {
private:
    Node<T>* start; // Primer nodo (nullptr si está vacía)
    Node<T>* end; // Último nodo (nullptr si está vacía)
    int count; // Cantidad de nodos

public:
    List() {
        this->start = nullptr;
        this->end = nullptr;
        this->count = 0;
    }

    ~List() { // Libera toda la memoria
        clear();
    }

    // Se prohíbe copiar para evitar doble delete
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    bool isEmpty() { // true si no hay nodos
        return this->start == nullptr;
    }

    void insertFirst(T value) { // Inserta al inicio: O(1)
        Node<T>* nuevo = new Node<T>(value);
        nuevo->setNext(this->start);
        this->start = nuevo;
        if (this->end == nullptr) this->end = nuevo;
        this->count++;
    }

    void insertLast(T value) { // Inserta al final: O(1)
        Node<T>* nuevo = new Node<T>(value);
        if (this->start == nullptr) {
            this->start = nuevo;
        } else {
            this->end->setNext(nuevo);
        }
        this->end = nuevo;
        this->count++;
    }

    void insert(T value, int index) { // Inserta en la posición "index" (0 = inicio)
        if (index < 0 || index > this->count) throw std::out_of_range("Indice fuera de rango");
        if (index == 0) {
            insertFirst(value);
            return;
        }
        if (index == this->count) {
            insertLast(value);
            return;
        }
        Node<T>* cursor = this->start; // Nodo anterior a la posición deseada
        for (int i = 0; i < index - 1; i++) {
            cursor = cursor->getNext();
        }
        Node<T>* nuevo = new Node<T>(value);
        nuevo->setNext(cursor->getNext());
        cursor->setNext(nuevo);
        this->count++;
    }

    T getFirst() { // Primer valor
        if (this->start == nullptr) throw std::out_of_range("Lista vacia");
        return this->start->getValue();
    }

    T getLast() { // Último valor: O(1)
        if (this->end == nullptr) throw std::out_of_range("Lista vacia");
        return this->end->getValue();
    }

    T get(int index) { // Valor en la posición "index"
        if (index < 0 || index >= this->count) throw std::out_of_range("Indice fuera de rango");
        Node<T>* cursor = this->start;
        for (int i = 0; i < index; i++) {
            cursor = cursor->getNext();
        }
        return cursor->getValue();
    }

    void remove(int index) { // Elimina el nodo en "index" y libera su memoria
        if (index < 0 || index >= this->count) throw std::out_of_range("Indice fuera de rango");
        if (index == 0) {
            Node<T>* toDelete = this->start;
            this->start = toDelete->getNext();
            if (this->start == nullptr) this->end = nullptr; // La lista quedó vacía
            delete toDelete;
            this->count--;
            return;
        }
        Node<T>* cursor = this->start; // Nodo anterior al que se elimina
        for (int i = 0; i < index - 1; i++) {
            cursor = cursor->getNext();
        }
        Node<T>* toDelete = cursor->getNext();
        cursor->setNext(toDelete->getNext());
        if (toDelete == this->end) this->end = cursor; // Se eliminó el último
        delete toDelete;
        this->count--;
    }

    void clear() { // Elimina todos los nodos
        while (this->start != nullptr) {
            Node<T>* temp = this->start->getNext();
            delete this->start;
            this->start = temp;
        }
        this->end = nullptr;
        this->count = 0;
    }

    int size() { // O(1)
        return this->count;
    }
};