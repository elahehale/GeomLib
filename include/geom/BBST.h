#ifndef BALANCED_BINARY_TREE_H
#define BALANCED_BINARY_TREE_H

#include <algorithm>
#include <iostream>
#include <functional>

// Do NOT use `using namespace std;` in headers

template <typename T, typename Compare = std::less<T>>
class BalancedBinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        explicit Node(const T& value)
            : data(value), left(nullptr), right(nullptr), height(1) {
        }
    };

private:
    Node* root;
    Compare comp;

    // Comparator helpers
    bool isLess(const T& a, const T& b) const { return comp(a, b); }
    bool isGreater(const T& a, const T& b) const { return comp(b, a); }
    bool isEqual(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insert(Node* node, const T& key) {
        if (!node)
            return new Node(key);

        if (isLess(key, node->data))
            node->left = insert(node->left, key);
        else if (isGreater(key, node->data))
            node->right = insert(node->right, key);
        else
            return node;

        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && isLess(key, node->left->data))
            return rotateRight(node);

        if (balance < -1 && isGreater(key, node->right->data))
            return rotateLeft(node);

        if (balance > 1 && isGreater(key, node->left->data)) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && isLess(key, node->right->data)) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& key) {
        if (!node)
            return nullptr;

        if (isLess(key, node->data))
            node->left = remove(node->left, key);
        else if (isGreater(key, node->data))
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    bool search(Node* node, const T& key) const {
        if (!node)
            return false;
        if (isEqual(node->data, key))
            return true;
        if (isLess(key, node->data))
            return search(node->left, key);
        return search(node->right, key);
    }

    void inorderTraversal(Node* node) const {
        if (!node) return;
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    Node* findNode(Node* node, const T& key) const {
        if (!node) return nullptr;
        if (isEqual(node->data, key)) return node;
        if (isLess(key, node->data))
            return findNode(node->left, key);
        return findNode(node->right, key);
    }

    Node* findParent(Node* node, const T& key, Node* parent = nullptr) const {
        if (!node) return nullptr;
        if (isEqual(node->data, key)) return parent;

        if (isLess(key, node->data))
            return findParent(node->left, key, node);
        return findParent(node->right, key, node);
    }

public:
    BalancedBinaryTree() : root(nullptr) {}

    void insert(const T& key) { root = insert(root, key); }
    void remove(const T& key) { root = remove(root, key); }
    bool search(const T& key) const { return search(root, key); }

    void printInorder() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    bool getParent(const T& key, T& parentOut) const {
        Node* parent = findParent(root, key);
        if (!parent) return false;
        parentOut = parent->data;
        return true;
    }

    bool getChildren(const T& key, T& leftOut, T& rightOut) const {
        Node* node = findNode(root, key);
        if (!node) return false;

        if (node->left) leftOut = node->left->data;
        if (node->right) rightOut = node->right->data;
        return true;
    }
};

#endif // BALANCED_BINARY_TREE_H
