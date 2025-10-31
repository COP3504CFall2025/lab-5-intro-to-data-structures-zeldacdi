#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;

    void PrintForward();

    void PrintReverse();
};

template<typename T>
LLS<T>::LLS() {
    list = new LinkedList<T>;
}

template<typename T>
T LLS<T>::peek() const {
    return list.getHead();
}

template<typename T>
void LLS<T>::push(const T& item) {
    list.AddHead(item);
}

template<typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}

template<typename T>
T LLS<T>::pop() {
    if (getSize() == 0) {
        throw std::invalid_argument("Stack Empty");
    }
    T item = peek();
    list.RemoveHead();
    return item;
}

template<typename T>
void LLS<T>::PrintForward() {
    list.PrintForward();
}

template<typename T>
void LLS<T>::PrintReverse() {
    list.PrintReverse();
}