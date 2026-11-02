#ifndef MATRIS_H
#define MATRIS_H
#include "Node.h"
#include <random>
#include <fstream>
#include <string>

class Matris
{
private:
    int row;
    int column;
    Node *head;

public:
    Matris* next;
    //
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
    //generates a random matris if no values are passed, generates a predetermined matris if values are passed
    //deletes the given row
    void deleteRow(int row);
    //deletes the given column
    void deleteColumn(int column);
    //inserts the matris to the file
    string matrisAsLine();
    //
    bool isEmpty();
    void switchNodePlaces(int n1Row,int n1Col, int n2Row, int n2Col);
    void switchRowColumn(int row,int column);
    //destructor: deletes the matris row by row until the matris is empty
    ~Matris();
    
};

#endif