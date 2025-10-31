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
    LLS() = default;

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;
};

template<typename T>
T LLS<T>::peek() const {
    if (list.getCount() == 0) {
        throw std::runtime_error("list is empty");
    }
    return list.getHead()->data;
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
