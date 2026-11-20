#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

struct Node{
        int data;
        Node* next;
        Node(int data=0, Node* next=NULL);
};

#endif