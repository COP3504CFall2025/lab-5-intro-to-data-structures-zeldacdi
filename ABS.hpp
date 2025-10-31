#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

    void PrintForward();
    void PrintReverse();

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template<typename T>
ABS<T>::ABS() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABS<T>::ABS(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABS<T>::ABS(const ABS& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        array_[i] = other.array_[i];
    }
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
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
ABS<T>::ABS(ABS&& other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
    return *this;
}

template<typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
    capacity_ = 0;
    curr_size_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template<typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}

template<typename T>
void ABS<T>::push(const T& data) {
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
T ABS<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::runtime_error("Array is empty!");
    }
    return array_[curr_size_ - 1];
}

template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) {
        throw std::runtime_error("Stack Empty");
    }
    T deletedElement = array_[curr_size_];
    curr_size_--;

    if (curr_size_ <= capacity_ / 2) {
        capacity_ /= 2;
    }

    T* tempArr = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        tempArr[i] = array_[i];
    }
    delete[] array_;
    array_ = tempArr;
    tempArr = nullptr;

    return deletedElement;
}

template<typename T>
void ABS<T>::PrintForward() {
    for (T item : array_) {
        std::cout << item << std::endl;
    }
}

template<typename T>
void ABS<T>::PrintReverse() {
    for (int i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}