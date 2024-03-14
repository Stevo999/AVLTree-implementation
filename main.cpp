// main.cpp

#include <iostream>
#include "AVLTree.h"
#include <vector>

int main() {
    // Create an AVLTree object
    AVLTree tree;

    // Insert some key-value pairs
    tree.insert(40, "Forty");
    tree.insert(20, "Twenty");
    tree.insert(50, "Fifty");
    tree.insert(10, "Ten");
    tree.insert(30, "Thirty");
    tree.insert(45, "Forty-five");

    // Print the AVL tree
    std::cout << "AVL Tree:" << std::endl;
    std::cout << tree << std::endl;

    // Find a key in the AVL tree
    std::string value;
    int keyToFind = 30;
    bool found = tree.find(keyToFind, value);
    if (found) {
        std::cout << "Value for key " << keyToFind << ": " << value << std::endl;
    } else {
        std::cout << "Key " << keyToFind << " not found." << std::endl;
    }

    // Find the range of keys in the AVL tree
    int lowKey = 20;
    int highKey = 45;
    std::vector<std::string> rangeValues = tree.findRange(lowKey, highKey);
    std::cout << "Values in range [" << lowKey << ", " << highKey << "]:" << std::endl;
    for (const auto &val : rangeValues) {
        std::cout << val << std::endl;
    }
    return 0;
}
