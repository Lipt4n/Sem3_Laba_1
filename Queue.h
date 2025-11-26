#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Queue {
    DoublyList<T> list;
public:
    void push(T x) { list.push_back(x); }
    void pop() { if (list.length()) list.pop_front(); } //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void print() { return list.print(); }
    bool empty() const { return list.length() == 0; }
    int size() const { return list.length(); }
};
