#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "array.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "BST.h"

using namespace std;

map<string, Array<int>> arrays;
map<string, SinglyList<int>> singlyLists;
map<string, DoublyList<int>> doublyLists;
map<string, Stack<int>> stacks;
map<string, Queue<int>> queues;
map<string, BST<int>> trees;


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

vector<string> split(const string& s) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

string to_upper(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


void process_command(const string& command) {
    vector<string> tokens = split(command);
    if (tokens.empty()) return;

    string cmd = to_upper(tokens[0]);
    
    // === МАССИВ (A) ===
    if (cmd == "APUB" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        arrays[name].push_back(value);
        cout << "OK" << endl;
    }
    else if (cmd == "APOB" && tokens.size() >= 2) {
        string name = tokens[1];
        arrays[name].pop_back();
        cout << "OK" << endl;
    }
    else if (cmd == "AIN" && tokens.size() >= 4) {
        string name = tokens[1];
        int idx = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        arrays[name].insert(idx, value);
        cout << "OK" << endl;
    }
    else if (cmd == "AREM" && tokens.size() >= 3) {
        string name = tokens[1];
        int idx = stoi(tokens[2]);
        arrays[name].remove(idx);
        cout << "OK" << endl;
    }
    else if (cmd == "AREP" && tokens.size() >= 4) {
        string name = tokens[1];
        int idx = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        arrays[name].replace(idx, value);
        cout << "OK" << endl;
    }
    else if (cmd == "AGET" && tokens.size() >= 3) {
        string name = tokens[1];
        int idx = stoi(tokens[2]);
        cout << arrays[name][idx] << endl;
    }
    else if (cmd == "ALEN" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << arrays[name].length() << endl;
    }
    else if (cmd == "APRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        arrays[name].print();
    }
    // === ОДНОСВЯЗНЫЙ СПИСОК (S) ===
    else if (cmd == "SPUF" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        singlyLists[name].push_front(value);
        cout << "OK" << endl;
    }
    else if (cmd == "SPUB" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        singlyLists[name].push_back(value);
        cout << "OK" << endl;
    }
    else if (cmd == "SINA" && tokens.size() >= 4) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        Node<int>* node = singlyLists[name].find(target);
        if (node) {
            singlyLists[name].insert_after(node, value);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }
    }
    else if (cmd == "SINB" && tokens.size() >= 4) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        Node<int>* node = singlyLists[name].find(target);
        if (node) {
            singlyLists[name].insert_before(node, value);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }
    }
    else if (cmd == "SPOF" && tokens.size() >= 2) {
        string name = tokens[1];
        singlyLists[name].pop_front();
        cout << "OK" << endl;
    }
    else if (cmd == "SPOB" && tokens.size() >= 2) {
        string name = tokens[1];
        singlyLists[name].pop_back();
        cout << "OK" << endl;
    }
    else if (cmd == "SREB" && tokens.size() >= 2) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        Node<int>* node = singlyLists[name].find(target);
        if (node) {
            singlyLists[name].remove_before(node);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }        
    }
    else if (cmd == "SREA" && tokens.size() >= 2) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        Node<int>* node = singlyLists[name].find(target);
        if (node) {
            singlyLists[name].remove_after(node);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        } 
    }
    else if (cmd == "SREM" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        bool result = singlyLists[name].remove_value(value);
        cout << (result ? "OK" : "NOT_FOUND") << endl;
    }
    else if (cmd == "SLEN" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << singlyLists[name].length() << endl;
    }
    else if (cmd == "SPRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        singlyLists[name].print();
    }
    // === ДВУСВЯЗНЫЙ СПИСОК (D) ===
    else if (cmd == "DPUF" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        doublyLists[name].push_front(value);
        cout << "OK" << endl;
    }
    else if (cmd == "DPUB" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        doublyLists[name].push_back(value);
        cout << "OK" << endl;
    }
    else if (cmd == "DINA" && tokens.size() >= 4) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        Node<int>* node = doublyLists[name].find(target);
        if (node) {
            doublyLists[name].insert_after(node, value);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }
    }
    else if (cmd == "DINB" && tokens.size() >= 4) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        Node<int>* node = doublyLists[name].find(target);
        if (node) {
            doublyLists[name].insert_before(node, value);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }
    }
    else if (cmd == "DPOF" && tokens.size() >= 2) {
        string name = tokens[1];
        doublyLists[name].pop_front();
        cout << "OK" << endl;
    }
    else if (cmd == "DPOB" && tokens.size() >= 2) {
        string name = tokens[1];
        doublyLists[name].pop_back();
        cout << "OK" << endl;
    }
    else if (cmd == "DREB" && tokens.size() >= 2) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        Node<int>* node = doublyLists[name].find(target);
        if (node) {
            doublyLists[name].remove_before(node);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        }        
    }
    else if (cmd == "DREA" && tokens.size() >= 2) {
        string name = tokens[1];
        int target = stoi(tokens[2]);
        Node<int>* node = doublyLists[name].find(target);
        if (node) {
            doublyLists[name].remove_after(node);
            cout << "OK" << endl;
        } else {
            cout << "TARGET_NOT_FOUND" << endl;
        } 
    }
    else if (cmd == "DREM" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        bool result = doublyLists[name].remove_value(value);
        cout << (result ? "OK" : "NOT_FOUND") << endl;
    }
    else if (cmd == "DLEN" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << doublyLists[name].length() << endl;
    }
    else if (cmd == "DPRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        doublyLists[name].print();
    }
    // === СТЕК (ST) ===
    else if (cmd == "STPU" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        stacks[name].push(value);
        cout << "OK" << endl;
    }
    else if (cmd == "STPO" && tokens.size() >= 2) {
        string name = tokens[1];
        stacks[name].pop();
        cout << "OK" << endl;
    }
    else if (cmd == "STEM" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << (stacks[name].empty() ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "STSI" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << stacks[name].size() << endl;
    }
    else if (cmd == "STPRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        stacks[name].print();
    }
    // === ОЧЕРЕДЬ (Q) ===
    else if (cmd == "QPU" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        queues[name].push(value);
        cout << "OK" << endl;
    }
    else if (cmd == "QPO" && tokens.size() >= 2) {
        string name = tokens[1];
        queues[name].pop();
        cout << "OK" << endl;
    }
    else if (cmd == "QEM" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << (queues[name].empty() ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "QSI" && tokens.size() >= 2) {
        string name = tokens[1];
        cout << queues[name].size() << endl;
    }
    else if (cmd == "QPRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        queues[name].print();
    }  
    // === ДЕРЕВО (T) ===
    else if (cmd == "TINS" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        trees[name].insert(value);
        cout << "OK" << endl;
    }
    else if (cmd == "TREM" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        trees[name].remove(value);
        cout << "OK" << endl;
    }
    else if (cmd == "TFIN" && tokens.size() >= 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        bool found = trees[name].find(value);
        cout << (found ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "TPRINT" && tokens.size() >= 2) {
        string name = tokens[1];
        trees[name].print();
    }
    // === СИСТЕМНЫЕ ===
    else if (cmd == "TEST") {
        test();
    }
    else if (cmd == "EXIT" || cmd == "QUIT") {
        exit(0);
    }
    else if (cmd == "HELP") {
        cout << "Доступные команды:" << endl;
        cout << "=== МАССИВ (A) ===" << endl;
        cout << "APUB <name> <value> - Push Back" << endl;
        cout << "APOB <name> - Pop Back" << endl;
        cout << "AIN <name> <index> <value> - Insert" << endl;
        cout << "AREM <name> <index> - Remove" << endl;
        cout << "AREP <name> <index> <value> - Replace" << endl;
        cout << "AGET <name> <index> - Get elem at index" << endl;
        cout << "ALEN <name> - Get length" << endl;
        cout << "APRINT <name> - Print" << endl;

        cout << "=== ОДНОСВЯЗНЫЙ СПИСОК (S) ===" << endl;
        cout << "SPUF <name> <value> - Push Front" << endl;
        cout << "SPUB <name> <value> - Push Back" << endl;
        cout << "SINA <name> <target_value> <new_value> - Insert After" << endl;
        cout << "SINB <name> <target_value> <new_value> - Insert Before" << endl;
        cout << "SPOF <name> - Pop Front" << endl;
        cout << "SPOB <name> - Pop Back" << endl;
        cout << "SREB <name> <target_value> - Remove before" << endl;
        cout << "SREA <name> <target_value> - Remove after" << endl;
        cout << "SREM <name> <value> - Remove by value" << endl;
        cout << "SLEN <name> - Get length" << endl;
        cout << "SPRINT <name> - Print" << endl;

        cout << "=== ДВУСВЯЗНЫЙ СПИСОК (D) ===" << endl;
        cout << "DPUF <name> <value> - Push Front" << endl;
        cout << "DPUB <name> <value> - Push Back" << endl;
        cout << "DINA <name> <target_value> <new_value> - Insert After" << endl;
        cout << "DINB <name> <target_value> <new_value> - Insert Before" << endl;
        cout << "DPOF <name> - Pop Front" << endl;
        cout << "DPOB <name> - Pop Back" << endl;
        cout << "DREB <name> <target_value> - Remove before" << endl;
        cout << "DREA <name> <target_value> - Remove after" << endl;
        cout << "DREM <name> <value> - Remove by value" << endl;
        cout << "DLEN <name> - Get length" << endl;
        cout << "DPRINT <name> - Print" << endl;
        //rem bef rem after

        cout << "=== СТЕК (ST) ===" << endl;
        cout << "STPU <name> <value> - Push" << endl;
        cout << "STPO <name> - Pop" << endl;
        cout << "STEM <name> - Check if empty" << endl;
        cout << "STSI <name> - Get size" << endl;
        cout << "STPRINT <name> - Print" << endl;

        cout << "=== ОЧЕРЕДЬ (Q) ===" << endl;
        cout << "QPU <name> <value> - Push" << endl;
        cout << "QPO <name> - Pop" << endl;
        cout << "QEM <name> - Check if empty" << endl;
        cout << "QSI <name> - Get size" << endl;
        cout << "QPRINT <name> - Print" << endl;
        

        cout << "=== ДЕРЕВО (T) ===" << endl;
        cout << "TINS <name> <value> - Insert" << endl;
        cout << "TREM <name> <value> - Remove" << endl;
        cout << "TPRINT <name> - Print (inorder)" << endl;

        cout << "=== СИСТЕМНЫЕ ===" << endl;
        cout << "TEST - Run tests" << endl;
        cout << "HELP - Show this help" << endl;
        cout << "EXIT - Exit program" << endl;
    }
    else {
        cout << "Неизвестная команда. Введите HELP для справки." << endl;
    }
}

int main() {
    cout << "Система управления структурами данных" << endl;
    cout << "Введите HELP для списка команд" << endl;
    
    string line;
    while (true) {
        cout << "   > ";
        getline(cin, line);
        if (line.empty()) continue;
        process_command(line);
    }
    return 0;
}

