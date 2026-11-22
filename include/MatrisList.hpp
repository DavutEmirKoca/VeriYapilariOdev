/**
* @file MatrisList.hpp
* @description Matrisleri tutan liste ve işlemleri
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#ifndef MATRISLIST_HPP
#define MATRISLIST_HPP

#include "Matris.hpp"
#include "sstream"

class MatrisList{
    private:
        Matris* head;
        bool isFileOpened;
        string formatArithmeticAverage(double arithmeticAv);
        string formatAddressBox(string addressText);
    public:
        //constructor: creates a matris list reading the file
        MatrisList();
        //gets the given matris address
        Matris* getMatrisAddress(int matrisNo);
        int getMatrisIndex(Matris* targetMatris);
        //inserts a matris prev
        void insertMatrisPrev(Matris*);
        //inserts a matris next
        void insertMatrisNext(Matris*);
        //rearranges the list as arithmetic order
        void arithmeticOrder();
        //gets the matris node
        string getMatrisRow(int matrisNo,int rowNo);
        void deleteMatris(int matrisIndex);
        //destructor: saves and deletes the matris list
        ~MatrisList();
};

#endif