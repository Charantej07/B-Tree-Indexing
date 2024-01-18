#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include "B_Tree.h"
using namespace std;

Key::Key()
{
    keyValue = -1;
    filePtr = nullptr;
}
Key::Key(int keyValue, FILE *filePtr)
{
    this->keyValue = keyValue;
    this->filePtr = filePtr;
}

int Node::minimumDegree = 3;
int Node::minimumNoOfKeys = 3 - 1;
int Node::maximumNoOfKeys = 2 * 3 - 1;

Node::Node()
{
    isLeaf = false;
    noOfKeys = 0;
    key.assign(maximumNoOfKeys, Key(0, nullptr));
    child.assign(maximumNoOfKeys + 1, nullptr);
}

int BTree::minimumDegree = 3;

BTree::BTree()
{
    root = new Node;
    root->isLeaf = true;
    root->noOfKeys = 0;
}
Node *BTree::splitRoot()
{
    Node *newRoot = new Node;
    newRoot->child[0] = root;
    root = newRoot;
    splitChild(newRoot, 0);
    return newRoot;
}
void BTree::splitChild(Node *parent, int index)
{
    Node *fullNode = parent->child[index];
    Node *newNode = new Node;
    newNode->isLeaf = fullNode->isLeaf;
    newNode->noOfKeys = minimumDegree - 1;
    for (int i = 0; i < minimumDegree - 1; i++)
    {
        newNode->key[i] = fullNode->key[i + minimumDegree];
    }
    if (!fullNode->isLeaf)
    {
        for (int i = 0; i < minimumDegree; i++)
        {
            newNode->child[i] = fullNode->child[i + minimumDegree];
        }
    }
    fullNode->noOfKeys = minimumDegree - 1;
    for (int i = parent->noOfKeys; i >= index + 1; i--)
    {
        parent->child[i + 1] = parent->child[i];
    }
    parent->child[index + 1] = newNode;
    for (int i = parent->noOfKeys - 1; i >= index; i--)
    {
        parent->key[i + 1] = parent->key[i];
    }
    parent->key[index] = fullNode->key[minimumDegree - 1];
    parent->noOfKeys = parent->noOfKeys + 1;
}
void BTree::insertInNonFullNode(Node *currentNode, Key k)
{
    int i = currentNode->noOfKeys - 1;
    if (currentNode->isLeaf)
    {
        while (i >= 0 && k.keyValue < currentNode->key[i].keyValue)
        {
            currentNode->key[i + 1] = currentNode->key[i];
            i--;
        }
        currentNode->key[i + 1] = k;
        currentNode->noOfKeys += 1;
    }
    else
    {
        while (i >= 0 && k.keyValue < currentNode->key[i].keyValue)
        {
            i--;
        }
        i = i + 1;
        if (currentNode->child[i]->noOfKeys == 2 * minimumDegree - 1)
        {
            splitChild(currentNode, i);
            if (k.keyValue > currentNode->key[i].keyValue)
            {
                i = i + 1;
            }
        }
        insertInNonFullNode(currentNode->child[i], k);
    }
}
void BTree::insert(Key k)
{
    if (root->noOfKeys == 2 * minimumDegree - 1)
    {
        Node *newRoot = splitRoot();
        insertInNonFullNode(newRoot, k);
    }
    else
    {
        insertInNonFullNode(root, k);
    }
}

void BTree::display()
{
    if (root == nullptr)
    {
        return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            Node *currentNode = q.front();
            q.pop();
            for (int i = 0; i < currentNode->noOfKeys; i++)
            {
                cout << currentNode->key[i].keyValue << " ";
            }
            cout << "|| ";
            if (!currentNode->isLeaf)
            {
                for (int j = 0; j <= currentNode->noOfKeys; j++)
                {
                    if (currentNode->child[j] != nullptr)
                    {
                        q.push(currentNode->child[j]);
                    }
                }
            }
        }
        cout << endl;
    }
}
FILE *BTree::search(int keyValue)
{
    return recursiveSearch(root, keyValue);
}
FILE *BTree::recursiveSearch(Node *currentNode, int keyValue)
{
    int i = 0;
    while (i < currentNode->noOfKeys && keyValue > currentNode->key[i].keyValue)
    {
        i++;
    }
    if (i < currentNode->noOfKeys && keyValue == currentNode->key[i].keyValue)
    {
        return currentNode->key[i].filePtr;
    }
    else if (currentNode->isLeaf)
    {
        return nullptr;
    }
    else
    {
        return recursiveSearch(currentNode->child[i], keyValue);
    }
}