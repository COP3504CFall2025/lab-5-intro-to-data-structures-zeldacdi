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
    LLS(const LLS& other) = default;
    LLS(LLS&& other) = default;

    LLS& operator=(const LLS& other) = default;
    LLS& operator=(LLS&& other) noexcept = default;

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
    list.addHead(item);
}

template<typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}

template<typename T>
T LLS<T>::pop() {
    if (getSize() == 0) {
        throw std::runtime_error("Stack Empty");
    }
    T item = peek();
    list.removeHead();
    return item;
}
