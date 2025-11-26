#pragma once
#include <iostream>

using namespace std;

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