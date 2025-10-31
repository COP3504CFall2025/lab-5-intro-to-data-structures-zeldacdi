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
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void clear();

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
void LinkedList<T>::printForward() const {
	Node<T>* current = head;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->next;
	}
}

template <typename T>
void LinkedList<T>::printReverse() const {
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
	if (count == 0) {
		throw std::runtime_error("list is empty");
	}
	return head;
}

template <typename T>
const Node<T>* LinkedList<T>::getHead() const {
	if (count == 0) {
		throw std::runtime_error("list is empty");
	}
	return head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail() {
	if (count == 0) {
		throw std::runtime_error("list is empty");
	}
	return tail;
}

template <typename T>
const Node<T>* LinkedList<T>::getTail() const {
	if (count == 0) {
		throw std::runtime_error("list is empty");
	}
	return tail;
}

template <typename T>
void LinkedList<T>::addHead(const T& data) {
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
void LinkedList<T>::addTail(const T& data) {
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
bool LinkedList<T>::removeHead() {
	if (head == nullptr) {
		return false;
	}
	if (head -> next == nullptr) {
		delete head;
		head = nullptr;
		tail = nullptr;
		count--;
		return true;
	}
	head = head->next;
	delete head->prev;
	head->prev = nullptr;
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
	if (tail == nullptr) {
		return false;
	}
	if (tail -> prev == nullptr) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		count--;
		return true;
	}
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	count--;
	return true;
}

template<typename T>
void LinkedList<T>::clear() {
	if (count == 0) {
		return;
	}
	Node<T>* current = head;
	while (current != nullptr) {
		Node<T>* tempNext = current->next;
		delete current;
		current = tempNext;
	}
	count = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	clear();
	Node<T>* otherCurr = other.head;

	while (otherCurr != nullptr) {
		addHead(otherCurr->data);
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
	clear();
	Node<T>* otherCurr = rhs.head;

	while (otherCurr != nullptr) {
		addHead(otherCurr->data);
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
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	head = new Node<T>(list.getHead()->data);
	Node<T>* currNode = list.getHead()->next;
	count = 0;
	while (currNode != nullptr) {
		addTail(currNode->data);
		currNode = currNode->next;
		count++;
	}
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
	clear();
}

