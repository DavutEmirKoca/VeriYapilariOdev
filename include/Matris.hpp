/**
* @file Matris.hpp
* @description Düğümleri tutan matris ve işlemleri
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#ifndef MATRIS_HPP
#define MATRIS_HPP
#include "Node.hpp"
#include <random>
#include <fstream>
#include <string>

class Matris
{
private:
    
    Node *head;
    void clearMatris();
    //inserts data to given node place
    void insertNodeData(int nodePlace,int data);
    //gets the data of given node
    int getNodeData(int nodePlace);
public:
    int row;
    int column;
    Matris* next;
    //constructor: creates a blank matris
    Matris();
    //creates a predetermined matris if parametres are given
    void matrisGenerate(int row, int column, string matris);
    //creates a random matris if parametres are not given
    void matrisGenerate();
    //prints the whole matris
    void print();
    //calculates the arithmetic average of the matris and returns it
    double arithmeticCalculate();
    //deletes the given row 0 based
    void deleteRow(int row);
    //deletes the given column 0 based
    void deleteColumn(int column);
    //returns matris info as a string
    string matrisAsLine();
    //returns if the matris is empty
    bool isEmpty();
    //switch the given nodes's places
    void switchNodePlaces(int n1Row,int n1Col, int n2Row, int n2Col);
    //switch the given row and column
    void switchRowColumn(int row,int column);
    string getLine(int row,int columnDelete,int rowDelete);
    //destructor: deletes the matris
    ~Matris();
    
};

#endif