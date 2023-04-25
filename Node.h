#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int numOfKeys = 3;

class Node {
    bool isLeaf;
    int *key;
    int size;
    Node **point;
    friend class bPlus;

public:
    Node();
    Node(bool isLeaf, int *keys, Node **pointers, int node_size);
};