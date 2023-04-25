//
// Created by Corey Loss on 4/20/23.
//

#include "Node.h"

    Node::Node() {
        isLeaf = true;
        size = 0;
        key = new int[numOfKeys];
        point = new Node *[numOfKeys + 1];
        for (int i = 0; i < numOfKeys + 1; i++) {
            point[i] = nullptr;
        }
    }

Node::Node(bool is_leaf, int* keys, Node** pointers, int node_size) {
    isLeaf = is_leaf;
    size = node_size;
    key = new int[numOfKeys];
    point = new Node *[numOfKeys + 1];
    for (int i = 0; i < size; i++) {
        key[i] = keys[i];
        point[i] = pointers[i];
    }
    point[size] = pointers[size];
}



