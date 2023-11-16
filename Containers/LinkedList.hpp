#pragma once

#include <stdexcept>

template <typename T>
class Node
{
    public:
        T data;
        Node<T>* next;
        Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList
{
    private:
        Node<T>* head;
        int length;

    public:
        LinkedList() : head(nullptr), length(0) {}
        ~LinkedList() {this->Clear();}

        void Add(T data)
        {
            Node<T>* newNode = new Node<T>(data);

            if (head == nullptr) head = newNode;
            else
            {
                Node<T>* temp = head;
                while (temp->next != nullptr) temp = temp->next;
                temp->next = newNode;
            }
            length += 1;
        }

        void Insert(T value, int index)
        {
            if (index < 0 || index > length) throw std::out_of_range("Index is out of range");

            Node<T>* newNode = new Node<T>(value);

            if (index == 0)
            {
                newNode->next = head;
                head = newNode;
            } 
            else
            {
                Node<T>* current = head;
                for (int i = 0; i < index - 1; ++i) current = current->next;
                newNode->next = current->next;
                current->next = newNode;
            }

            length++;
        }

        void Clear()
        {
            while (head != nullptr)
            {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
            length = 0;
        }
        
        T& Get(int index)
        {
            if (index < 0 || index > length) throw std::out_of_range("Index is out of range");
            Node<T>* temp = head;
            for (int i = 0; i < index; ++i) temp = temp->next;
            return temp->data;
        }

        int IndexOf(const T& value)
        {
            Node<T>* current = head;
            int index = 0;
            while (current != nullptr)
            {
                if (current->data == value) return index;
                current = current->next;
                ++index;
            }
            return -1;
        }

        T& Remove(int index)
        {
            if (index < 0 || index >= length) throw std::out_of_range("Index is out of range");
            Node<T>* current = head;
            T* data;

            if (index == 0)
            {
                head = head->next;
                data = &current->data;
                delete current;
            }
            else
            {
                Node<T>* prev = nullptr;
                for (int i = 0; i < index; ++i)
                {
                    prev = current;
                    current = current->next;
                }
                prev->next = current->next;
                data = &current->data;
                delete current;
            }
            length--;
            return *data;
        }

        int Size() {return length;}

        // Definition of ListIterator class is inside LinkedList
        class ListIterator
        {
            private:
                Node<T>* current;

            public:
                ListIterator(Node<T>* startNode) : current(startNode) {}
                bool hasNext() {return current != nullptr;}
                T Next()
                {
                    if (current == nullptr)
                    {
                        throw std::out_of_range("No more elements in the list");
                    }
                    T data = current->data;
                    current = current->next;
                    return data;
                }
        };

        ListIterator Iterator() {return ListIterator(head);}
};