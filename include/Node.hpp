/**
* @file Node.hpp
* @description temel düğüm sınıfı
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>

using namespace std;

struct Node{
        int data;
        Node* next;
        Node(int data=0, Node* next=NULL);
};

#endif