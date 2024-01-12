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
    static int minimumDegree;
    static int minimumNoOfKeys;
    static int maximumNoOfKeys;
    bool isLeaf;
    int noOfKeys;
    vector<Key> key;
    vector<Node *> child;
    friend class BTree;

public:
    Node();
};

class BTree
{
private:
    static int minimumDegree;
    Node *root;
    Node *splitRoot();
    void splitChild(Node *, int);
    void insertInNonFullNode(Node *, Key);
    FILE *recursiveSearch(Node *, int);

public:
    BTree();
    void insert(Key k);
    FILE *search(int);
    void display();
};
#endif