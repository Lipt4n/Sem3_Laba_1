#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Stack {
    Array<T> a;
public:
    void push(T x) { a.push_back(x); }
    auto pop() { if (a.length()) a.remove(a.length()-1); } //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void print() { a.print(); }
    bool empty() const { return a.length() == 0; }
    int size() const { return a.length(); }
};