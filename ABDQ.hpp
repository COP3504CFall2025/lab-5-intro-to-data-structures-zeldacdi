#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void shrinkIfNeeded();

    void addExtrema(size_t& extrema);

    void subtractExtrema(size_t& extrema);

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    void printForward();
    void printReverse();

    void ensureCapacity();
};

template<typename T>
ABDQ<T>::ABDQ() {
    capacity_ = 4;
    size_ = 0;
    data_ = new T[capacity_];
    front_ = 0;
    back_ = 0;
}

template<typename T>
ABDQ<T>::ABDQ(const size_t capacity) {
    capacity_ = capacity;
    size_ = 0;
    data_ = new T[capacity_];
    front_ = 0;
    back_ = 0;
}

template<typename T>
ABDQ<T>::ABDQ(const ABDQ& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new T[capacity_];
    front_ = other.front_;
    back_ = other.back_;
    for (size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& other) {
    if (this == &other) {
        return *this;
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    delete[] data_;
    T* tempArr = new T[capacity_];
    for (size_t i = 0; i < size_; i++) {
        tempArr[i] = other.data_[i];
    }
    data_ = tempArr;
    tempArr = nullptr;
    return *this;
}

template<typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    front_ = other.front_;
    back_ = other.back_;
    other.capacity_ = 0;
    other.size_ = 0;
    other.data_ = nullptr;
    other.front_ = 0;
    other.back_ = 0;
}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    front_ = other.front_;
    back_ = other.back_;
    other.capacity_ = 0;
    other.size_ = 0;
    other.data_ = nullptr;
    other.front_ = 0;
    other.back_ = 0;

    return *this;
}

template<typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    capacity_ = 0;
    size_ = 0;
}

template<typename T>
void ABDQ<T>::ensureCapacity() {
    capacity_ *= SCALE_FACTOR;
    T* tempArr = new T[capacity_];
    for (size_t i = 0; i < size_; i++) {
        tempArr[i] = data_[i];
    }
    delete[] data_;
    data_ = tempArr;
    tempArr = nullptr;
}

template<typename T>
const T& ABDQ<T>::front() const {
    if (size_ == 0) {
        throw std::runtime_error("Array is empty!");
    }
    return data_[front_];
}

template<typename T>
const T& ABDQ<T>::back() const {
    if (size_ == 0) {
        throw std::runtime_error("Array is empty!");
    }
    return data_[back_];
}

template<typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}

template<typename T>
void ABDQ<T>::addExtrema(size_t& extrema) {
    if (++extrema >= capacity_) {
        extrema = 0;
    }
}

template<typename T>
void ABDQ<T>::subtractExtrema(size_t& extrema) {
    if (extrema == 0) {
        extrema = capacity_ - 1;
    }
    else {
        extrema--;
    }
}

template<typename T>
void ABDQ<T>::pushFront(const T& item) {
    if (size_ >= capacity_) {
        ensureCapacity();
    }

    if (size_ != 0) {
        subtractExtrema(front_);
    }

    data_[front_] = item;
    size_++;
}

template<typename T>
void ABDQ<T>::pushBack(const T& item) {
    if (size_ >= capacity_) {
        ensureCapacity();
    }

    if (size_ != 0) {
        addExtrema(back_);
    }

    data_[back_] = item;
    size_++;
}

template<typename T>
T ABDQ<T>::popFront() {
    if (size_ == 0) {
        throw std::runtime_error("Array is already empty!");
    }
    T deletedItem = front();

    addExtrema(front_);

    size_--;
    return deletedItem;
}

template<typename T>
T ABDQ<T>::popBack() {
    if (size_ == 0) {
        throw std::runtime_error("Array is already empty!");
    }
    T deletedItem = back();

    subtractExtrema(back_);

    size_--;
    return deletedItem;
}

template<typename T>
void ABDQ<T>::shrinkIfNeeded() {
    T* newArray = new T[capacity_ / SCALE_FACTOR];
    for (size_t i = 0; i < std::max(front_, back_) - std::min(front_, back_); i++) {
        newArray[i] = data_[front_];
        addExtrema(front_);
    }

    back_ = std::max(front_, back_) - std::min(front_, back_);
    front_ = 0;
}

template<typename T>
void ABDQ<T>::printForward() {
    for (T item : data_) {
        std::cout << item << std::endl;
    }
}

template<typename T>
void ABDQ<T>::printReverse() {
    for (int i = size_ - 1; i >= 0; i--) {
        std::cout << data_[i] << std::endl;
    }
}