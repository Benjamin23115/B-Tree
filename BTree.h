#pragma once

#include <iostream>
#include <vector>

class DuplicateValueException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Duplicate value not allowed.";
    }
};

class KeyNotFoundException : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Key not found.";
    }
};

template <typename T>
struct BTreeNode
{
    std::vector<T> keys;
    std::vector<BTreeNode *> children;
    bool isLeaf;

    BTreeNode() : isLeaf(true) {}

    BTreeNode(T key) : isLeaf(true)
    {
        keys.push_back(key);
    }
};

template <typename T>
class BTree
{
private:
    BTreeNode<T> *root;
    int degree;

public:
    BTree(int t);

    void insert(T key);
    void insertNonFull(BTreeNode<T> *node, T key);
    void splitChild(BTreeNode<T> *node, int childIndex);
    bool find(T key);
    bool findInNode(BTreeNode<T> *node, T key);
    void findAndRemove(T key);
    void findAndRemoveInNode(BTreeNode<T> *node, T key);
    T getPredecessor(BTreeNode<T> *node, int idx);
    T findAndRetrieve(T key);
    T findAndRetrieveInNode(BTreeNode<T> *node, T key);
    int count();
    int countKeys(BTreeNode<T> *node);
    void destroyTree(BTreeNode<T> *node);
    ~BTree();
};
