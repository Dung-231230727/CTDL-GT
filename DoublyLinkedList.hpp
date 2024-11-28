#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
using namespace std;

// Node
template<typename T>
class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

// Lớp DoublyLinkedList
template<typename T>
class DoublyLinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
        ~DoublyLinkedList();

        void pushFront(const T& value);
        void pushBack(const T& value);
        void popFront();
        void popBack();
        void removeAt(int position);
        Node<T>* find(int ma);
        void printList();
        int getSize();
        Node<T>* getHead(); 
};

// Destructor để giải phóng bộ nhớ
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

// Thêm phần tử vào đầu danh sách
template<typename T>
void DoublyLinkedList<T>::pushFront(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

// Thêm phần tử vào cuối danh sách
template<typename T>
void DoublyLinkedList<T>::pushBack(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Xóa phần tử đầu danh sách
template<typename T>
void DoublyLinkedList<T>::popFront() {
    if (head == nullptr) return;
    Node<T>* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size--;
}

// Xóa phần tử cuối danh sách
template<typename T>
void DoublyLinkedList<T>::popBack() {
    if (tail == nullptr) return;
    Node<T>* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size--;
}

// Xóa phần tử tại vị trí cụ thể
template<typename T>
void DoublyLinkedList<T>::removeAt(int position) {
    if (position < 0 || position >= size) return;
    if (position == 0) {
        popFront();
        return;
    }
    if (position == size - 1) {
        popBack();
        return;
    }
    Node<T>* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size--;
}

// Tìm kiếm phần tử theo mã
template<typename T>
Node<T>* DoublyLinkedList<T>::find(int ma) {
    Node<T>* current = head;
    int position = 0;
    while (current != nullptr) {
        if (current->data.getMaKH() == ma)
            return current;
        current = current->next;
        position++;
    }
    return nullptr;
}

// Hiển thị toàn bộ danh sách
template<typename T>
void DoublyLinkedList<T>::printList() {
    Node<T>* current = head;
    while (current != nullptr) {
        current->data.xuat();
        cout << endl;
        current = current->next;
    }
}

// Trả về kích thước của danh sách
template<typename T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

// Trả về con trỏ tới phần tử đầu tiên 
template<typename T> 
Node<T>* DoublyLinkedList<T>::getHead() { 
    return head; 
}

#endif // DOUBLY_LINKED_LIST_HPP
