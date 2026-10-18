#pragma once

template <class T>
class Node {
private:
    T value;
    Node<T>* next;

public:
    Node(T value) {
        this->value = value;
        this->next = nullptr;
    }

    T getValue() { return this->value; }
    void setValue(T value) { this->value = value; }

    Node<T>* getNext() { return this->next; }
    void setNext(Node<T>* next) { this->next = next; }
};