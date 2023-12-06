#pragma once

#include <stdexcept>

template <typename T>
class DNode {
public:
    T data;
    DNode* prev;
    DNode* next;

    DNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList;

template <typename T>
class DListIterator;

template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            DNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Add(const T& value) {
        DNode<T>* newNode = new DNode<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void Insert(const T& value, int index) {
        if (index < 0 || index > size) {
            std::cerr << "Index out of bounds." << std::endl;
            return;
        }

        DNode<T>* newNode = new DNode<T>(value);

        if (index == 0) {
            newNode->next = head;
            if (head) {
                head->prev = newNode;
            } else {
                tail = newNode;
            }
            head = newNode;
        } else if (index == size) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            DNode<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }

        size++;
    }

    T& Get(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds." << std::endl;
            exit(1);
        }

        DNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    int IndexOf(const T& value) {
        DNode<T>* current = head;
        int index = 0;

        while (current) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }

        return -1; // Element not found
    }

    T& Remove(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds." << std::endl;
            exit(1);
        }

        DNode<T>* removedNode;
        if (index == 0) {
            removedNode = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (index == size - 1) {
            removedNode = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            DNode<T>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            removedNode = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        T& removedData = removedNode->data;
        delete removedNode;
        size--;

        return removedData;
    }

    DListIterator<T> Iterator() {
        return DListIterator<T>(head);
    }

    int Size() {
        return size;
    }
};

template <typename T>
class DListIterator {
private:
    DNode<T>* current;

public:
    DListIterator(DNode<T>* start) : current(start) {}

    bool HasNext() {
        return current != nullptr;
    }

    T& Next() {
        if (!HasNext()) {
            std::cerr << "No more elements in the iterator." << std::endl;
            exit(1);
        }

        T& data = current->data;
        current = current->next;
        return data;
    }
};
