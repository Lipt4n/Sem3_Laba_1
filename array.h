#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Array {
    T* arr;
    int size, cap;
    void grow() {
        cap = cap ? cap * 2 : 8;
        T* newarr = new T[cap];
        for (int i = 0; i < size; i++) newarr[i] = arr[i];
        delete[] arr;
        arr = newarr;
    }
public:
    Array() : arr(nullptr), size(0), cap(0) {}
    ~Array() { delete[] arr; }

    void push_back(T x) {
        if (size == cap) grow();
        arr[size++] = x;
    }
    void pop_back() {
        if (size > 0) {
            size--;
            arr[size] = T();   // вызываем конструктор по умолчанию
        }
    }
    void insert(int idx, T x) {
        if (idx < 0 || idx > size) throw "Некорректный индекс!";
        if (size == cap) grow();
        for (int i = size; i > idx; i--) arr[i] = arr[i-1];
        arr[idx] = x;
        size++;
    }
    void remove(int idx) {
        if (idx < 0 || idx >= size) throw "Некорректный индекс!";
        for (int i = idx; i < size-1; i++) arr[i] = arr[i+1];
        size--;
    }
    void replace(int idx, T x) {
        if (idx < 0 || idx >= size) throw "Некорректный индекс!";
        arr[idx] = x;
    }
    T& operator[](int i) { return arr[i]; }
    int length() const { return size; }
    void print() const { for (int i = 0; i < size; i++) cout << arr[i] << ' '; cout << endl; }
};