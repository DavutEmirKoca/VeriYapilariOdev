/**
* @file Node.cpp
* @description temel düğüm sınıfı
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#include "Node.hpp"

Node::Node(int data, Node* next){
            this->data=data;
            this->next=next;
}

