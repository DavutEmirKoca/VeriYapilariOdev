#ifndef MATRISLIST_H
#define MATRISLIST_H

#include "Matris.h"
#include "sstream"

class MatrisList{
    private:
        Matris* head;
        string formatArithmeticAverage(double arithmeticAv);
    public:
        //constructor: creates a matris list reading the file
        MatrisList();
        Matris* getMatrisAddress(int matrisNo);
        //
        void insertMatrisPrev(Matris*);
        //
        void insertMatrisNext(Matris*);
        //rearranges the list as arithmetic order
        void arithmeticOrder();
        //
        void print();
        string getMatrisRow(int matrisNo,int rowNo);
        //destructor: saves and deletes the matris list
        ~MatrisList();
};

#endif