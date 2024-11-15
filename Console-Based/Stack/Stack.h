#pragma once
#include <iostream>

template <typename T>
class Stack {
private:
    struct Element;
    Element* top;
    size_t size;
public:
    Stack();
    Stack(Element* top, size_t size);
    ~Stack();
    size_t getSize() const;
    void push(T value);
    void pop();
    bool isEmpty() const;
    T& getTop() const;
};