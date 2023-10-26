#include "BTree.h"

// Constructor
template <typename T>
BTree<T>::BTree(int t) : root(nullptr), degree(t) {}

// Insert a value into the B-Tree
template <typename T>
void BTree<T>::insert(T key)
{
    if (root == nullptr)
    {
        root = new BTreeNode<T>(key);
    }
    else
    {
        // Check for duplicates before insertion
        if (find(key))
        {
            throw DuplicateValueException();
        }

        // If the root is full, split it and create a new root
        if (root->keys.size() == 2 * degree - 1)
        {
            BTreeNode<T> *newRoot = new BTreeNode<T>();
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }

        // Insert the key into the non-full root
        insertNonFull(root, key);
    }
}

// Insert a key into a non-full B-Tree node
template <typename T>
void BTree<T>::insertNonFull(BTreeNode<T> *node, T key)
{
    int i = node->keys.size() - 1;

    if (node->isLeaf)
    {
        // If the node is a leaf, insert the key
        node->keys.push_back(T()); // Create space for the new key
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
    }
    else
    {
        // Find the child where the key should be inserted
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }
        i++;

        // Check for duplicates before insertion
        if (i < node->keys.size() && key == node->keys[i])
        {
            throw DuplicateValueException();
        }

        // If the child is full, split it
        if (node->children[i]->keys.size() == 2 * degree - 1)
        {
            splitChild(node, i);
            if (key > node->keys[i])
            {
                i++;
            }
        }

        // Insert the key into the appropriate child
        insertNonFull(node->children[i], key);
    }
}

// Split a full child node of a B-Tree node
template <typename T>
void BTree<T>::splitChild(BTreeNode<T> *node, int childIndex)
{
    BTreeNode<T> *child = node->children[childIndex];
    BTreeNode<T> *newChild = new BTreeNode<T>();

    // Move the middle key from the child to the parent node
    node->keys.insert(node->keys.begin() + childIndex, child->keys[degree - 1]);

    // Move the right-half of child's keys to the new child
    newChild->keys.assign(child->keys.begin() + degree, child->keys.end());
    child->keys.erase(child->keys.begin() + degree, child->keys.end());

    // If child is not a leaf, move the right-half of child's children to the new child
    if (!child->isLeaf)
    {
        newChild->children.assign(child->children.begin() + degree, child->children.end());
        child->children.erase(child->children.begin() + degree, child->children.end());
    }

    node->children.insert(node->children.begin() + childIndex + 1, newChild);
    child->keys.pop_back();
}

// Find a value in the B-Tree
template <typename T>
bool BTree<T>::find(T key)
{
    if (root == nullptr)
    {
        return false; // The tree is empty, so the key is not found.
    }
    else
    {
        return findInNode(root, key);
    }
}

// Helper function to find a key in a B-Tree node
template <typename T>
bool BTree<T>::findInNode(BTreeNode<T> *node, T key)
{
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i])
    {
        i++;
    }

    // Check if the key is found in the current node
    if (i < node->keys.size() && key == node->keys[i])
    {
        return true; // Key found in the current node
    }
    else if (node->isLeaf)
    {
        return false; // Key is not in the current node, and it's a leaf node.
    }
    else
    {
        // Recursively search in the appropriate child node
        return findInNode(node->children[i], key);
    }
}

// Find and remove a value from the B-Tree
template <typename T>
void BTree<T>::findAndRemove(T key)
{
    if (root == nullptr)
    {
        throw KeyNotFoundException();
    }
    else
    {
        findAndRemoveInNode(root, key);
    }
}

// Helper function to find and remove a key in a B-Tree node
template <typename T>
void BTree<T>::findAndRemoveInNode(BTreeNode<T> *node, T key)
{
    int idx = 0;

    // Find the index where the key is located in the current node
    while (idx < node->keys.size() && key > node->keys[idx])
    {
        idx++;
    }

    // Case 1: The key is in the current node
    if (idx < node->keys.size() && key == node->keys[idx])
    {
        if (node->isLeaf)
        {
            // Case 1a: If the key is in a leaf node, simply remove it
            node->keys.erase(node->keys.begin() + idx);
        }
        else
        {
            // Case 1b: If the key is in an internal node, replace it with the predecessor or successor
            // and recursively remove the predecessor or successor
            T pred = getPredecessor(node, idx);
            node->keys[idx] = pred;
            findAndRemoveInNode(node->children[idx], pred);
        }
    }
    else
    {
        // Case 2: The key is not in the current node
        if (node->isLeaf)
        {
            throw KeyNotFoundException();
        }
        else
        {
            // Recursively remove the key from the appropriate child
            findAndRemoveInNode(node->children[idx], key);
        }

        // Ensure B-Tree properties are maintained after the removal
    }
}

// Helper function to find and remove the predecessor key in a node
template <typename T>
T BTree<T>::getPredecessor(BTreeNode<T> *node, int idx)
{
    // Navigate to the right-most (largest) key in the left subtree
    BTreeNode<T> *current = node->children[idx];
    while (!current->isLeaf)
    {
        current = current->children[current->keys.size()];
    }
    return current->keys.back();
}

// Find a value in the B-Tree and retrieve it
template <typename T>
T BTree<T>::findAndRetrieve(T key)
{
    if (root == nullptr)
    {
        throw KeyNotFoundException();
    }
    else
    {
        return findAndRetrieveInNode(root, key);
    }
}

// Helper function to find a key in a B-Tree node and retrieve it
template <typename T>
T BTree<T>::findAndRetrieveInNode(BTreeNode<T> *node, T key)
{
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i])
    {
        i++;
    }

    // Check if the key is found in the current node
    if (i < node->keys.size() && key == node->keys[i])
    {
        return node->keys[i]; // Key found in the current node
    }
    else if (node->isLeaf)
    {
        throw KeyNotFoundException();
    }
    else
    {
        // Recursively search in the appropriate child node
        return findAndRetrieveInNode(node->children[i], key);
    }
}

// Count the number of keys in the B-Tree
template <typename T>
int BTree<T>::count()
{
    if (root == nullptr)
    {
        return 0; // The tree is empty, so there are no keys.
    }
    else
    {
        return countKeys(root);
    }
}

// Helper function to count keys in a B-Tree node
template <typename T>
int BTree<T>::countKeys(BTreeNode<T> *node)
{
    int totalCount = node->keys.size();

    if (!node->isLeaf)
    {
        for (BTreeNode<T> *child : node->children)
        {
            totalCount += countKeys(child);
        }
    }

    return totalCount;
}

// Destructor to clean up dynamically allocated memory
template <typename T>
void BTree<T>::destroyTree(BTreeNode<T> *node)
{
    if (node == nullptr)
        return;

    if (!node->isLeaf)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            destroyTree(node->children[i]);
        }
    }

    delete node;
}

// Destructor
template <typename T>
BTree<T>::~BTree()
{
    destroyTree(root);
}

// Explicit instantiation of the template for specific data types
template class BTree<int>;
