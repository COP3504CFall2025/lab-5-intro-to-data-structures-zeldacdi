#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward();

    void PrintReverse();
};

template<typename T>
LLDQ<T>::LLDQ() {
    list = new LinkedList<T>;
}

template<typename T>
const T& LLDQ<T>::front() const {
    return list.getHead();
}

template<typename T>
const T& LLDQ<T>::back() const {
    return list.getTail();
}

template<typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.addHead(item);
}

template<typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.addTail(item);
}

template<typename T>
T LLDQ<T>::popFront() {
    T item = front();
    list.removeHead();
    return item;
}

template<typename T>
T LLDQ<T>::popBack() {
    T item = back();
    list.removeTail();
    return item;
}

template<typename T>
std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getCount();
}

template<typename T>
void LLDQ<T>::PrintForward() {
    list.printForward();
}

template<typename T>
void LLDQ<T>::PrintReverse() {
    list.printReverse();
}






