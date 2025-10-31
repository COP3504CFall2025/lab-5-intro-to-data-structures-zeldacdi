#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ();

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward();

    void PrintReverse();

};

template<typename T>
LLQ<T>::LLQ() {
    LinkedList<T> l;
    list = l;
}

template<typename T>
T LLQ<T>::peek() const {
    return list.getHead()->data;
}

template<typename T>
void LLQ<T>::enqueue(const T& item) {
    list.AddTail(item);
}

template<typename T>
T LLQ<T>::dequeue() {
    T item = peek();
    list.RemoveHead();
    return item;
}

template<typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getCount();
}

template<typename T>
void LLQ<T>::PrintForward() {
    list.PrintForward();
}

template<typename T>
void LLQ<T>::PrintReverse() {
    list.PrintReverse();
}