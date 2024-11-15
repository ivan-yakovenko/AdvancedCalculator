#include "Stack.h"

template <typename T>

struct Stack<T>::Element {
    T value = T();
    Element* pNext = nullptr;
};


template <typename T>
Stack<T>::Stack() {
    top = nullptr;
    size = 0;
}

template <typename T>
Stack<T>::Stack(Stack::Element *top, size_t size) {
    this->top = top;
    this->size = size;
}

template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
size_t Stack<T>::getSize() const {
    return size;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void Stack<T>::push(T value) {
    size++;
    if(top == nullptr) {
        top = new Element;
        top->value = value;
        return;
    }
    Element* temp = new Element;
    temp->value = value;
    temp->pNext = top;
    top = temp;
}

template <typename T>
void Stack<T>::pop() {
    if (top == nullptr) {
        return;
    }
    Element *temp = top;
    top = top->pNext;
    delete temp;
    size--;
}

template <typename T>
T &Stack<T>::getTop() const{
    return top->value;
}