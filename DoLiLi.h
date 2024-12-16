#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        DeleteAll();
    }

    void AddToHead(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void AddToTail(T value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void DeleteFromHead() {
        if (!head) return;

        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    void DeleteFromTail() {
        if (!tail) return;

        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void DeleteAll() {
        while (head) {
            DeleteFromHead();
        }
    }

    void Show() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void InsertAtPosition(T value, int position) {
        if (position < 0) return;

        Node* newNode = new Node(value);
        if (position == 0) {
            AddToHead(value);
            return;
        }

        Node* current = head;
        for (int i = 0; i < position - 1 && current; ++i) {
            current = current->next;
        }

        if (!current) {
            AddToTail(value);
        }
        else {
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) {
                current->next->prev = newNode;
            }
            else {
                tail = newNode;
            }
            current->next = newNode;
        }
    }

    void DeleteAtPosition(int position) {
        if (position < 0 || !head) return;

        if (position == 0) {
            DeleteFromHead();
            return;
        }

        Node* current = head;
        for (int i = 0; i < position && current; ++i) {
            current = current->next;
        }

        if (!current) return;

        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        else {
            tail = current->prev;
        }

        delete current;
    }

    int Find(T value) const {
        Node* current = head;
        int position = 0;

        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            ++position;
        }

        return -1;
    }

    int FindAndReplace(T oldValue, T newValue) {
        Node* current = head;
        int replaceCount = 0;

        while (current) {
            if (current->data == oldValue) {
                current->data = newValue;
                ++replaceCount;
            }
            current = current->next;
        }

        return replaceCount > 0 ? replaceCount : -1;
    }

    void Reverse() {
        Node* current = head;
        Node* temp = nullptr;

        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp) {
            head = temp->prev;
        }
    }
};

#endif