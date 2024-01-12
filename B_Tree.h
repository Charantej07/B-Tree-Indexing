#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#ifndef B_TREE_H
#define B_TREE_H

class Key
{
private:
    int keyValue;
    FILE *filePtr;

public:
    Key();
    Key(int, FILE *);
    friend class Node;
    friend class BTree;
};

class Node
{
private:
    bool isLeaf;
    int minimumDegree;
    int minimumNoOfKeys;
    int maximumNoOfKeys;
    vector<Key> key;
    vector<Node *> child;
    friend class BTree;

public:
    Node();
    Node(int minimumDegree);
};

class BTree
{
private:
    Node *root;
    void splitRoot();
    void splitChild(Node *, int);
    void insertInNonFullNode(Node *, Key);

public:
    BTree();
    void insert(Key k);
    void search(Node *, Key);
};
#endif