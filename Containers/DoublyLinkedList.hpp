#pragma once

#include <stdexcept>

template <typename T>
class DNode
{
    public:
        T data;
        DNode<T>* prev;
        DNode<T>* next;
        DNode(T data) : Node<T>(data), prev(nullptr), next(nullptr) {}
};


template <typename T>
class DoublyLinkedList
{
    public:
        DoublyLinkedList() : LinkedList<T>() {}
        ~DoublyLinkedList() {this->Clear();}

        void Add(T data) override
        {
            DNode<T>* newNode = new DNode<T>(data);
            if (this->head == nullptr)
            {
                this->head = newNode;
            }
            else
            {
                DNode<T>* temp = static_cast<DNode<T>*>(this->head);
                while (temp->next != nullptr)
                {
                    temp = static_cast<DNode<T>*>(temp->next);
                }
                temp->next = newNode;
                newNode->prev = temp;
            }
            this->length++;
        }

        void Insert(T value, int index) override
        {
            if (index < 0 || index > this->length)
            {
                throw std::out_of_range("Index out of range");
            }
            DNode<T>* newNode = new DNode<T>(value);
            if (index == 0)
            {
                newNode->next = this->head;
                if (this->head != nullptr)
                {
                    static_cast<DNode<T>*>(this->head)->prev = newNode;
                }
                this->head = newNode;
            }
            else
            {
                DNode<T>* temp = static_cast<DNode<T>*>(this->head);
                for (int i = 0; i < index - 1; ++i)
                {
                    temp = static_cast<DNode<T>*>(temp->next);
                }
                newNode->next = temp->next;
                newNode->prev = temp;
                if (temp->next != nullptr)
                {
                    static_cast<DNode<T>*>(temp->next)->prev = newNode;
                }
                temp->next = newNode;
            }
            this->length++;
        }

        T& Remove(int index) override
        {
            if (index < 0 || index >= this->length)
            {
                throw std::out_of_range("Index out of range");
            }
            DNode<T>* temp = static_cast<DNode<T>*>(this->head);
            if (index == 0)
            {
                this->head = temp->next;
                if (this->head != nullptr)
                {
                    static_cast<DNode<T>*>(this->head)->prev = nullptr;
                }
            }
            else
            {
                for (int i = 0; i < index; ++i)
                {
                    temp = static_cast<DNode<T>*>(temp->next);
                }
                temp->prev->next = temp->next;
                if (temp->next != nullptr)
                {
                    static_cast<DNode<T>*>(temp->next)->prev = temp->prev;
                }
            }
            T& data = temp->data;
            delete temp;
            this->length--;
            return data;
        }

        void Clear() override {
            while (this->head != nullptr) {
                DNode<T>* temp = static_cast<DNode<T>*>(this->head);
                this->head = temp->next;
                delete temp;
            }
            this->length = 0;
        }

        // Other methods can be overridden as needed
};
