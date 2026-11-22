/**
* @file Menu.hpp
* @description ekrana yazdırma ve kontrol alma sınıfı
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 22.11.2026
* @author Davut Emir Koca davut.koca1@ogr.sakarya.edu.tr
*/
#ifndef MENU_HPP
#define MENU_HPP
#include "MatrisList.hpp"

class Menu{
    private:
        MatrisList* matrisList;
        // 0 dugum gezilimi, 1 dugum islemleri, 2 satir silme, 3 sütun silme, 4 satir sutun degistirme
        int mode;
        string screen;
        //creates the screen with current values
        void screenRefresh();
        //the indexOfSelectedMatris
        int selectedMatris;
        // for 0-4. matrises -> 0, for 5-9 matrises -> 5 and so on
        int matrisGroup;
        //the right menu
        string panels(int row);
        int rowToMatrisIndex(int i);
        int rowToMatrisRow(int row);
        void controls();
        void orderMatrisList();
        //
        int columnDeleteIndex;
        int rowDeleteIndex;
        string errorMessage;
        
    public:
        Menu();
        void run();
        void printScreen();
        ~Menu();
    
};

#endif