#pragma once
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;

	explicit Node(T data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};

template <typename T>
void LinkedList<T>::PrintForward() const {
	Node<T>* current = head;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node<T>* current = tail;
	while (current != nullptr) {
		cout << current->data << " " << endl;
		current = current->prev;
	}
}

template <typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const {
	return count;
}

template <typename T>
Node<T>* LinkedList<T>::getHead() {
	return head;
}

template <typename T>
const Node<T>* LinkedList<T>::getHead() const {
	return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail() {
	return tail;
}

template <typename T>
const Node<T>* LinkedList<T>::getTail() const {
	return tail;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	if (head == nullptr) {
		head = new Node<T>(data);
		tail = head;
	}
	else {
		head->prev = new Node<T>(data);
		head->prev->next = head;
		head = head->prev;
	}
	count++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	if (tail == nullptr) {
		tail = new Node<T>(data);
		head = tail;
	}
	else {
		tail->next = new Node<T>(data);
		tail->next->prev = tail;
		tail = tail->next;
	}
	count++;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (head == nullptr) {
		return false;
	}
	if (head -> next == nullptr) {
		delete head;
		head = nullptr;
		return true;
	}
	head = head->next;
	delete head->prev;
	head->prev = nullptr;
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail == nullptr) {
		return false;
	}
	if (tail -> prev == nullptr) {
		delete tail;
		tail = nullptr;
		return true;
	}
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	count--;
	return true;
}

template<typename T>
void LinkedList<T>::Clear() {
	Node<T>* current = head;
	while (current != nullptr) {
		Node<T>* tempNext = current->next;
		delete current;
		current = tempNext;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	Clear();
	Node<T>* otherCurr = other.head;

	while (otherCurr != nullptr) {
		AddHead(otherCurr->data);
		otherCurr = otherCurr->next;
		delete otherCurr->prev;
	}

	other.count = 0;
	return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	Clear();
	Node<T>* otherCurr = rhs.head;

	while (otherCurr != nullptr) {
		AddHead(otherCurr->data);
		otherCurr = otherCurr->next;
	}

	return *this;
}


template<typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
	head = new Node<T>(list.getHead()->data);
	Node<T>* currNode = list.getHead()->next;
	count = 0;
	while (currNode != nullptr) {
		AddTail(currNode->data);
		currNode = currNode->next;
		count++;
	}
	tail = currNode->prev;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}

