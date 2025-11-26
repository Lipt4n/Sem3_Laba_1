#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Queue {
    DoublyList<T> list;
public:
    void push(T x) { list.push_back(x); }
    auto pop() {
        T res;
        if (list.length()) {
            res = list.pop_front();
        }
        return res;
    }
    void print() { return list.print(); }
    bool empty() const { return list.length() == 0; }
    int size() const { return list.length(); }
};
