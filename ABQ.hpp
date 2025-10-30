#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

    void PrintForward();
    void PrintReverse();

};

template<typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABQ<T>::ABQ(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABQ<T>::ABQ(const ABQ& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        array_[i] = other.array_[i];
    }
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    delete[] array_;
    T* tempArr = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        tempArr[i] = rhs.array_[i];
    }
    array_ = tempArr;
    tempArr = nullptr;
    return *this;
}

template<typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
    return *this;
}

template<typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    capacity_ = 0;
    curr_size_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template<typename T>
[[nodiscard]] T* ABQ<T>::getData() const noexcept {
    return array_;
}

template<typename T>
void ABQ<T>::enqueue(const T& data) {
    if (curr_size_ >= capacity_) {
        capacity_ *= scale_factor_;
        T* tempArr = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            tempArr[i] = array_[i];
        }
        delete[] array_;
        array_ = tempArr;
        tempArr = nullptr;
    }

    array_[curr_size_] = data;
    curr_size_++;
}

template<typename T>
T ABQ<T>::peek() const {
    return array_[0];
}

template<typename T>
T ABQ<T>::dequeue() {
    T deletedElement = array_[0];

    T* tempArr = new T[capacity_];
    for (size_t i = 1; i < curr_size_; i++) {
        tempArr[i-1] = array_[i];
    }
    delete[] array_;
    array_ = tempArr;
    tempArr = nullptr;

    curr_size_--;
    return deletedElement;
}

template<typename T>
void ABQ<T>::PrintForward() {
    for (T item : array_) {
        std::cout << item << std::endl;
    }
}

template<typename T>
void ABQ<T>::PrintReverse() {
    for (int i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}