//
// Created by Corey Loss on 4/19/23.
//

#include "bPlus.h"

bPlus::bPlus() {
    root = nullptr;
}

// Search the tree
void bPlus::search(int input) {
    //if empty
    if (root == nullptr) {
        cout << "Empty tree" << endl;
    } else {
        Node *cursor = root;
        //traverse until valid leaf node is found
        while (!cursor->isLeaf) {
            for (int i = 0; i < cursor->size; i++) {
                if (input < cursor->key[i]) {
                    cursor = cursor->point[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->point[i + 1];
                    break;
                }
            }
        }
        //search node for the correct key
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == input) {
                cout << "Match found" << endl;
                return;
            }
        }
        cout << "Match not found" << endl;
    }
}

// Main insert function for leaf node
void bPlus::insert(int input) {
    if (root == nullptr) {
        //adds node as root if empty
        root = new Node;
        root->key[0] = input;
        root->isLeaf = true;
        root->size = 1;
    } else {
        Node *cursor = root;
        //traverses
        Node *parent;
        while (!cursor->isLeaf) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (input < cursor->key[i]) {
                    cursor = cursor->point[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->point[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < numOfKeys) {
            int i = 0;
            while (input > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = input;
            cursor->size++;
            cursor->point[cursor->size] = cursor->point[cursor->size - 1];
            cursor->point[cursor->size - 1] = nullptr;
        } else {
            Node *newLeaf = new Node;
            int temp[numOfKeys + 1];
            for (int i = 0; i < numOfKeys; i++) {
                temp[i] = cursor->key[i];
            }
            int i = 0, j;
            while (input > temp[i] && i < numOfKeys)
                i++;
            for (int j = numOfKeys + 1; j > i; j--) {
                temp[j] = temp[j - 1];
            }
            temp[i] = input;
            newLeaf->isLeaf = true;
            cursor->size = (numOfKeys + 1) / 2;
            newLeaf->size = numOfKeys + 1 - (numOfKeys + 1) / 2;
            cursor->point[cursor->size] = newLeaf;
            newLeaf->point[newLeaf->size] = cursor->point[numOfKeys];
            cursor->point[numOfKeys] = nullptr;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = temp[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = temp[j];
            }
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->point[0] = cursor;
                newRoot->point[1] = newLeaf;
                newRoot->isLeaf = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void bPlus::insertInternal(int x, Node *cursor, Node *child) {
    if (cursor->size < numOfKeys) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->point[j] = cursor->point[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->point[i + 1] = child;
    } else {
        Node *internNode = new Node;
        int vKey[numOfKeys + 1];
        Node *vPtr[numOfKeys + 2];
        for (int i = 0; i < numOfKeys; i++) {
            vKey[i] = cursor->key[i];
        }
        for (int i = 0; i < numOfKeys + 1; i++) {
            vPtr[i] = cursor->point[i];
        }
        int i = 0, j;
        while (x > vKey[i] && i < numOfKeys)
            i++;
        for (int j = numOfKeys + 1; j > i; j--) {
            vKey[j] = vKey[j - 1];
        }
        vKey[i] = x;
        for (int j = numOfKeys + 2; j > i + 1; j--) {
            vPtr[j] = vPtr[j - 1];
        }
        vPtr[i + 1] = child;
        internNode->isLeaf = false;
        cursor->size = (numOfKeys + 1) / 2;
        internNode->size = numOfKeys - (numOfKeys + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < internNode->size; i++, j++) {
            internNode->key[i] = vKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < internNode->size + 1; i++, j++) {
            internNode->point[i] = vPtr[j];
        }
        if (cursor == root) {
            Node *newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->point[0] = cursor;
            newRoot->point[1] = internNode;
            newRoot->isLeaf = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), internNode);
        }
    }
}

// Find the parent
Node *bPlus::findParent(Node *cursor, Node *child) {
    Node *parent;
    if (cursor->isLeaf || (cursor->point[0])->isLeaf) {
        return nullptr;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->point[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParent(cursor->point[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}

// Get the root
Node *bPlus::getRoot() {
    return root;
}