//
// Created by Michael Ivanov
//

#ifndef TAXIPROJECT_TREEMAP_H
#define TAXIPROJECT_TREEMAP_H

#include <iostream>

template<typename K, typename D>
class TreeMap {
public:
    struct Node {
        K key;
        D data;
        Node *left;
        Node *right;
        Node *parent;
        bool isBlack;

        Node(K _key, D _data);
    };

private:
    Node *root;

    Node *treeInsert(Node *_root, Node *_input);

    void balanceRB(Node *_input);

    void leftRotation(Node *_node);

    void rightRotation(Node *_node);

    void printTree(Node *_root);

public:

    TreeMap();

    void insert(K key, D data);

    void print();
};

template<typename K, typename D>
TreeMap<K, D>::Node::Node(K _key, D _data)
        : left(nullptr), right(nullptr), parent(nullptr), key(_key), data(_data), isBlack(false) {}

template<typename K, typename D>
TreeMap<K, D>::TreeMap() : root(nullptr) {}

template<typename K, typename D>
void TreeMap<K, D>::insert(K _key, D _data) {
    Node *input = new Node(_key, _data);
    root = treeInsert(root, input);
    balanceRB(input);
}

template<typename K, typename D>
void TreeMap<K, D>::balanceRB(Node *_input) {
    while (_input != root && !_input->parent->isBlack && !_input->isBlack) {
        Node *parent = _input->parent;
        Node *grandParent = parent->parent;
        Node *uncle = grandParent->right == parent ? grandParent->left : grandParent->right;
        // Uncle is Black
        if (!uncle || uncle->isBlack) {
            if (grandParent->left == parent) {
                // Left
                if (parent->right == _input) { //Left Right
                    leftRotation(parent);
                    _input->isBlack = !_input->isBlack;
                } else { // Left Left
                    parent->isBlack = !parent->isBlack;
                }
                rightRotation(grandParent);
            } else { // Right
                if (parent->left == _input) { // Right Left
                    rightRotation(parent);
                    _input->isBlack = !_input->isBlack;
                } else { // Right Right
                    parent->isBlack = !parent->isBlack;
                }
                leftRotation(grandParent);
            }
            grandParent->isBlack = !grandParent->isBlack;
        } else { // Uncle is Red
            uncle->isBlack = true;
            parent->isBlack = true;
            _input = grandParent;
        }
    }
    root->isBlack = true;
}

template<typename K, typename D>
typename TreeMap<K, D>::Node *TreeMap<K, D>::treeInsert(TreeMap::Node *_root, TreeMap::Node *_input) {
    if (_root == nullptr)
        return _input;
    _input->parent = _root;
    if (_root->key < _input->key) {
        _root->right = treeInsert(_root->right, _input);
    } else {
        _root->left = treeInsert(_root->left, _input);
    }
    return _root;
}

template<typename K, typename D>
void TreeMap<K, D>::leftRotation(TreeMap::Node *_node) {
    Node *child = _node->right;
    if (_node == root) {
        root = child;
    }
    _node->right = child->left;
    if (_node->right) {
        _node->right->parent = _node;
    }
    child->left = _node;
    child->parent = _node->parent;
    _node->parent = child;
}

template<typename K, typename D>
void TreeMap<K, D>::rightRotation(TreeMap::Node *_node) {
    Node *child = _node->left;
    if (_node == root) {
        root = child;
    }
    _node->left = child->right;
    if (_node->left) {
        _node->left->parent = _node;
    }
    child->right = _node;
    child->parent = _node->parent;
    _node->parent = child;
}

template<typename K, typename D>
void TreeMap<K, D>::print() {
    printTree(root);
}

template<typename K, typename D>
void TreeMap<K, D>::printTree(TreeMap::Node *_root) {
    if (!_root)
        return;
    std::cout << _root->key << " " << _root->isBlack << std::endl;
    printTree(_root->left);
    printTree(_root->right);
}


#endif //TAXIPROJECT_TREEMAP_H
