// C++ Program to Implement Balanced Binary Tree
#include <algorithm>
#include <iostream>
#include <functional> // Required for std::less

using namespace std;

template <typename T, typename Compare = std::less<T>>
class BalancedBinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    Compare comp; // Instance of the comparator

    // Helper functions to use the comparator
    bool isLess(const T& a, const T& b) { return comp(a, b); }
    bool isGreater(const T& a, const T& b) { return comp(b, a); }
    bool isEqual(const T& a, const T& b) { return !comp(a, b) && !comp(b, a); }

    // Function to get the height of the node
    int height(Node* node)
    {
        return node ? node->height : 0;
    }

    // Function to get the balance factor of the node
    int balanceFactor(Node* node)
    {
        return node ? height(node->left)
            - height(node->right)
            : 0;
    }

    // Function to update the height of the node
    void updateHeight(Node* node)
    {
        node->height = 1
            + max(height(node->left),
                height(node->right));
    }

    // Right rotation function
    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation function
    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Function to insert a node
    Node* insert(Node* node, T key)
    {
        // Perform the normal BST insertion
        if (!node)
            return new Node(key);

        if (isLess(key, node->data))
            node->left = insert(node->left, key);
        else if (isGreater(key, node->data))
            node->right = insert(node->right, key);
        else
            return node; // Duplicate keys are not allowed

        // Update height of this ancestor node
        updateHeight(node);

        // Get the balance factor to check whether this node
        // became unbalanced
        int balance = balanceFactor(node);

        // If the node becomes unbalanced, there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->data)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->data)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Function to find the node with the minimum value
    // (used in deletion)
    Node* findMin(Node* node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    // Function to delete a node
    Node* remove(Node* node, T key)
    {
        // Perform standard BST delete
        if (!node)
            return nullptr;

        if (isLess(key, node->data))
            node->left = remove(node->left, key);
        else if (isGreater (key, node->data))
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp
                    = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right
                    = remove(node->right, temp->data);
            }
        }

        if (!node)
            return nullptr;

        // Update height of the current node
        updateHeight(node);

        // Get the balance factor
        int balance = balanceFactor(node);

        // Balance the node if it has become unbalanced

        // Left Left Case
        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        // Left Right Case
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        // Right Left Case
        if (balance < -1
            && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Function to search for a key in the tree
    bool search(Node* node, T key)
    {
        if (!node)
            return false;
        if (isEqual(node->data, key))
            return true;
        if (isLess(key, node->data))
            return search(node->left, key);
        return search(node->right, key);
    }

    // Function for inorder traversal of the tree
    void inorderTraversal(Node* node)
    {
        if (node) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    // Constructor
    BalancedBinaryTree()
        : root(nullptr)
    {
    }

    // Public insert function
    void insert(T key) { root = insert(root, key); }

    // Public remove function
    void remove(T key) { root = remove(root, key); }

    // Public search function
    bool search(T key) { return search(root, key); }

    // Public function to print the inorder traversal
    void printInorder()
    {
        inorderTraversal(root);
        cout << endl;
    }
};
