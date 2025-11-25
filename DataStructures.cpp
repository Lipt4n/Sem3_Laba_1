#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};


// 1. ДИНАМИЧЕСКИЙ МАССИВ

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


// 2. ОДНОСВЯЗНЫЙ СПИСОК

template<typename T>
class SinglyList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int len = 0;

    void del(Node<T>* n) { delete n; }
public:
    ~SinglyList() { while(head) pop_front(); }

    void push_front(T x) {
        Node<T>* n = new Node<T>(x);
        n->next = head;
        head = n;
        if (!tail) tail = n;
        len++;
    }
    void push_back(T x) {
        Node<T>* n = new Node<T>(x);
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = tail;
        len++;
    }
    void insert_after(Node<T>* pos, T x) {
        if (!pos) return;
        Node<T>* n = new Node<T>(x);
        n->next = pos->next;
        pos->next = n;
        if (tail == pos) tail = n;
        len++;
    }
    void insert_before(Node<T>* pos, T x) {
        if (!pos) return;
        if (pos == head) return push_front(x);
        Node<T>* cur = head;
        while (cur && cur->next != pos) cur = cur->next;
        if (cur) insert_after(cur, x);
    }

    void pop_front() {
        if (!head) return;
        Node<T>* t = head;
        head = head->next;
        del(t);
        if (!head) tail = nullptr;
        len--;
    }
    void pop_back() {
        if (!head) return;
        if (head == tail) { pop_front(); return; }
        Node<T>* cur = head;
        while (cur->next != tail) cur = cur->next;
        del(tail);
        tail = cur;
        tail->next = nullptr;
        len--;
    }

    Node<T>* find(T x) {
        Node<T>* cur = head;
        while (cur && cur->data != x) cur = cur->next;
        return cur;
    }
    bool remove_value(T x) {
        if (!head) return false;
        if (head->data == x) { pop_front(); return true; }
        Node<T>* cur = head;
        while (cur->next && cur->next->data != x) cur = cur->next;
        if (cur->next) {
            Node<T>* t = cur->next;
            cur->next = t->next;
            if (t == tail) tail = cur;
            del(t);
            len--;
            return true;
        }
        return false;
    }
    void print() const {
        for (Node<T>* p = head; p; p = p->next) cout << p->data << " -> ";
        cout << "null" << endl;
    }
    int length() const { return len; }
    Node<T>* get_head() const { return head; }
};


// 3. ДВУСВЯЗНЫЙ СПИСОК

template<typename T>
class DoublyList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int len = 0;
public:
    ~DoublyList() { while(head) { Node<T>* t = head; head = head->next; delete t; } }

    void push_front(T x) {
        Node<T>* n = new Node<T>(x);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        len++;
    }
    void push_back(T x) {
        Node<T>* n = new Node<T>(x);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        len++;
    }
    void insert_after(Node<T>* p, T x) {
        if (!p) return;
        Node<T>* n = new Node<T>(x);
        n->next = p->next; n->prev = p;
        if (p->next) p->next->prev = n;
        p->next = n;
        if (p == tail) tail = n;
        len++;
    }
    void insert_before(Node<T>* p, T x) {
        if (!p) return;
        if (p == head) return push_front(x);
        insert_after(p->prev, x);
    }
    void remove(Node<T>* p) {
        if (!p) return;
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
        if (head == p) head = p->next;
        if (tail == p) tail = p->prev;
        delete p;
        len--;
    }
    bool remove_value(T x) {
        for (Node<T>* p = head; p; p = p->next)
            if (p->data == x) { remove(p); return true; }
        return false;
    }
    void pop_front() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        len--;
    }
    void pop_back() {
        if (!tail) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        len--;
    }       
    Node<T>* find(T x) {
        for (Node<T>* p = head; p; p = p->next)
            if (p->data == x) return p;
        return nullptr;
    }
    void print() const {
        for (Node<T>* p = head; p; p = p->next) cout << p->data << " <-> ";
        cout << "null\n";
    }
    int length() const { return len; }
};


// 4. СТЕК (на массиве)

template<typename T>
class Stack {
    Array<T> a;
public:
    void push(T x) { a.push_back(x); }
    void pop() { if (a.length()) a.remove(a.length()-1); }
    void print() { a.print(); }
    bool empty() const { return a.length() == 0; }
    int size() const { return a.length(); }
};


// 5. ОЧЕРЕДЬ (на двусвязном списке)

template<typename T>
class Queue {
    DoublyList<T> list;
public:
    void push(T x) { list.push_back(x); }
    void pop() { if (list.length()) list.pop_front(); }
    void print() { return list.print(); }
    bool empty() const { return list.length() == 0; }
    int size() const { return list.length(); }
};


// 6. БИНАРНОЕ ДЕРЕВО ПОИСКА

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(T v) : data(v) {}
};

template<typename T>
class BST {
    TreeNode<T>* root = nullptr;

    TreeNode<T>* insert(TreeNode<T>* node, T val) {
        if (!node) return new TreeNode<T>(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }
    TreeNode<T>* min(TreeNode<T>* node) {
        while (node->left) node = node->left;
        return node;
    }
    TreeNode<T>* remove(TreeNode<T>* node, T val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = remove(node->left, val);
        else if (val > node->data) node->right = remove(node->right, val);
        else {
            if (!node->left) { TreeNode<T>* t = node->right; delete node; return t; }
            if (!node->right) { TreeNode<T>* t = node->left; delete node; return t; }
            TreeNode<T>* t = min(node->right);
            node->data = t->data;
            node->right = remove(node->right, t->data);
        }
        return node;
    }
    void inorder(TreeNode<T>* node) {
        if (node) { inorder(node->left); cout << node->data << " "; inorder(node->right); }
    }
    void clear(TreeNode<T>* node) {
        if (node) { clear(node->left); clear(node->right); delete node; }
    }
public:
    void insert(T x) { root = insert(root, x); }
    void remove(T x) { root = remove(root, x); }
    bool find(T x) {
        TreeNode<T>* cur = root;
        while (cur) {
            if (x == cur->data) return true;
            cur = (x < cur->data) ? cur->left : cur->right;
        }
        return false;
    }
    void print() { inorder(root); cout << endl; }
    ~BST() { clear(root); }
};

//Тест

void test() {
    cout << "Dynamic array" << endl;
    Array<int> a;
    a.push_back(10); //10
    a.push_back(123); a.push_back(123); a.push_back(123); //10 123 123 123
    a.pop_back(); //10 123 123
    a.insert(1,20); //10 20 123 123
    a.replace(2,30); //10 20 30 123
    a.remove(3); //10 20 30
    a.print();
    cout << a[0] << " " << a.length() << endl; //10, 3

    cout << "Singly list" << endl;
    SinglyList<int> s;
    s.push_back(1); // 1 -> null
    Node<int>* node_with_1 = s.find(1);
    s.insert_after(node_with_1, 2); // 1 -> 2 -> null
    s.insert_before(node_with_1, 123); // 123 -> 1 -> 2 -> null
    s.pop_front(); // 1 -> 2 -> null
    s.push_front(0); // 0 -> 1 -> 2 -> null
    s.push_back(123); // 0 -> 1 -> 2 -> 123 -> null
    s.remove_value(123); // 0 -> 1 -> 2 -> null
    s.print();
    cout << s.length() << endl; // 3

    cout << "Doubly list" << endl;
    DoublyList<int> d;
    d.push_back(2); // 2 <-> null
    d.push_front(1); // 1 <-> 2 <-> null
    d.insert_after(d.find(2), 3); // 1 <-> 2 <-> 3 <-> null
    d.insert_before(d.find(1), 0); // 0 <-> 1 <-> 2 <-> 3 <-> null
    d.push_back(123); // 0 <-> 1 <-> 2 <-> 3 <-> 123 <-> null
    d.remove_value(123); // 0 <-> 1 <-> 2 <-> 3 <-> null
    d.print();
    cout << d.length() << endl; // 4

    cout << "Stack" << endl;
    Stack<int> st;
    st.push(9); // 9
    st.push(8); // 9 8
    st.push(123); // 9 8 123
    st.pop(); // 9 8
    st.print(); 
    cout << st.size() << " " << st.empty() << endl; // 2 0

    cout << "Queue" << endl;
    Queue<int> q;
    q.push(-1); q.push(0); q.push(1); q.push(2); // -1 0 1 2
    q.pop(); q.pop(); // 1 2
    q.print();
    cout << q.size() << " " << q.empty() << endl;
    
    cout << "Binary Search Tree" << endl;
    BST<int> tree;
    tree.insert(50); tree.insert(30); tree.insert(70); tree.insert(20); //20 30 50 70
    tree.remove(30); // 20 50 70
    tree.print();
}

int main() {
    test();
    return 0;
}

