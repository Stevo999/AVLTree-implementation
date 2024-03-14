#include "AVLTree.h"

AVLTree::AVLTree() : root(NULL) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}
// Recursively destroys the AVL tree nodes
void AVLTree::destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
// Returns the height of the given node
int AVLTree::height(Node* node) const {
    return (node == NULL) ? 0 : node->height;
}

// Calculates the balance factor of the given node
int AVLTree::balanceFactor(Node* node) const {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}
// Updates the height of the given node based on its children's heights
void AVLTree::updateHeight(Node* node) {
    if (node != NULL)
        node->height = 1 + std::max(height(node->left), height(node->right));
}
// Performs a right rotation on the given node
AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}
// Performs a left rotation on the given node
AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}
// Balances the AVL tree starting from the given node
AVLTree::Node* AVLTree::balance(Node* node) {
    if (node == NULL)
        return NULL;

    updateHeight(node);

    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
// Inserts a new key/value pair into the AVL tree
AVLTree::Node* AVLTree::insert(Node* node, int key, const std::string& value) {
    if (node == NULL)
        return new Node(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        return node; // Duplicate keys not allowed

    return balance(node);
}
// Public method to insert a key/value pair into the AVL tree
bool AVLTree::insert(int key, const std::string& value) {
    root = insert(root, key, value);
    return true; // Assuming insertion is always successful for simplicity
}
// Returns the height of the AVL tree
int AVLTree::getHeight() const {
    return height(root);
}
// Returns the number of nodes in the AVL tree

int AVLTree::getSize() const {
    return countNodes(root);
}
// Counts the number of nodes in the subtree rooted at the given node
int AVLTree::countNodes(Node* node) const {
    if (node == NULL)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
// Finds the value associated with the given key in the AVL tree
bool AVLTree::find(int key, std::string& value) const {
    Node* current = root;
    while (current != NULL) {
        if (key == current->key) {
            value = current->value;
            return true;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}
// Collects values in the range [lowkey, highkey] from the AVL tree
void AVLTree::collectInRange(Node* node, int lowkey, int highkey, std::vector<std::string>& result) const {
    if (node == NULL)
        return;
    
    if (node->key >= lowkey && node->key <= highkey) {
        collectInRange(node->left, lowkey, highkey, result);
        result.push_back(node->value);
        collectInRange(node->right, lowkey, highkey, result);
    } else if (node->key < lowkey) {
        collectInRange(node->right, lowkey, highkey, result);
    } else {
        collectInRange(node->left, lowkey, highkey, result);
    }
}

std::vector<std::string> AVLTree::findRange(int lowkey, int highkey) const {
    std::vector<std::string> result;
    collectInRange(root, lowkey, highkey, result);
    return result;
}

std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
    tree.printInOrder(os, tree.root, 0);
    return os;
}

void AVLTree::printInOrder(std::ostream& os, Node* node, int indent) const {
    if (node == NULL)
        return;
    
    printInOrder(os, node->right, indent + 4);
    os << std::setw(indent) << node->key << ", " << node->value << std::endl;
    printInOrder(os, node->left, indent + 4);
}
