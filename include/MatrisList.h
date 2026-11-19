#ifndef MATRISLIST_H
#define MATRISLIST_H

#include "Matris.h"

class MatrisList{
    private:
        Matris* head;
    public:
        //constructor: creates a matris list reading the file
        MatrisList();
        //rearranges the list as arithmetic order
        void arithmeticOrder();
        //
        void print();
        //destructor: saves and deletes the matris list
        ~MatrisList();
};

#endif