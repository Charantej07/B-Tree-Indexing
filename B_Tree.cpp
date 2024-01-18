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

int Node::findKey(int k)
{
    int idx = 0;
    while (idx < noOfKeys && key[idx].keyValue < k)
        ++idx;
    return idx;
}

void Node::deletion(int k)
{
    int idx = findKey(k);
    if (idx < noOfKeys && key[idx].keyValue == k)
    {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        if (isLeaf)
        {
            cout << "The key " << k << " is does not exist in the tree\noOfKeys";
            return;
        }
        bool flag = ((idx == noOfKeys) ? true : false);
        if (child[idx]->noOfKeys < minimumDegree)
            fill(idx);
        if (flag && idx > noOfKeys)
            child[idx - 1]->deletion(k);
        else
            child[idx]->deletion(k);
    }
    return;
}

void Node::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < noOfKeys; ++i)
        key[i - 1] = key[i];
    noOfKeys--;
    return;
}

void Node::removeFromNonLeaf(int idx)
{
    Key k = key[idx];
    if (child[idx]->noOfKeys >= minimumDegree)
    {
        Key pred = getPredecessor(idx);
        key[idx] = pred;
        child[idx]->deletion(pred.keyValue);
    }
    else if (child[idx + 1]->noOfKeys >= minimumDegree)
    {
        Key succ = getSuccessor(idx);
        key[idx] = succ;
        child[idx + 1]->deletion(succ.keyValue);
    }
    else
    {
        merge(idx);
        child[idx]->deletion(k.keyValue);
    }
    return;
}

Key Node::getPredecessor(int idx)
{
    Node *cur = child[idx];
    while (!cur->isLeaf)
        cur = cur->child[cur->noOfKeys];
    return cur->key[cur->noOfKeys - 1];
}

Key Node::getSuccessor(int idx)
{
    Node *cur = child[idx + 1];
    while (!cur->isLeaf)
        cur = cur->child[0];
    return cur->key[0];
}

void Node::fill(int idx)
{
    if (idx != 0 && child[idx - 1]->noOfKeys >= minimumDegree)
        borrowFromPrev(idx);
    else if (idx != noOfKeys && child[idx + 1]->noOfKeys >= minimumDegree)
        borrowFromNext(idx);
    else
    {
        if (idx != noOfKeys)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void Node::borrowFromPrev(int idx)
{
    Node *currentChild = child[idx];
    Node *sibling = child[idx - 1];
    for (int i = currentChild->noOfKeys - 1; i >= 0; --i)
        currentChild->key[i + 1] = currentChild->key[i];
    if (!currentChild->isLeaf)
    {
        for (int i = currentChild->noOfKeys; i >= 0; --i)
            currentChild->child[i + 1] = currentChild->child[i];
    }
    currentChild->key[0] = key[idx - 1];
    if (!currentChild->isLeaf)
        currentChild->child[0] = sibling->child[sibling->noOfKeys];
    key[idx - 1] = sibling->key[sibling->noOfKeys - 1];
    currentChild->noOfKeys += 1;
    sibling->noOfKeys -= 1;
    return;
}

void Node::borrowFromNext(int idx)
{
    Node *currentChild = child[idx];
    Node *sibling = child[idx + 1];
    currentChild->key[(currentChild->noOfKeys)] = key[idx];
    if (!(currentChild->isLeaf))
        currentChild->child[(currentChild->noOfKeys) + 1] = sibling->child[0];
    key[idx] = sibling->key[0];
    for (int i = 1; i < sibling->noOfKeys; ++i)
        sibling->key[i - 1] = sibling->key[i];

    if (!sibling->isLeaf)
    {
        for (int i = 1; i <= sibling->noOfKeys; ++i)
            sibling->child[i - 1] = sibling->child[i];
    }
    currentChild->noOfKeys += 1;
    sibling->noOfKeys -= 1;
    return;
}

void Node::merge(int idx)
{
    Node *currentChild = child[idx];
    Node *sibling = child[idx + 1];
    currentChild->key[minimumDegree - 1] = key[idx];
    for (int i = 0; i < sibling->noOfKeys; ++i)
        currentChild->key[i + minimumDegree] = sibling->key[i];
    if (!currentChild->isLeaf)
    {
        for (int i = 0; i <= sibling->noOfKeys; ++i)
            currentChild->child[i + minimumDegree] = sibling->child[i];
    }
    for (int i = idx + 1; i < noOfKeys; ++i)
        key[i - 1] = key[i];
    for (int i = idx + 2; i <= noOfKeys; ++i)
        child[i - 1] = child[i];
    currentChild->noOfKeys += sibling->noOfKeys + 1;
    noOfKeys--;
    delete (sibling);
    return;
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

void BTree::deletion(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
    root->deletion(k);
    if (root->noOfKeys == 0)
    {
        Node *tmp = root;
        if (root->isLeaf)
            root = NULL;
        else
            root = root->child[0];
        delete tmp;
    }
    return;
}