#ifndef MATRISLIST_H
#define MATRISLIST_H

#include "Matris.h"

class MatrisList{
    private:
        Matris* head;
    public:
        //constructor: creates a matris list reading the file
        MatrisList();
        void arithmeticOrder();
        void print();
        ~MatrisList();
};

#endif