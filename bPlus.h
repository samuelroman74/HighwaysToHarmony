// BP tree
#include <iostream>
#include "Node.h"

class bPlus {
    Node *root;
    void insertInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    bPlus();
    void search(int);
    void insert(int);
    Node *getRoot();
};
