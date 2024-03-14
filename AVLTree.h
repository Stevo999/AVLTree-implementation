#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For setw

class AVLTree {
private:
    struct Node {
        int key;
        std::string value;
        Node* left;
        Node* right;
        int height;
        Node(int k, const std::string& v) : key(k), value(v), left(NULL), right(NULL), height(1) {}
    };

    Node* root;

    // Helper methods for AVL operations
    void destroyTree(Node* node);
    int height(Node* node) const; // Add const qualifier
    int balanceFactor(Node* node) const; // Add const qualifier
    void updateHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insert(Node* node, int key, const std::string& value);
    int countNodes(Node* node) const; // Add const qualifier
    void collectInRange(Node* node, int lowkey, int highkey, std::vector<std::string>& result) const; // Add const qualifier
    void printInOrder(std::ostream& os, Node* node, int indent) const; // Add const qualifier

public:
    AVLTree();
    ~AVLTree();

    bool insert(int key, const std::string& value);
    int getHeight() const; // Add const qualifier
    int getSize() const; // Add const qualifier
    bool find(int key, std::string& value) const; // Add const qualifier
    std::vector<std::string> findRange(int lowkey, int highkey) const; // Add const qualifier

    friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree);
};

#endif
